#include <QCoreApplication>
#include <QVector>
#include <QtDebug>

#include "room.h"
#include <iostream>
#include <QTime>

#include <atomic>
#include <mutex>
#include <thread>

namespace Oleshko
{
    class sample
    {
    public:
        sample()
        {
            std::cout << "Deafault constructor" << std::endl;
        }
        sample(const sample&)
        {
            std::cout << "Copy constructor" << std::endl;
        }
        sample(const sample&&)
        {
            std::cout << "R-value constructor" << std::endl;
        }
        ~sample()
        {
            std::cout << "Destructor" << std::endl;
        }
        sample operator=(const sample& arg)
        {
            std::cout << "Operator = ";
            return sample(arg);
        }
        bool operator ==(const sample& arg)
        {
            std::cout << "Operator == ";
            return (this == &arg);
        }
        bool operator!=(const sample& arg)
        {
            std::cout << "Operator != ";
            return (this != &arg);
        }
        bool operator<(const sample& arg)
        {
            std::cout << "Operator < ";
            return (this < &arg);
        }
        bool operator>(const sample& arg)
        {
            std::cout << "Operator > ";
            return (this > &arg);
        }
        friend bool operator<(const sample& arg1, const sample& arg2);
        friend bool operator >(const sample& arg1, const sample& arg2);
        friend bool operator ==(const sample& arg1, const sample& arg2);
        friend bool operator !=(const sample& arg1, const sample& arg2);
    };

    bool operator <(const sample& arg1, const sample& arg2)
    {
        std::cout << "Operator < ";
        return (&arg1 < &arg2);
    }

    bool operator>(const sample& arg1, const sample& arg2)
    {
        std::cout << "Operator > ";
        return (&arg1 > &arg2);
    }

    bool operator==(const sample& arg1, const sample& arg2)
    {
        std::cout << "Operator < ";
        return (&arg1 == &arg2);
    }

    bool operator!=(const sample& arg1, const sample& arg2)
    {
        std::cout << "Operator < ";
        return (&arg1 != &arg2);
    }
}

/*
R   *10 Flash Royal    (checkFlashRolyal)
H   *9 Flash Street    (checkFlashStreet)
Q   *8 Square          (checkMultiple == 4)
TP  *7 Full House      (checkMultiple == 3)
F*  6 Flash           (checkFlash)
S*  5 Street          (checkStreet)
T   *4 Set             (checkMultiple == 3)
PP  *3 Pair of pairs   (checkMultiple == 2)
P   *2 Pair            (checkMultiple == 2)
K*1 Kicker          (checkKicker)
 */



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    Room lab;
    lab.addPlayer();
    lab.addPlayer();
    lab.startRound();
    return app.exec();
}
