#ifndef CLIENT_H
#define CLIENT_H

/*Description of class Client
 * Client class responsible for broadcasting messages.
 * Client inherited from QWidget.
 * It's providing simple users interface to operate broadcasting
 * It's user's choice to start broadcasting with "Start" button
 * When broadcasting is on - user may send logging message with current date with "Log" button
 * To stop broadcasting user has to close Client window, which will cause app to end
 *
 * Client class doesn't reimplement default members, but default contructor.
 * Also, default constructor is only public member of this class.
 */

#include <QtCore>
#include <QtWidgets>
#include <QUdpSocket>
#include <ctime>
#include <chrono>



class Client : public QWidget
{
    Q_OBJECT

public:
    explicit        Client(QWidget *parent = nullptr);

private slots:
    void            slot_startBroadcasting();
    void            slot_broadcastDatagram();
    void            slot_castLogRecord();

private:
    QLabel*         p_statusLabel;
    QPushButton*    p_startButton;
    QPushButton*    p_logButton;
    QUdpSocket*     p_udpSocket;
    QTimer          m_timer;
    size_t          m_messageNo;
};

#endif // CLIENT_H

