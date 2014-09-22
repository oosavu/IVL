#include "canmessage.h"



CanMessage::CanMessage(quint32 initId, quint8 initLenght, const char *initData, quint32 initTimeStamp)
{
    timeStamp = initTimeStamp;
    id = initId;
    lenght = initLenght;
    if(initData) memcpy(data, initData,8);
    else memset(data, 0, 8);
}

QString CanMessage::toString() const
{
    QString res;
    res.append(QString::number(id) + ' ');
    res.append(QString::number(lenght) + ' ');
    for(int i = 0; i < lenght; i++)
        res.append(QString::number(data[i],16).rightJustified(2,'0').toUpper() + " ");
    return  res;
}

qint32 CanMessage::getInt32(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 4);

    return  *reinterpret_cast<const qint32*>(&data[pos]);
}

qint16 CanMessage::getInt16(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 2);
    return *reinterpret_cast<const qint16*>(&data[pos]);
}

qint8 CanMessage::getInt8(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 1);
    return *reinterpret_cast<const qint8*>(&data[pos]);
}

quint32 CanMessage::getUInt32(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 4);
    return *reinterpret_cast<const quint32*>(&data[pos]);
}

quint16 CanMessage::getUInt16(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 2);
    return *reinterpret_cast<const quint16*>(&data[pos]);
}

quint8 CanMessage::getUInt8(quint8 pos) const
{
    Q_ASSERT(pos <= lenght - 1);
    return *reinterpret_cast<const quint8*>(&data[pos]);
}

bool CanMessage::getBit(quint8 byte, quint8 bit) const
{
    Q_ASSERT(byte <= lenght - 1);
    return data[byte] & (0x1 << bit);
}

quint32 CanMessage::getEnum(quint8 len, quint8 startByte, quint8 startBit) const
{
    Q_ASSERT((startByte*8 + len + startBit < lenght*8) || (len < 20));
    return ((*reinterpret_cast<const quint32*>(&data[startByte])) << startBit) >> (32 -len);
}

QBitArray CanMessage::getBits(quint8 len, quint8 startByte, quint8 startBit) const
{
    Q_ASSERT(startByte + (len + startBit) % 8 + 1 < lenght);
    QBitArray res(len);
    for(int i = 0; i < len; i ++)
    {
        res[i] = getBit(startByte + (i + startBit)/8, (i + startBit) % 8);
    }
    return res;
}

void CanMessage::setInt8(qint8 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 1);
    *reinterpret_cast<qint8*>(&data[pos]) = val;
}

void CanMessage::setInt16(qint16 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 2);
    *reinterpret_cast<qint16*>(&data[pos]) = val;
}

void CanMessage::setInt32(qint32 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 4);
    *reinterpret_cast<qint32*>(&data[pos]) = val;
}

void CanMessage::setUInt8(quint8 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 1);
    *reinterpret_cast<quint8*>(&data[pos]) = val;
}

void CanMessage::setUInt16(quint16 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 2);
    *reinterpret_cast<quint16*>(&data[pos]) = val;
}

void CanMessage::setUInt32(quint32 val, quint8 pos)
{
    Q_ASSERT(pos <= lenght - 4);
    *reinterpret_cast<quint32*>(&data[pos]) = val;
}

void CanMessage::setBit(bool val, quint8 byte, quint8 bit)
{
    Q_ASSERT(byte <= lenght - 1);
    Q_ASSERT(bit < 8);
    data[byte] = (data[byte] & ~(1<<bit))| (val<<bit);
}

void CanMessage::setEnum(quint32 val, quint8 len, quint8 startByte, quint8 startBit)
{
    qDebug()<<(!val & (0xFFFFFFFF <<  len));
    qDebug()<<(val & (0xFFFFFFFF <<  len));
    Q_ASSERT((8*startByte +len + startBit + 1 <= lenght*8) || (len < 20) || (startBit <= 7));
    Q_ASSERT((~val & (0xFFFFFFFF <<  len)));
    quint32* temp = (reinterpret_cast<quint32*>(&data[startByte]));
    quint32 mask = ((0xFFFFFFFF<<(32 - startBit - len))>>startBit);
    *temp = (*temp & ~mask) | (mask & (val<<(32 - len - startBit)));
}

void CanMessage::setBits(const QBitArray &val, quint8 startByte, quint8 startBit)
{
    Q_ASSERT((startByte*8 + startBit + val.size() <= lenght)|| (startBit <= 7));
    for(int i = 0; i < val.size(); i ++)
        setBit(val[i],startByte + (startBit + i) / 8, i % 8);
}
