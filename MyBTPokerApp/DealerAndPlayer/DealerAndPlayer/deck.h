#ifndef DECK_H
#define DECK_H
/*
 * DESCRIPTION OF DECK CLASS
 * Class Deck is managing representation of cards in deck as natural number from 0 to 51.
 * It selects random cards depending on players participating, and extract single card from Deck by user request.
 * Also, for debugging purpose it has method getCard() to show selected cards in console.
*/


#include <QCoreApplication>
#include <QVector>
#include <QtDebug>
#include <QtAlgorithms>
#include <iostream>
#include <mutex>
#include <memory>
#include <QTime>

const int deckSize = 52;

class Deck
{
public:
    Deck();/**/
    Deck(const Deck& arg);          //copyconstrutor, isn't it?
    ~Deck();
    void            selectCards(const int& nPlayers);/**/
    void            showCards();/**/
    int             getCard();/**/
private:
    int             deckHeight;
    QVector <int>   playDeck;
    bool            fullDeck[deckSize];
};


#endif // DECK_H
