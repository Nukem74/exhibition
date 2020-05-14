#include "room.h"
#include <algorithm>
Room::Room() : m_numberPlayers(0) , m_smallBlind(5) ,  m_bank(0), m_initializerPlayer(nullptr)
{
    qDebug() << "Room::Room()";
    seats_Players.clear();
    seats_Players.reserve(8);
    tableCards.clear();
    tableCards.reserve(5);
}

Room::~Room()
{
    qDebug() << "Room::~Room()";
    m_numberPlayers = 0;
    seats_Players.clear();
}

void Room::initializePlayer()
{
    m_initializerPlayer = new iPlayer(m_smallBlind,m_numberPlayers,&seats_Players,&tableCards,&m_stake);
}

/*void Room::addPlayer()
{
    if((m_numberPlayers + 1) <= 8)
    {
        seats_Players.push_back(Player(&seats_Players,&tableCards,m_numberPlayers,m_smallBlind));
        m_numberPlayers++;
    }
    else
    {
        qDebug() << "Room::addPlayer()" << "Room is full";
    }

}*/

void Room::addPlayer() /*iPlayer& init*/
{
    initializePlayer();
    if((m_numberPlayers + 1) <= 8)
    {
        seats_Players.push_back(Player(*m_initializerPlayer));

        connect(&seats_Players.back(),   SIGNAL(fold())
                ,this,                  SLOT(dbg_slotFold()));

        connect(&seats_Players.back(),   SIGNAL(bet(const int&))
                ,this,                  SLOT(dbg_slotBet(const int&)));
        m_numberPlayers++;
    }
    else
    {
        qDebug() << "Room::addPlayer(iPlayer& init)" << "Room is full";
    }
    delete m_initializerPlayer;
    m_initializerPlayer = nullptr;
}

void Room::removePlayer(const Player &player)
{
    seats_Players.removeOne(player);
    qDebug() << "player removed";
}

void Room::startRound()
{
    qDebug() << "Room::startRound()";
    m_bank = 0;
    m_stake = 0;
    tableCards.clear();
    QVector<Player>::iterator it = std::find(seats_Players.begin(),seats_Players.end(),Player(0,nullptr));
    if(it != seats_Players.end())
    {
        it->playDealer();
        qDebug() << "startRound() "<< "new dealer is" << &it;
    }
    else
    {
        qDebug() << "startRound() " << "no dealer called";
    }
    //std::sort(seats_Players.begin(), seats_Players.end());
}

void Room::endRound()
{
    QVector<Player>::iterator it = seats_Players.begin();
    while(it != seats_Players.end())
    {
        it->newOrder((it->getOrder() + 1) % seats_Players.size());
        qDebug() << "endRound() " << it->getOrder();
        it++;
    }
    //qSort(seats_Players.begin(),seats_Players.end(),operator<(const Player& arg1, const Player& arg2));
}

int Room::getNumberPlayers()
{
    return m_numberPlayers;
}

void Room::dbg_slotFold()
{

}

void Room::dbg_slotBet(const int&)
{

}

void Room::dbg_removePlayer()
{
    seats_Players.removeLast();
    m_numberPlayers--;
}
