#include "player.h"

Player::Player(/*QObject* pObj*/)   : m_playerHand()
                                    , m_sBlind(5)
                                    , m_order(0)
                                    , m_stake(0)
                                    , m_wallet(0)
                                    , p_stake(nullptr)
                                    , p_dealer(nullptr)
                                    , uPtr_playersVector(nullptr)
                                    , p_TimeClick(nullptr)
                                    , p_gamingTable(nullptr)
                                    , m_userAction(userAction::idle)

{
    qDebug() << "Player::Player()";
}

Player::Player(int place, int* stake/*,QObject* pObj*/) : m_playerHand()
                                                        , m_sBlind(5)
                                                        , m_order(place)
                                                        , m_stake(0)
                                                        , m_wallet(0)
                                                        , p_stake(stake)
                                                        , p_dealer(nullptr)
                                                        , uPtr_playersVector(nullptr)
                                                        , p_TimeClick(nullptr)
                                                        , p_gamingTable(nullptr)
                                                        , m_userAction(userAction::idle)
{
    qDebug() << "Player::Player(int, int*)";
}
//Replaced with Player(iPlayer& arg)
/*Player::Player(QVector<Player>* pVect,QVector<int>* pTable,const int& sBlind, int place)       : m_playerHand()
                                                                                                , m_order(place)
                                                                                                , p_dealer(nullptr)
                                                                                                , p_playersVect(pVect)
                                                                                                , p_gamingTable(pTable)
                                                                                                , m_wallet(0)
                                                                                                , m_userAction(userAction::idle)
                                                                                                , m_sBlind(sBlind)
{
    qDebug() << place;
}*/

Player::Player(const Player& arg/*,QObject* pObj*/)   : m_playerHand(arg.m_playerHand)
                                                      , m_sBlind(arg.m_sBlind)
                                                      , m_order(arg.m_order)
                                                      , m_stake(arg.m_stake)
                                                      , m_wallet(arg.m_wallet)
                                                      , p_stake(arg.p_stake)
                                                      , p_dealer(arg.p_dealer)
                                                      , uPtr_playersVector(arg.uPtr_playersVector.get())//there will be shit
                                                      , p_TimeClick(arg.p_TimeClick)
                                                      , p_gamingTable(arg.p_gamingTable)
                                                      , m_userAction(userAction::idle)
{
    qDebug() << "Player::Player(const Player&)";
}

Player::Player(iPlayer& arg/*, QObject* pObj*/) : m_playerHand()
                                                  , m_sBlind(arg.init_sBlind)
                                                  , m_order(arg.init_order)
                                                  , m_stake(0)
                                                  , m_wallet(0)
                                                  , p_stake(arg.init_stake)
                                                  , p_dealer(nullptr)
                                                  , uPtr_playersVector(arg.init_uPtr_playersVector.release())//there will be shit
                                                  , p_TimeClick(nullptr)
                                                  , p_gamingTable(arg.init_gamingTable)
                                                  , m_userAction(userAction::idle)
{
    qDebug() << "Player(iPlayer& arg)";
}

Player::~Player()
{
    qDebug() << "Player::~Player()";            //Rule for deleting pointer - first set to nullpointer, second - delete
    //qDebug() << "~Hand";                        //What about calling constructor?
    m_playerHand.card_A = 99;
    m_playerHand.card_B = 99;
    m_order = 9;
    m_stake = 0;
    //delete p_dealer;
    p_dealer = nullptr;
    if(uPtr_playersVector)
        uPtr_playersVector.release();
    p_gamingTable = nullptr;
    //delete p_gamingTable;
    p_TimeClick = nullptr;
    //delete p_TimeClick;
    //delete p_stake;
}

void Player::setCard(const int &card)
{
    qDebug() << "Player::setCard";
    if(m_playerHand.card_A == 101)
    {
        m_playerHand.card_A = card;
        qDebug() << this << " card A is " << card;
        return;
    }
    else if(m_playerHand.card_B == 101)
    {
        m_playerHand.card_B = card;
        qDebug() << this << " card B is " << card;
        return;
    }
}

void Player::resetCard()
{
    m_playerHand.card_A = 101;
    m_playerHand.card_B = 101;
}

void Player::showHand()
{
    qDebug() << this << " " << this->m_order << " " << m_playerHand.card_A << " and " << m_playerHand.card_B;
}

Hand Player::getHand()
{
    return this->m_playerHand;
}

int Player::getOrder()
{
    return m_order;
}

void Player::newOrder(const int& ref)
{
    m_order = ref;
}

void Player::increaseWallet(const int &arg)
{
    m_wallet += arg;
}

void Player::collectPrize(const int &arg)
{
    m_wallet += arg;
}

Player Player::operator =(const Player &arg)
{
    return Player(arg);
}

bool Player::operator ==(const Player &arg)
{
    return (this->m_order == arg.m_order);
}

bool    operator >(const Player& arg1, const Player& arg2)
{
    return ( arg1.m_order > arg2.m_order);
}

bool    operator>=(const Player& arg1, const Player& arg2)
{
    return ( arg1.m_order >= arg2.m_order);
}

bool    operator<(const Player& arg1, const Player& arg2)
{
    return ( arg1.m_order < arg2.m_order);
}

bool    operator<=(const Player& arg1, const Player& arg2)
{
    return ( arg1.m_order <= arg2.m_order);
}

bool operator==(const Player& arg1, const Player& arg2)
{
    return (arg1.m_order == arg2.m_order);
}

//user action

userAction Player::getUserAction()
{
    switch (m_userAction)
    {
        case (userAction::away):    qDebug() << "Player away";              return m_userAction;
        case (userAction::call):    qDebug() << "Player called";            return m_userAction;
        case (userAction::check):   qDebug() << "Player cheked";            return m_userAction;
        case (userAction::fold):    qDebug() << "Player folded";            return m_userAction;
        case (userAction::idle):    qDebug() << "Player idle";              return m_userAction;
        case (userAction::rise):    qDebug() << "Player rised";             return m_userAction;
        case (userAction::quit):    qDebug() << "Player quit";              return m_userAction;
        default:      qDebug() << this << " user action not recognized";    return m_userAction;
    }
    return m_userAction;
}

void Player::actAway()
{
    qDebug() << this << " away";
    m_userAction = userAction::away;
    emit fold();
    p_TimeClick = new QTime();
    p_TimeClick->start();
    if(p_TimeClick->elapsed() > 180000)
    {
        m_userAction = userAction::quit;
        p_TimeClick->~QTime();
        emit fold();
    }
}

int Player::actCall()
{
    qDebug() << this << " call";
    m_userAction = userAction::call;
    if(!p_TimeClick)
        p_TimeClick->~QTime();
    m_stake = *p_stake;
    if(m_stake < m_wallet)
    {
        m_wallet = m_wallet - m_stake;
        emit bet(m_stake);
        return m_stake;
    }
    else
    {
        emit bet(m_wallet);
        return m_wallet;
    }

}

void Player::actCheck()
{
    qDebug() << this << " check";
    m_userAction = userAction::check;
    if(!p_TimeClick)
        p_TimeClick->~QTime();
    emit bet(0);

}

void Player::actFold()
{
    qDebug() << this << " fold";
    if(!p_TimeClick)
        p_TimeClick->~QTime();
    emit fold();
    m_userAction = userAction::fold;
    m_stake = 0;
    m_playerHand.card_A = 101;
    m_playerHand.card_B = 101;

}

void Player::actIdle()
{
    m_userAction = userAction::idle;
    qDebug() << this << " idle";
}

int Player::actRise(const int& arg)
{
    qDebug() << this << " rise";
    m_userAction = userAction::rise;
    if(!p_TimeClick)
        p_TimeClick->~QTime();
    m_stake = arg;
    if(m_stake < m_wallet)
    {
        m_wallet = m_wallet - m_stake;
        if(*p_stake < m_stake)
        {
            *p_stake = m_stake;
        }
        emit bet(m_stake);
        return m_stake;
    }
    else
    {
        if(*p_stake < m_wallet)
        {
            *p_stake = m_wallet;
        }
        emit bet(m_stake);
        return m_wallet;
    }

    return arg;
}

void Player::actQuit()
{
    m_userAction = userAction::quit;
    if(!p_TimeClick)
        p_TimeClick->~QTime();
    qDebug() << this << " quit";
}
