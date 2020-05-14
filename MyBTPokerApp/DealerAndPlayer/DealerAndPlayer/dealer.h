#ifndef DEALER_H
#define DEALER_H

/*
 * DESCRIPTION OF DEALER CLASS
 * This is the second major class of poker app. It's is managing flow of the game round.
 * It has methods to despense cards to players and to table(in Room), methods to rule the round(updatePlayers(),startTrade(),demandAction(Player*), etc)
 * It also select winner of the round. Within the game every player will eventualy call for dealer.
*/
#include "player.h"

class Dealer
{
public:
    Dealer(Player* p_seat,QVector <Player>* p_Vect, QVector<int>* p_Table, const int& sBlind, int* pStake);/**/
    Dealer(const Dealer& arg);
    ~Dealer();
    void servePlayers();
    void serveTable();
    void showTable();
    int  getPlayers();
    void showPlayersHands();
    void setBlind(const int& arg);
    //Round manager
    void updatePlayers();
    void throwBlinds();
    void startTrade();
    void demandAction(Player* p);
    Player* findTopKit();
    void declareWinner(Player* p);
    void finishRound();
private:
    int                 m_numPlayers;
    int                 m_smallBlind;
    int                 m_bigBlind;
    int                 m_rebuyValue;
    int* const          p_stake;
    Player*             p_dealingPlayer;
    std::unique_ptr<QVector <Player> > uPtr_playersVector;
    //QVector<Player>*    p_playersVect;
    QVector <int>*      p_gamingTable;
    Deck*               p_gameDeck;
};
#endif // DEALER_H
