#ifndef CANMESSAGE_H
#define CANMESSAGE_H
#include <QtCore>
#include <QDebug>

/** класс, представляющий CAN-пакет. Содержит в себе бинарные данные и удобные функции доступа к этим данным.
 * Множество методов getXXX() и setXXX предоставляют удобный интерфейс для работы с данным классом.
 * Внутри этих функций проверяется возможность установки или получения данных из заданных позиций исходя из lenght
 * Функция @ref toString() возвращает удобное строковое представление пакета в HEX-е.
 * TODO пока что данные оставленны открытыми для удобства создания новых пакетов. Иначе бы пришлось писать много
 * сеттеров/геттеров для всех данных класса.
 * TODO сделать таки функции переинициализации..
 */
class CanMessage
{
public:
    /// время прихода сообщения (msec)
    quint32 timeStamp;
    /// ID сообщения
    quint32 id;
    /// длинна сообщения
    quint8 lenght;
    /// данные сообщения
    quint8 data[8];

public:

    /**
     * Конструктор. В случае initData == 0, заполняет нолями
     * @param initId ID пакета. по умолчанию ноль.
     * @param initLenght длинна пакета. Если задана более 8, то выведется предупреждение и обрезается до 8
     * @param initData тело сообщения. Если не задано - заполняется нолями.
     * @param initTimeStamp врменная метка.
     */
    CanMessage( quint32 initId = 0, quint8 initLenght = 0,
                const char* initData  = 0, quint32 initTimeStamp = 0);

//    /**
//     * Конструктор. В случае initArray.size < 8, заполняет недостающие данные нолями
//     * @param initId ID пакета. по умолчанию ноль.
//     * @param initLenght длинна пакета. Если задана более 8, то выведется предупреждение и обрезается до 8
//     * @param initArray тело сообщения. Если размерность меньше 8 - заполняется нолями.
//     * @param initTimeStamp врменная метка.
//     */
//    CanMessage( quint32 initId = 0, quint8 initLenght = 0,
//                const QByteArray& initArray  = QByteArray(), quint32 initTimeStamp = 0);

//    /**
//     * переинициализирует данные пакета.
//     * @param initId ID пакета. по умолчанию ноль.
//     * @param initLenght длинна пакета. Если задана более 8, то выведется предупреждение и обрезается до 8
//     * @param initData тело сообщения. Если не задано - заполняется нолями.
//     * @param initTimeStamp врменная метка.
//     */
//    void reInit(quint32 initId = 0, quint8 initLenght = 0,
//                const char* initData  = 0, quint32 initTimeStamp = 0);

//    /**
//     * переинициализирует данные пакета.
//     * @param initId ID пакета. по умолчанию ноль.
//     * @param initLenght длинна пакета. Если задана более 8, то выведется предупреждение и обрезается до 8
//     * @param initArray тело сообщения. Если размерность меньше 8 - заполняется нолями.
//     * @param initTimeStamp врменная метка.
//     */
//    void reInit( quint32 initId = 0, quint8 initLenght = 0,
//                const QByteArray& initArray  = QByteArray(), quint32 initTimeStamp = 0);


    /// строковое представление сообщения. предназначено для отладки.
    /// @return строковое представление пакета
    QString toString() const;

    /**
     * Функция получения 32 битного знакового целого из пакета. При невозможности чтения выводится сообщение на консоль
     * @param pos - номер байта данных, начиная с которого находится данный параметр.
     * @return 32 битный целочисленный параметр.
     */
    qint32 getInt32(quint8 pos = 0) const;


    /**
     * Функция получения 16 битного знакового числа из пакета. При невозможности чтения выводится сообщеие на консоль
     * @param pos Номер байта, начиная с которого лежит данное параметр
     * @return 16 битный целочисленный параметр.
     */
    qint16 getInt16(quint8 pos = 0) const;

    /**
     * Функция получения 8 битного знакового числа из пакета. При невозможности чтения выводится сообщение на консоль
     * @param pos Номер байта, начиная с которого находится данный параметр
     * @return 8 битный целочисленный параметр.
     */
    qint8 getInt8(quint8 pos = 0) const;

    /**
     * Функция получения 32 битного беззнакового числа из пакета. При невозможности чтения выводится сообщение в консоль
     * @param pos Номер байта, начиная с которого находится данный параметр
     * @return 32 битный беззнаковый параметр.
     */
    quint32 getUInt32(quint8 pos = 0) const;

    /**
     * Функция получения 16 битного беззнакового числа из пакета. При невозможности чтения выводится сообщение в консоль
     * @param pos Номер байта, начиная с которого находится данный параметр.
     * @return 16 битный беззнаковый параметр.
     */
    quint16 getUInt16(quint8 pos = 0) const;

    /**
     * Функция получения беззнакового числа из пакета. При невозможности чтения выводится сообщение в консоль
     * @param pos Номер бита, в котором находится данное число
     * @return 8 битное беззнаковое число.
     */
    quint8 getUInt8(quint8 pos = 0) const;

    /**
     * Функция получения булевского значения из пакета. При невозможности чтения выводится сообщение в консоль
     * @param byte номер байта в пакете, из которого необходимо получить данный параметр
     * @param bit Номер бита в байте, из которого необходимо получить данный параметр
     * @return булевское значение.
     */
    bool getBit(quint8 byte, quint8 bit) const;

    /**
     * Функция получения последовательности бит из пакета. Максимум 32 бита.
     * Применяется для чтения значений перечислений. При невозможности чтения выводится сообщение в консоль.
     * @param startByte стартовый байт последовательности в пакете
     * @param startBit стартовый бит последовательности в пакете
     * @param len колличество бит для чтения
     * @return 32 битное целое, в старших разрядах которого находятся прочитанные биты.
     */
    quint32 getEnum(quint8 len, quint8 startByte, quint8 startBit) const;

    /**
     * Функция получения последовательности бит из пакета. Максимум 32 бита.
     * Применяется для чтения последовательности флагов. При невозможности чтения выводится сообщение в консоль.
     * @param startByte стартовый байт последовательности в пакете
     * @param startBit стартовый бит последовательности в пакете
     * @param len колличество бит для чтения
     * @return 32 битное целое, в старших разрядах которого находятся прочитанные биты.
     */
    QBitArray getBits(quint8 len, quint8 startByte, quint8 startBit) const;


    /**
     * Функция установки 8 битного знакового числа на заданное место в сообщении
     * @param val - значение параметра для устрановки
     * @param pos - номер байта сообщения, в который нужно установить данное значение.
     */
    void setInt8 ( qint8 val, quint8 pos);

    /**
     * Функция установки 16 битного знакового числа на заданное место в сообщении
     * @param val - значение параметра для установки
     * @param pos номер стартового байта сообщения для записи.
     */
    void setInt16( qint16 val, quint8 pos);

    /**
     * Функция установки 32 битного знакового числа на заданное место в сообщении.
     * @param val значение параметра для установки
     * @param pos номер стартового байта для установки.
     */
    void setInt32( qint32 val, quint8 pos);

    /**
     * Функция установки 8 битного беззнакового числа на заданное место в сообщении
     * @param val - значение параметра для устрановки
     * @param pos - номер байта сообщения, в который нужно установить данное значение.
     */
    void setUInt8 ( quint8 val, quint8 pos);

    /**
     * Функция установки 16 битного беззнакового числа на заданное место в сообщении
     * @param val - значение параметра для установки
     * @param pos номер стартового байта сообщения для записи.
     */
    void setUInt16( quint16 val, quint8 pos);

    /**
     * Функция установки 16 битного беззнакового числа на заданное место в сообщении
     * @param val - значение параметра для установки
     * @param pos номер стартового байта сообщения для записи.
     */
    void setUInt32( quint32 val, quint8 pos);

    /**
     * Функция установки флага в сообщение.
     * @param val - значение флага для установки
     * @param byte номер байта для записи
     * @param bit позиция бита в байте для записи
     */
    void setBit (bool val, quint8 byte, quint8 bit);

    /**
     * Функция установки значения перечисления. Максимум 32 бита.
     * @param val значение для записи.
     * @param len колличество бит для записи
     * @param startByte стартовый байт для записи
     * @param startBit позиция стартового бита для записи
     */
    void setEnum(quint32 val, quint8 len, quint8 startByte, quint8 startBit);

    /**
     * Функция установки последовательности бит.
     * @param val последовательность бит для записи
     * @param startByte стартовый байт
     * @param startBit стартовый бит
     */
    void setBits(const QBitArray& val, quint8 startByte, quint8 startBit);
};

#endif // CANMESSAGE_H
