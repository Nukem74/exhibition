#include "iwidget.h"

iWidget::iWidget(QWidget* parent) : QWidget(parent), son(nullptr)
{
    this->setGeometry(256,196,256,96);

    auto speakButton    = new QPushButton("Speak");
    auto listenButton   = new QPushButton("Listen");

    connect(speakButton, SIGNAL(clicked()),
            this, SLOT(makeClient()));

    connect(listenButton, SIGNAL(clicked()),
            this, SLOT(makeServer()));

    auto layout = new QVBoxLayout;

    layout->addWidget(speakButton);
    layout->addWidget(listenButton);
    setLayout(layout);



    setWindowTitle("Welcome");
}


void iWidget::makeServer()
{
    son = new Server;
    this->hide();
    son->show();
}
void iWidget::makeClient()
{
    son = new Client;
    this->hide();
    son->show();
}

