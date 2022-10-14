#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <typeinfo>

#include <QObject>
#include <QString>
#include <QFont>
#include <QImage>
#include <QPair>
#include <QTimer>
#include <QMediaPlayer>
#include <QFile>
#include <QFlags>
#include <QDate>
#include <QRawFont>
#include <QDataStream>
#include <QException>
#include <QMessageBox>
#include <QVector>
#include <QMap>

#include "Story/Evaluators.h"
#include "Exceptions.h"
#include "Story/Data/StorySettings.h"

enum class SerializationID
{
    ActionChangeMusic               = 0,
    ActionPlaySound                 = 1,
    ActionStatHide                  = 2, 
    ActionStatShow                  = 3, 
    ActionStatChange                = 4, 
    ActionEffectBlur                = 5, 
    ActionEffectDistort             = 6, 
    ActionEffectGlow                = 7, 
    ActionFilterBlur                = 8, 
    ActionFilterBrightness          = 9, 
    ActionFilterDilation            = 10,
    ActionFilterErosion             = 11,
    ActionFilterHue                 = 12,
    ActionFilterNegative            = 13,
    ActionFilterSaturation          = 14,
    ActionCharLive2DAnim            = 15,
    ActionSceneryObjectAnim         = 16,
    ActionSceneryObjectHide         = 17,
    ActionSceneryObjectShow         = 18,
    ActionSceneryObjectChange       = 19,   
    ActionSetBackground             = 20,
    Live2DAnimAsset                 = 21,
    Live2DCharacterModelAsset       = 22,
    AnimAsset                       = 23,
    FontAsset                       = 24,
    ImageAsset                      = 25,
    MusicAsset                      = 26,
    SceneryBackgroundImageAsset     = 27,
    SceneryObjectPartImageAsset     = 28,
    SoundAsset                      = 29,
    TextAsset                       = 30,
    StatString                      = 31,
    StatBool                        = 32,
    StatLongLong                    = 33,
    StatDouble                      = 34,
    InsertionSound                  = 35,
    Sentence                        = 36,
    Translation                     = 37,
    Voice                           = 38,
    AnimatorEffect                  = 39,
    AnimatorFilter                  = 40,
    AnimatorTransform               = 41,
    Character                       = 42,
    Scenery                         = 43
};

template <class T>
using uPtr = std::unique_ptr<T>;
using std::move;

///Serialization loading
template<typename T>
concept SerializableLoad = requires(QDataStream &dataStream, T const &t)
{
    t.serializableLoad(dataStream);
};
template<SerializableLoad T>
QDataStream &operator>>(QDataStream&, T &t)
{
    t.serializableLoad(dataStream);
    return dataStream;
}

///Serialization saving
template<typename T>
concept SerializableSave = requires(QDataStream &dataStream, T const &t)
{
    t.serializableSave(dataStream);
};
template<SerializableSave T>
QDataStream &operator<<(QDataStream &device, const T &t)
{
    t.serializableSave(dataStream);
    return dataStream;
}

template<class Type>
Type* findInArray(const QString &name, QVector<Type> &vector)
{
    auto element = std::find(vector.begin(), vector.end(), name);
    if (element == vector.end())
        error(QString(typeid(Type).name()) + " with a name \"" + name + "\" could not be found!");
    return &(*element);
}

template<class Type>
Type* findInuPtrArray(const QString &name, QVector<uPtr<Type>> &vector)
{
    auto element = std::find(vector.begin(), vector.end(), name);
    if (element == vector.end())
        error(QString(typeid(Type).name()) + " with a name \"" + name + "\" could not be found!");
    return element->get();
}
