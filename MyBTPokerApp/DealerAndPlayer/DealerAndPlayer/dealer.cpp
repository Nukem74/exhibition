#include "dealer.h"
#include "strategy_topkit.h"
struct Kit
{
    Kit() : p_Player(nullptr)
    {
        qDebug() << "Kit()";
        m_Kit.reserve(7);
    }
    Kit(Player* p) : p_Player(p)
    {
        qDebug() << "Kit(Player*)";
        m_Kit.reserve(7);
        Hand* temp = new Hand(p->getHand());
        m_Kit.push_back(temp->card_A);
        m_Kit.push_back(temp->card_B);
        std::sort(m_Kit.begin(), m_Kit.end());
        delete temp;
    }
    Kit(const Kit& arg) : p_Player(arg.p_Player), m_Kit(arg.m_Kit) , m_rank(arg.m_rank)
    {
        qDebug() << "Kit(const Kit&)";
    }
    ~Kit()
    {
        p_Player = nullptr;
        m_Kit.clear();
    }
    void setTable(QVector<int>* cards)
    {
        QVector<int>::iterator it = cards->begin();
        while(it != cards->end())
        {
            m_Kit.push_back(*it);
            it++;
        }
        std::sort(m_Kit.begin(), m_Kit.end());
    }
    void setRank()
    {
        QVector<int>::iterator it = m_Kit.begin();
        while(it != m_Kit.end())
        {
            qDebug() << *it;
            it++;
        }
        m_rank = getRank(m_Kit.begin(), m_Kit.end());
    }
    Player* p_Player;
    QVector<int> m_Kit;
    QString m_rank;
};

Dealer::Dealer(Player* place, QVector <Player>* p_Vect, QVector<int>* p_Table, const int& sBlind, int *pStake)   : m_smallBlind(sBlind)
                                                                                                                , p_stake(pStake)
                                                                                                                , p_dealingPlayer(place)        //
                                                                                                                , uPtr_playersVector(p_Vect)
                                                                                                                , p_gamingTable(p_Table)        //
                                                                                                                , p_gameDeck(nullptr)           //
                                                                                                                                                //
{                                                                                                                                               //

    qDebug() << "Dealer(4 args)";                                                                                                               //
    p_gameDeck = new Deck();                                                                                                                    //
    m_numPlayers = uPtr_playersVector->size();                                                                                                  //
    //m_numPlayers = uPtr_playersVector->size();
    //setBlind(sBlind);

}

Dealer::Dealer(const Dealer& arg)   : m_numPlayers(arg.m_numPlayers)
                                    , m_smallBlind(arg.m_smallBlind)                                                                            //
                                    , m_bigBlind(arg.m_bigBlind)                                                                                //
                                    , m_rebuyValue(arg.m_rebuyValue)                                                                            //
                                    , p_stake(arg.p_stake)                                                                                      //
                                    , p_dealingPlayer(arg.p_dealingPlayer)                                                                      //
                                    , uPtr_playersVector(arg.uPtr_playersVector.get())                                                          //
                                    , p_gamingTable(arg.p_gamingTable)                                                                          //
                                    , p_gameDeck(arg.p_gameDeck)                                                                                //
{                                                                                                                                               //

}

Dealer::~Dealer()                                                                                                                               //
{                                                                                                                                               //
    p_dealingPlayer = nullptr;                                                                                                                  //
    if(uPtr_playersVector)
        uPtr_playersVector.release();                                                                                                           //
    p_gameDeck = nullptr;                                                                                                                       //
    m_numPlayers = 0;                                                                                                                           //
    p_gamingTable = nullptr;                                                                                                                    //
}

void Dealer::servePlayers()                                                                                                                     //
{                                                                                                                                               //
    qDebug() << "Dealer::servePlayers";                                                                                                         //
    if(m_numPlayers > 1)                                                                                                                        //
    {                                                                                                                                           //
        p_gameDeck->selectCards(m_numPlayers);                                                                                                  //
        QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                             //
        while(it != uPtr_playersVector->end())                                                                                                  //
        {                                                                                                                                       //
            it->setCard(p_gameDeck->getCard());                                                                                                 //
            it++;                                                                                                                               //
        }                                                                                                                                       //
        it = uPtr_playersVector->begin();                                                                                                       //
        while(it != uPtr_playersVector->end())                                                                                                  //
        {                                                                                                                                       //
            it->setCard(p_gameDeck->getCard());                                                                                                 //
            it++;                                                                                                                               //
        }                                                                                                                                       //
    }                                                                                                                                           //
}

int Dealer::getPlayers()
{
    return m_numPlayers;
}

void Dealer::showPlayersHands()                                                                                                                 //
{                                                                                                                                               //
    QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                                 //
    while(it != uPtr_playersVector->end())                                                                                                      //
    {                                                                                                                                           //
        it->showHand();                                                                                                                         //
        it++;                                                                                                                                   //
    }                                                                                                                                           //
}                                                                                                                                               //

void Dealer::serveTable()                                                                                                                       //
{                                                                                                                                               //
                                                                                                                                                //
    p_gamingTable->push_back(p_gameDeck->getCard());                                                                                            //
                                                                                                                                                //
    this->showTable();                                                                                                                          //
}

void Dealer::showTable()                                                                                                                        //
{                                                                                                                                               //
    qDebug() << "Table contents";                                                                                                               //
    QVector<int>::iterator it = p_gamingTable->begin();                                                                                         //
    while(it != p_gamingTable->end())                                                                                                           //
    {                                                                                                                                           //
        qDebug() << *it;                                                                                                                        //
        it++;                                                                                                                                   //
    }                                                                                                                                           //
}

void Dealer::setBlind(const int& arg)                                                                                                           //
{                                                                                                                                               //
    qDebug() << "Dealer::setBlind()";                                                                                                           //
    m_smallBlind = arg;                                                                                                                         //
    m_bigBlind = 2 * m_smallBlind;                                                                                                              //
    m_rebuyValue = 1000 * m_bigBlind;                                                                                                           //
}
//Round managment=============================================================================================================================

void Dealer::updatePlayers()                                                                                                                    //
{                                                                                                                                               //
    qDebug() << "Dealer::updatePlayers()";                                                                                                      //
    QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                                 //
    while(it != uPtr_playersVector->end())                                                                                                      //
    {                                                                                                                                           //
        switch (it->getUserAction())                                                                                                            //
        {                                                                                                                                       //
            case (userAction::away) :   it->actAway();  break;                                                                                  //
            case (userAction::call) :   it->actIdle();  break;                                                                                  //
            case (userAction::check):   it->actIdle();  break;                                                                                  //
            case (userAction::fold) :   it->actAway();  break;                                                                                  //
            case (userAction::idle) :   it->actIdle();  break;                                                                                  //
            case (userAction::rise) :   it->actIdle();  break;                                                                                  //
            case (userAction::quit) :                                                                                                           //
                                        {                                                                                                       //
                                            uPtr_playersVector->removeOne(*it);                                                                 //
                                            m_numPlayers--;                                                                                     //
                                            break;                                                                                              //
                                        }                                                                                                       //
            default                 :   {                                                                                                       //
                                            qDebug() << &it << " player action not recognized";                                                 //
                                            break;                                                                                              //
                                        }                                                                                                       //
        }                                                                                                                                       //
        it++;                                                                                                                                   //
    }
    if(m_numPlayers == 1)
    {
        declareWinner(&uPtr_playersVector->first());
        finishRound();
    }
}

void Dealer::throwBlinds()                                                                                                                      //
{                                                                                                                                               //
    qDebug() << "Dealer::throwBlinds()";                                                                                                        //
    QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                                 //
    if(uPtr_playersVector->size() == 2)                                                                                                         //
    {                                                                                                                                           //
        it->actRise(m_bigBlind);                                                                                                                //
        it->actIdle();                                                                                                                          //
        it++;                                                                                                                                   //
        it->actRise(m_smallBlind);                                                                                                              //
        it->actIdle();                                                                                                                          //
        *p_stake = m_bigBlind;
        return;                                                                                                                                 //
    }
    else                                                                                                                                        //
    {                                                                                                                                           //
        it++;                                                                                                                                   //
        it->actRise(m_smallBlind);                                                                                                              //
        it->actIdle();                                                                                                                          //
        it->actRise(m_bigBlind);                                                                                                                //
        it->actIdle();                                                                                                                          //
        *p_stake = m_bigBlind;
    }
}

void Dealer::startTrade()                                                                                                                       //
{                                                                                                                                               //
    qDebug() << "Dealer::startTrade()";                                                                                                         //
    updatePlayers();
    QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                                 //
    //repeat checking while everybody's stake isn't equal or maximal !recurently!
    while(it != uPtr_playersVector->end())                                                                                                      //
    {                                                                                                                                           //
        if(it->getUserAction() == userAction::idle)
        {
            this->demandAction(it);
        }                                                                                                            //
        it++;                                                                                                                                   //
    }                                                                                                                                           //
//check for winner in the end of round
}

void Dealer::demandAction(Player* p)                                                                                                            //
{                                                                                                                                               //
    qDebug() << "Dealer::demandAction(" << this << ")";                                                                                         //
    std::mutex m;                                                                                                                               //
    m.lock();                                                                                                                                   //
    QTime now;                                                                                                                                  //
    now.start();                                                                                                                                //
    while((p->getUserAction() == userAction::idle) &&  (now.elapsed() < 2000))                                                                  //
    {                                                                                                                                           //
        qDebug() << now.elapsed() << " sec elapsed";                                                                                            //
    }                                                                                                                                           //
    m.unlock();                                                                                                                                 //
    if(p->getUserAction() == userAction::idle)                                                                                                  //
    {                                                                                                                                           //
        p->actAway();                                                                                                                           //
        qDebug() << "Player away";                                                                                                              //
    }                                                                                                                                           //
    return;                                                                                                                                     //
}

Player* Dealer::findTopKit()
{
    qDebug() << "Dealer::findTopKit()";
    QList<Kit> kitList;
    QVector<Player>::iterator it = uPtr_playersVector->begin();
    while(it != uPtr_playersVector->end())
    {
        Kit* K = new Kit(it);
        K->setTable(p_gamingTable);
        K->setRank();
        kitList.push_back(*K);
        it++;
    }

    QList<Kit>::iterator iKit = kitList.begin();
    QString rankTag = "R";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "H";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "Q";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "";
    while(iKit != kitList.end())
    {
        if(-1 != iKit->m_rank.indexOf("TP"))
            return iKit->p_Player;

        if(-1 != iKit->m_rank.indexOf("PT"))
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "F";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "S";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }

    iKit = kitList.begin();
    rankTag = "K";
    while(iKit != kitList.end())
    {
        if(rankTag != iKit->m_rank)
            return iKit->p_Player;

        iKit++;
    }
    qDebug() << "Top Kit Not Found";
    return nullptr;
}

void Dealer::declareWinner(Player* p)
{
    qDebug() << "Dealer::declareWinner( "<< p << " )";
    p->showHand();
    p->collectPrize(1);
}

void Dealer::finishRound()                                                                                                                      //
{                                                                                                                                               //
    qDebug() << "Dealer::finishRound()";
    updatePlayers();
    *p_stake = 0;
    QVector<Player>::iterator it = uPtr_playersVector->begin();                                                                                 //
    while(it != uPtr_playersVector->end())                                                                                                      //
    {                                                                                                                                           //
        it->resetCard();
        it->newOrder((it->getOrder() + 1) % uPtr_playersVector->size());                                                                        //
        qDebug() << "finishRound() " << it->getOrder();                                                                                         //
        it++;                                                                                                                                   //
    }                                                                                                                                           //
}                                                                                                                                               //



//Play Dealer method==========================================================================================================================
void Player::playDealer()                                                                                                                       //
{                                                                                                                                               //
    qDebug() << "Player::playDealer()";                                                                                                         //
    p_dealer = new Dealer(this,uPtr_playersVector.release(), p_gamingTable,m_sBlind,p_stake);                                                   //

    //Preflop trading
    p_dealer->updatePlayers();                                                                                                                  //
    p_dealer->servePlayers();                                                                                                                   //
    p_dealer->serveTable();
    p_dealer->serveTable();
    p_dealer->serveTable();
    p_dealer->serveTable();
    p_dealer->serveTable();
    p_dealer->declareWinner(p_dealer->findTopKit());
    /*p_dealer->setBlind(m_sBlind);
    p_dealer->throwBlinds();                                                                                                                    //
    int tempStake = *p_stake;
    while(tempStake != *p_stake)
    {
        p_dealer->startTrade();
    }
    if(p_dealer->getPlayers() == 1)
    {
        p_dealer->declareWinner(&uPtr_playersVector->first());
    }
    //Flop trading
    *p_stake = 0;
    tempStake = *p_stake;
    p_dealer->updatePlayers();
    for(int i = 0; i < 3; i++)
    {
        p_dealer->serveTable();
    }
    while(tempStake != *p_stake)
    {
        p_dealer->startTrade();
    }
    if(p_dealer->getPlayers() == 1)
    {
        p_dealer->declareWinner(&uPtr_playersVector->first());
    }
    //River trading
    *p_stake = 0;
    tempStake = *p_stake;
    p_dealer->updatePlayers();
    p_dealer->serveTable();
    while(tempStake != *p_stake)
    {
        p_dealer->startTrade();
    }
    if(p_dealer->getPlayers() == 1)
    {
        p_dealer->declareWinner(&uPtr_playersVector->first());
    }
    //Turn trading
    *p_stake = 0;
    tempStake = *p_stake;
    p_dealer->updatePlayers();
    p_dealer->serveTable();
    while(tempStake != *p_stake)
    {
        p_dealer->startTrade();
    }
    if(p_dealer->getPlayers() == 1)
    {
        p_dealer->declareWinner(&uPtr_playersVector->first());
    }
    //findWiningCombo
    p_dealer->finishRound();

*/
    delete p_dealer;
    p_dealer = nullptr;
    //qDebug() << "playDealer end";
}
