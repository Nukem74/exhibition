#ifndef ROOM_H
#define ROOM_H
#include "dealer.h"
/*
 * DESCRIPTION OF ROOM CLASS
 * This class represents state of gaming room. It stores vector of Players, vector of table cards, value of bank, value of small blind
 * value of stake.
 * It provides methods to add players in Room, remove players from room, start round, end round, and to set cards for table
*/
class Room : public QObject
{
    //Q_OBJECT
public:
    Room();
    ~Room();
    void                initializePlayer();
    void                addPlayer();
    //void                addPlayer(iPlayer& init);
    void                removePlayer(const Player& player);
    void                dbg_removePlayer();
    void                startRound();
    void                endRound();
    int                 getNumberPlayers();
    //void                setTable();
private:
    int                 m_numberPlayers;
    int                 m_smallBlind;
    int                 m_bank;
    int                 m_stake;
    iPlayer*            m_initializerPlayer;
    QVector <Player>    seats_Players;
    QVector <int>       tableCards;
private slots:
    void                dbg_slotFold();
    void                dbg_slotBet(const int&);

};




#endif // ROOM_H
