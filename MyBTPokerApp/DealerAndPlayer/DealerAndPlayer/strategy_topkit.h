#ifndef STRATEGY_TOPKIT_H
#define STRATEGY_TOPKIT_H
#include <QCoreApplication>
#include <QString>
#include <QDebug>

bool validRange(int* const start, int* const end)
{
    if(end - start != 7)
    {
        qDebug() << "Hand is not valid";
        return false;
    }
    else
    {
        return true;
    }
}

QString checkFlashRoyal(int* const start, int* const end)
{
    int* sampleKitStart = start;
    QString retValue = "";
    bool temp = false;
    //int* veryStart = start;
    unsigned int count = 0;
    while(sampleKitStart != end)
    {
        for(int i = 8; i < 13;i++)
        {
            temp = (*sampleKitStart == i);
            if(temp)
            {
                ++count;
                break;
            }
        }
        sampleKitStart++;
    }

    if(count == 5)
        retValue = "R";

    temp = false;
    sampleKitStart = start;
    count = 0;
    while(sampleKitStart != end)
    {
        for(int i = 21; i < 26;i++)
        {
            temp = (*sampleKitStart == i);
            if(temp)
            {
                ++count;
                break;

            }
        }
        sampleKitStart++;
    }

    if(count == 5)
        retValue = "R";

    temp = false;
    sampleKitStart = start;
    count = 0;
    while(sampleKitStart != end)
    {
        for(int i = 34; i < 39;i++)
        {
            temp = (*sampleKitStart == i);
            if(temp)
            {
                ++count;
                break;
            }
        }
        sampleKitStart++;
    }

    if(count == 5)
        retValue = "R";

    temp = false;
    sampleKitStart = start;
    count = 0;
    while(sampleKitStart != end)
    {
        for(int i = 47; i < 52;i++)
        {
            temp = (*sampleKitStart == i);
            if(temp)
            {
                ++count;
                break;
            }
        }
        sampleKitStart++;
    }


    if(count == 5)
        retValue = "R";

    return retValue;
}

QString checkFlashStreet(int* const start, int* const end)
{
    QString retValue = "";
    int* sampleKitStart = start;
    int count = 0;
    while(sampleKitStart < end)
    {
        for(int i = 0; i < 13; i++)
        {
            if(*sampleKitStart == i)
            {
                count++;
                if(sampleKitStart + 1 > end)
                {
                    break;
                }
                else
                {
                    sampleKitStart++;
                }
                continue;
            }
            else
            {
                if(count == 5)
                {
                    retValue = "H";
                    return retValue;
                }
                else
                {
                    count = 0;
                    continue;
                }
            }
        }
        if(count == 5)
        {
            retValue = "H";
            return retValue;
        }
        sampleKitStart++;
    }

    sampleKitStart = start;
    count = 0;
    while(sampleKitStart < end)
    {
        for(int i = 13; i < 26; i++)
        {
            if(*sampleKitStart == i)
            {
                count++;
                if(sampleKitStart + 1 > end)
                {
                    break;
                }
                else
                {
                    sampleKitStart++;
                }
                continue;
            }
            else
            {
                if(count == 5)
                {
                    retValue = "H";
                    return retValue;
                }
                else
                {
                    count = 0;
                    continue;
                }
            }
        }
        if(count == 5)
        {
            retValue = "H";
            return retValue;
        }
        sampleKitStart++;
    }

    sampleKitStart = start;
    count = 0;
    while(sampleKitStart < end)
    {
        for(int i = 26; i < 39; i++)
        {
            if(*sampleKitStart == i)
            {
                count++;
                if(sampleKitStart + 1 > end)
                {
                    break;
                }
                else
                {
                    sampleKitStart++;
                }
                continue;
            }
            else
            {
                if(count == 5)
                {
                    retValue = "H";
                    return retValue;
                }
                else
                {
                    count = 0;
                    continue;
                }
            }
        }
        if(count == 5)
        {
            retValue = "H";
            return retValue;
        }
        sampleKitStart++;
    }

    sampleKitStart = start;
    count = 0;
    while(sampleKitStart < end)
    {
        for(int i = 39; i < 52; i++)
        {
            if(*sampleKitStart == i)
            {
                count++;
                if(sampleKitStart + 1 > end)
                {
                    break;
                }
                else
                {
                    sampleKitStart++;
                }
                continue;
            }
            else
            {
                if(count == 5)
                {
                    retValue = "H";
                    return retValue;
                }
                else
                {
                    count = 0;
                    continue;
                }
            }
        }
        if(count == 5)
        {
            retValue = "H";
            return retValue;
        }
        sampleKitStart++;
    }
    return retValue;
}

QString checkFlash(int* const start, int* const end)
{
    QString retValue = "";
    int* sampleKitStart = start;
    int hCount = 0;
    int dCount = 0;
    int sCount = 0;
    int cCount = 0;
    while(sampleKitStart != end)
    {
        if((*sampleKitStart >= 0) && (*sampleKitStart <= 12))
        {
            hCount++;
            sampleKitStart++;
            continue;
        }
        if((*sampleKitStart >= 12) && (*sampleKitStart <= 25))
        {
            dCount++;
            sampleKitStart++;
            continue;
        }
        if((*sampleKitStart >= 26) && (*sampleKitStart <= 38))
        {
            sCount++;
            sampleKitStart++;
            continue;
        }
        if((*sampleKitStart >= 39) && (*sampleKitStart <= 51))
        {
            cCount++;
            sampleKitStart++;
            continue;
        }
    }

    if(hCount > 4 || dCount > 4 || sCount > 4 || cCount > 4)
    {
        retValue = "F";
        return retValue;
    }
    return retValue;
}


QString checkMultiple(int* const start, int* const end)
{
    int* sampleKitStart = start;
    //int* sampleKitEnd = end;
    int count   = 0;
    QString check = "";
    for(int i = 0; i < 13; i++)
    {
        sampleKitStart = start;
        count = 0;
        while(sampleKitStart != end)
        {
            if(*sampleKitStart == i)
            {
                count++;
            }
            if(*sampleKitStart == i+13)
            {
                count++;
            }
            if(*sampleKitStart == i+26)
            {
                count++;
            }
            if(*sampleKitStart == i+39)
            {
                count++;
            }
            sampleKitStart++;
        }
        if(count == 2)
        {
            //std::cout << "Pair detected" << std::endl;
            check+="P";
        }
        if(count == 3)
        {
            //std::cout << "Set detected" << std::endl;
            check+="T";
        }
        if(count == 4)
        {
            //std::cout << "Square detected" << std::endl;
            check+="Q";
        }
    }
    return check;
}

QString checkStreet(int* const begin, int* const end)
{
    int* sampleKitStart = begin;
    //int* sampleKitEnd = end;
    int count   = 1;
    int temp = 0;
    QString retValue = "";
    for(int i = 0; i < 13; i++)
    {
        sampleKitStart = begin;
        temp = count;
        while(sampleKitStart != end)
        {
            if(		(*sampleKitStart) == (i)
                || 	(*sampleKitStart) == (13 + i)
                || 	(*sampleKitStart) == (26 + i)
                || 	(*sampleKitStart) == (39 + i))
            {
                count++;
                break;
            }
            sampleKitStart++;
        }
        if(temp == count)
        {
            //std::cout << "reset" << std::endl;
            count = 1;
        }
        if(count == 5)
            retValue = "S";
    }
    return retValue;
}

QString	checkKicker(int* const start, int* const end)
{
    QString retValue = "";
    int* sampleKitStart = start;
    for(int i = 12; i >= 0; i--)
    {
        sampleKitStart = start;
        while(sampleKitStart != end)
        {
            if((*sampleKitStart) == (i))
            {
                retValue += "K";
                return retValue;
            }
            if((*sampleKitStart) == (13 + i))
            {
                retValue += "K";
                return retValue;
            }
            if((*sampleKitStart) == (26 + i))
            {
                retValue += "K";
                return retValue;
            }
            if((*sampleKitStart) == (39 + i))
            {
                retValue += "K";
                return retValue;
            }
            sampleKitStart++;
        }
    }
    return "";
}

QString getRank(int* const start, int* const end)
{
    if(!validRange(start, end))
        return "invalid range";

    std::sort(start, end);
    int* sampleKitStart = start;
    QString retValue = "";
    if(retValue == "")
        retValue.append(checkFlashRoyal(sampleKitStart, end));
    if(retValue == "")
        retValue.append(checkFlashStreet(sampleKitStart, end));
    if(retValue == "")
        retValue.append(checkMultiple(sampleKitStart, end));
    if(retValue == "")
        retValue.append(checkFlash(sampleKitStart, end));
    if(retValue == "")
        retValue.append(checkStreet(sampleKitStart, end));
    if(retValue == "")
        retValue.append(checkKicker(sampleKitStart, end));

    qDebug() << retValue;
    return retValue;
}

#endif // STRATEGY_TOPKIT_H
