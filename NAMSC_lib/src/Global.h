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
    ActionSceneryObjectAnimMove     = 16,
    ActionSceneryObjectAnimScale    = 17,
    ActionSceneryObjectAnimRotate   = 18,
    ActionSceneryObjectAnimColor    = 19,
    ActionSceneryObjectHide         = 20,
    ActionSceneryObjectShow         = 21,
    ActionSceneryObjectChange       = 22,   
    ActionSetBackground             = 23,
    Live2DAnimAsset                 = 24,
    Live2DCharacterModelAsset       = 25,
    AnimAsset                       = 26,
    FontAsset                       = 27,
    ImageAsset                      = 28,
    MusicAsset                      = 29,
    SceneryBackgroundImageAsset     = 30,
    SceneryObjectPartImageAsset     = 31,
    SoundAsset                      = 32,
    TextAsset                       = 33,
    StatString                      = 34,
    StatBool                        = 35,
    StatLongLong                    = 36,
    StatDouble                      = 37,
    InsertionSound                  = 38,
    Sentence                        = 39,
    Translation                     = 40,
    Voice                           = 41,
    AnimatorEffect                  = 42,
    AnimatorFilter                  = 43,
    AnimatorTransform               = 44,
    Character                       = 45,
    Scenery                         = 46
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
