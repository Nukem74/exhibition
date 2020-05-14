#include "deck.h"

/*
    Hearts   Diamonds   Spades   Clubs
2       0  ||   13    ||  26   ||   39
=======================================
3       1  ||   14    ||  27   ||   40
=======================================
4       2  ||   15    ||  28   ||   41
=======================================
5       3  ||   16    ||  29   ||   42
=======================================
6       4  ||   17    ||  30   ||   43
=======================================
7       5  ||   18    ||  31   ||   44
=======================================
8       6  ||   19    ||  32   ||   45
=======================================
9       7  ||   20    ||  33   ||   46
=======================================
10      8  ||   21    ||  34   ||   47
=======================================
J       9  ||   22    ||  35   ||   48
=======================================
Q       10 ||   23    ||  36   ||   49
=======================================
K       11 ||   24    ||  37   ||   50
=======================================
A       12 ||   25    ||  38   ||   51

*/


Deck::Deck(): deckHeight(5)
{
    qDebug() << "Deck()";
    for(int i = 0;i < deckSize; i++)
    {
        fullDeck[i] = true;
    }
    playDeck.clear();
    playDeck.reserve(21);
}

Deck::Deck(const Deck& arg)
{
    deckHeight = arg.deckHeight;
    for(int i = 0; i < deckSize;i++)
    {
        fullDeck[i] = arg.fullDeck[i];
    }

    for(int i = 0; i < arg.deckHeight; i++)
    {
        playDeck.push_back(arg.playDeck[i]);
    }
}

Deck::~Deck()
{
    for(int i = 0;i < deckSize; i++)
    {
        fullDeck[i] = true;
    }
    playDeck.clear();
}


void Deck::selectCards(const int& nPlayers)
{
    qDebug() << "Deck::selectCards(" << nPlayers << ") ";
    deckHeight += 2*nPlayers;

    std::srand(unsigned(std::clock()));
    for(int i = 0; i < deckHeight;)
    {

        int tempValue = std::rand() % (deckSize - 1);
        //qDebug() << tempValue;
        if(fullDeck[tempValue])
        {
            fullDeck[tempValue] = false;
            playDeck.push_back(tempValue);
            //std::cout << tempValue << " ";
            i++;

        }
        else
        {
            continue;
        }
    }
    std::cout << std::endl;

}

void Deck::showCards()
{
    if(playDeck.size() > 5)
    {

        for(QVector<int>::iterator it = playDeck.begin(); it != playDeck.end(); it++)
        {
            //QDebug() << it;   find a way to show cards in console
        }
    }
}

int Deck::getCard()
{
    qDebug() << "Deck::getCard()";
    int retVal = 111;
    if(!playDeck.isEmpty())
    {
        retVal = playDeck.back();
        playDeck.pop_back();
    }
    else
    {
        return 404;
    }


    return retVal;
}
