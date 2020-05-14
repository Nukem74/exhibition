#ifndef SERVER_H
#define SERVER_H

/* Server class description
 * Class Server responsible for receiving broadcasted messages.
 * Server inherited from QWidget.
 * It's displaying last 10 received messages within message list.
 * Also, server provides error messages when received broadcast has unexpected value
 * or broadcast interval was interupted for more then 1 second.
 * There is an option for user to start broadcasting messages in response for received messages.
 *
 * Server class doesn't reimplement default members, but default contructor.
 * Also, default constructor is only public member of this class.
 */
#include <QtWidgets>
#include <QtNetwork>

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit        Server(QWidget *parent = nullptr);

private slots:
    void            slot_processPendingDatagrams();
    void            slot_connectionTimeout();
    void            slot_feedbackDatagram();

private:
    int             m_reconnectAttempts;
    int             m_nextValue;
    int             m_errorCount;
    int             m_responseNo;
    QUdpSocket*     p_udpSocket;
    QListWidget*    p_messageList;
    QRadioButton*   p_respondFlag;
    QTimer*         p_feedbackTimeout;
    QTimer*         p_connectionTimeout;
};

#endif // SERVER_H

