#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QObject>

#include <QTranslator>
#include <QGuiApplication>
#include <QTime>
/**
 * класс переводчика. является достаточно костыльным решением,  которое,
 * однако, найдено в официальной справке: http://qt-project.org/wiki/How_to_do_dynamic_translation_in_QML
 * Суть в том, что файлы перевода грузятся в среде С++, но необходимо динамический менять текст надписей в QML
 * Для этого из с++ расшаривается свойство "пустой строки". которое тригирирует  при изменении языка.
 * TODO возможно надо добавить много языков а не два, и так же каким то образом синхронизацию с ПЗУ.
 */
class TranslationManager : public QObject
{
    Q_OBJECT

    Q_ENUMS(languages)
    /// Свойство пустой строки. Необходимо  для динамического переключения языка в QML.
    /// Для этого к каждой строке для показа пользователю необходимо добавлять данную строку.
    Q_PROPERTY(QString tS READ getTS NOTIFY languageChanged)

    /// Свойство текущего языка интерфейса
    Q_PROPERTY(languages language READ getLanguage WRITE setLanguage NOTIFY languageChanged)

public:

    /// Перечисление возможных языков интерфейса
    enum languages{
        Rus = 0, ///< русский
        Eng = 1  ///< английский
    };

    /**
     * функция возвращения пустой строки.
     * @return пустую строку.
     */
    QString getTS(){return "";}
private:
    /// транслятор для русского
    QTranslator *translatorRU;
    /// транслятор для английского
    QTranslator *translatorEN;

    /// конструктор. По умолчанию включается русский.
    explicit TranslationManager(QObject *parent = 0);

    /// укозатель на объект. Нужен для реализации паттерна синглтон
    static TranslationManager* _self;
    languages m_language;

public:
    /// метод получения ссылки на объект
    static TranslationManager* instance();

    languages getLanguage() const
    {
        return m_language;
    }

public slots:
    /**
     * Функция установки языка интерфейса
     * @param arg - новый язык
     */
    void setLanguage(languages arg);

signals:
    /// сигнал, высылаемый при смене языка
    void languageChanged();
    
};

#endif // TRANSLATIONMANAGER_H
