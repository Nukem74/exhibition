#include <QCoreApplication>
#include <QVector>
#include <QtDebug>
#include <QtAlgorithms>
#include <iostream>
#include <mutex>
#include <memory>
#include <QTime>

class Dealer;

class Room;
/*
 * DESCRIPTION OF HAND CLASS
 * This is auxilary struct to represent cards in Player's hand. All it's members are public.
 *
 * */
struct Hand
{
    Hand() : card_A(101) , card_B(101)
    {

    }
    Hand(const Hand& arg)
    {
        card_A = arg.card_A;
        card_B = arg.card_B;
    }
    int     card_A;
    int     card_B;
};

/*
 * DESCRIPTION OF USERACTION ENUMERATION CLASS
 * This is auxilary class to represent action undertaken by players.
*/
enum class userAction
{
    away,       //for timed-out players

    call,       //for players called a stake

    check,      //for players checked stake

    fold,       //for players folded hand

    idle,       //for players not acted

    rise,       //for players risen stake

    quit        //for players quit the game(room)

};

class Player;

/*
 * DESCRIPTION OF IPLAYER CLASS
 * This is auxilary class for initialising Player's instance, since Player's constructor has too much arguments.
*/

struct iPlayer
{
    iPlayer(const int& sBlind, const int& order, QVector<Player>* pPlayers, QVector<int>* pTable, int* stake): init_sBlind(sBlind)
                                                                                                            , init_order(order)
                                                                                                            , init_uPtr_playersVector(pPlayers)
                                                                                                            , init_gamingTable(pTable)
                                                                                                            , init_stake(stake)
    {

    }
    iPlayer(const iPlayer& arg) = delete;
    iPlayer operator=(const iPlayer& arg) = delete;
    const int               init_sBlind;
    const int               init_order;
    std::unique_ptr<QVector<Player> > init_uPtr_playersVector;
    QVector<int>*           init_gamingTable;
    int*                    init_stake;
};
