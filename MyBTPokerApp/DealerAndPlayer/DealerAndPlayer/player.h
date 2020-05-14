#ifndef PLAYER_H
#define PLAYER_H
/*
 * DESCRIPTION OF PLAYER CLASS
 * This is major class of poker app, it's inherited from QObject. It represents Players attributes, methods to manage Player's cards, order,  wallet, actions.
 * It relies on auxialry classes Hand and enum class userAction.
 * Player class provides methods for setting cards in Hand(setCard(int&), resetCard()), changing players order (getOrder(), setOrder(int&))
 * act over gaming table(getUserAction(), act****()) and throw signals of undertaken actions.
 * Also Player has pointer to Dealer class, which manages the flow of round. It's initialised when Player's order comes to 0.
*/
#include "deck.h"
#include "auxilary.cpp"


class Player : public QObject
{
    friend bool         operator > (const Player& arg1, const Player& arg2);
    friend bool         operator>= (const Player& arg1, const Player& arg2);
    friend bool         operator < (const Player& arg1, const Player& arg2);
    friend bool         operator <= (const Player& arg1, const Player& arg2);
    friend bool         operator== (const Player& arg1, const Player& arg2);
    Q_OBJECT
public:
    Player(/*QObject* pObj = nullptr*/);
    Player(int place, int* stake/*,QObject* pObj = nullptr*/);
    //Player(QVector<Player>* pVect ,QVector<int>* pTable, const int& sBlind, int place,QObject* pObj = nullptr);//sBlind should be a pointer to constant variable
    Player(iPlayer& arg/*, QObject* pObj = nullptr*/);
    ~Player();
    Player(const Player& arg/*, QObject* pObj = nullptr*/);
    Player              operator =(const Player& arg);
    bool                operator == (const Player& arg);

    void                setCard(const int& card);
    void                resetCard();
    void                showHand();//this has to be slot(or not?)
    Hand                getHand();
    void                playDealer();//defined in Dealer.h
    int                 getOrder();
    void                newOrder(const int& ref);
    void                increaseWallet(const int& arg);
    void                collectPrize(const int& arg);

    //users actions
    userAction          getUserAction();
    void                actAway();
    int                 actCall();
    void                actCheck();
    void                actFold();
    void                actIdle();
    int                 actRise(const int& arg);
    void                actQuit();

signals:
    void                bet(const int&);
    void                fold();
private:
    Hand                m_playerHand;
    int                 m_sBlind;
    int                 m_order;
    int                 m_stake;
    int                 m_wallet;
    int* const          p_stake;
    Dealer*             p_dealer;
    //QVector<Player>*    p_playersVect;
    std::unique_ptr<QVector<Player> > uPtr_playersVector;
    QTime*              p_TimeClick;
    QVector<int>*       p_gamingTable;
    userAction          m_userAction;
};






#endif // PLAYER_H
