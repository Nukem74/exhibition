#ifndef IWIDGET_H
#define IWIDGET_H

//#include <QCoreApplication>
#include <QApplication>
#include "server.h"
#include "client.h"
//iWidget class description
/*
 * iWidget class developed to initialise different modes of this app by user's choice.
 * iWidget inherited from QWidget
 * It provides simple window with 2 buttons for each mode.
 * When user choose "Speak" button - iWidget initialises class Client, which is broadcasting messages.
 * When user choose "Listen" button - iWdiget initialises class Server, which is displaying received messages.
 * iWidget class doesn't reimplement default members, but default constructor.
 * Also, default constructor is only public member of this class.
*/
class iWidget : public QWidget
{
    Q_OBJECT
public:
    explicit iWidget(QWidget* parent = nullptr);
private:
    QWidget* son;
private slots:
    void makeServer();
    void makeClient();
};

#endif // IWIDGET_H

