#include "client.h"

Client::Client(QWidget *parent)
    : QWidget(parent)
    , p_statusLabel(nullptr)
    , p_startButton(nullptr)
    , p_logButton(nullptr)
    , p_udpSocket(nullptr)
    , m_messageNo(1)
{
    p_statusLabel = new QLabel(tr("Ready to broadcast datagrams on port 45454"));
    p_statusLabel->setWordWrap(true);

    p_startButton = new QPushButton(tr("&Start"));
    p_logButton = new QPushButton(tr("&Log"));
    auto quitButton = new QPushButton(tr("&Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(p_startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(p_logButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    p_udpSocket = new QUdpSocket(this);

    connect(p_startButton, &QPushButton::clicked, this, &Client::slot_startBroadcasting);
    connect(p_logButton, &QPushButton::clicked,this,&Client::slot_castLogRecord);
    connect(quitButton, &QPushButton::clicked, this, &Client::close);
    connect(&m_timer, &QTimer::timeout, this, &Client::slot_broadcastDatagram);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(p_statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Sender"));
}

void Client::slot_startBroadcasting()
{
    p_startButton->setEnabled(false);
    m_timer.start(100);
}

void Client::slot_broadcastDatagram()
{
    QByteArray datagram;
    if(m_messageNo % 2 == 0)
    {
        ++m_messageNo;
        datagram = "Broadcast message " + QByteArray::number(m_messageNo);

        p_statusLabel->setText(tr("Now broadcasting datagram %1").arg(m_messageNo));
    }
    else
    {
        datagram = "Broadcast message " + QByteArray::number(m_messageNo);
        p_statusLabel->setText(tr("Now broadcasting datagram %1").arg(m_messageNo));
        ++m_messageNo;
    }

    p_udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);

}

void Client::slot_castLogRecord()
{
    std::time_t result = std::time(nullptr);
    QByteArray datagram = std::asctime(std::localtime(&result));
    qDebug() << datagram;
    p_udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}


