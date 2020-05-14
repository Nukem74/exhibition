#include "server.h"
#include <string>
int ctoi(char arg)
{
    //this fucntion casting type char numbers to type int
    if(arg < 48 || arg > 57)
        return 0;
    return (static_cast<int>(arg) - 48);
}

int stringToInt(std::string arg)
{
    //this fucntion casting type string numbers to type int
    int value = 0;
    for(size_t it = 1; it <= arg.length(); it++)
    {
        value += pow(10, it - 1) * ctoi(*(arg.end() - it));
    }
    return value;
}

Server::Server(QWidget *parent)
    : QWidget(parent)
    , m_reconnectAttempts(0)
    , m_nextValue(0)
    , m_errorCount(0)
    , m_responseNo(1)
    , p_udpSocket(nullptr)
    , p_messageList(nullptr)
    , p_feedbackTimeout(new QTimer)
    , p_connectionTimeout(new QTimer)
{


    p_messageList = new QListWidget;

    auto quitButton = new QPushButton(tr("&Quit"));
    p_respondFlag = new QRadioButton(tr("Respond"));

    p_udpSocket = new QUdpSocket(this);
    p_udpSocket->bind(45454, QUdpSocket::ShareAddress);

    connect(p_connectionTimeout,SIGNAL(timeout()),
            this,SLOT(slot_connectionTimeout()));

    connect(p_feedbackTimeout,SIGNAL(timeout()),
            this,SLOT(slot_feedbackDatagram()));

    connect(p_udpSocket, SIGNAL(readyRead()),
            this, SLOT(slot_processPendingDatagrams()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addWidget(p_respondFlag);
    buttonLayout->addStretch(1);

    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(p_messageList);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Receiver"));
}

void Server::slot_connectionTimeout()
{
    //this slot is displaying connection timeout error
    p_messageList->addItem(new QListWidgetItem("Connection timeout",p_messageList));
    p_connectionTimeout->stop();
}

void Server::slot_feedbackDatagram()
{
    //this slot is broadcasting feedback messages
    QByteArray datagram;

    if(m_responseNo % 2 != 0)
    {
        ++m_responseNo;
        datagram = "Response message " + QByteArray::number(m_responseNo);
    }
    else
    {
        datagram = "Response message " + QByteArray::number(m_responseNo);
        ++m_responseNo;
    }
    p_udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

void Server::slot_processPendingDatagrams()
{
    //this slot process and display received messages
    //check for valid datagram size
    if(p_udpSocket->pendingDatagramSize() == 0)
    {
        p_messageList->addItem(new QListWidgetItem("Datagram transaction failed",p_messageList));
        return;
    }
    //start connection timer
    p_connectionTimeout->start(1000);

    QByteArray datagram;

    //read message
    while (p_udpSocket->hasPendingDatagrams())
    {
        //set QByteArray size to fit received datagram and read it
        datagram.resize(int(p_udpSocket->pendingDatagramSize()));
        p_udpSocket->readDatagram(datagram.data(), datagram.size());

        //extract value received from Client
        std::string str = datagram.data();
        if(str.find_first_of("Broadcast") != 0 && str.find_first_of("Response") != 0)
        {
            p_messageList->addItem(new QListWidgetItem(str.data(),p_messageList));
            p_messageList->count() > 10 ? p_messageList->takeItem(0) : nullptr;
        }
        int value = stringToInt(str);

        //validate received value and display
        if(value % 2 != 0)
        {
            p_messageList->addItem(new QListWidgetItem(tr("Received datagram: \"%1\" from \"%2\"")
                                                       .arg(value)
                                                       .arg(p_udpSocket->peerAddress().toIPv4Address())
                                                       ,p_messageList));
            p_messageList->count() > 10 ? p_messageList->takeItem(0) : nullptr;
            //respond to Client
            if(p_respondFlag->isChecked())
                p_feedbackTimeout->start(50);
            else
            {
                p_feedbackTimeout->stop();
            }
            //display error
            if(value != m_nextValue)
            {
                p_messageList->addItem(new QListWidgetItem(tr("Error count incresed: \"%1\"")
                                                           .arg(++m_errorCount),p_messageList));
                p_messageList->count() > 10 ? p_messageList->takeItem(0) : nullptr;
            }
            m_nextValue = value + 2;
        }
    }
}
