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
    ActionSceneryObjectShow         = 20,
    ActionSceneryObjectChange       = 21,   
    ActionSetBackground             = 22,
    AssetLive2DAnim                 = 23,
    Live2DCharacterModelAsset       = 24,
    AnimAsset                       = 25,
    AssetFont                       = 26,
    AssetImage                      = 27,
    AssetMusic                      = 28,
    SceneryBackgroundImageAsset     = 29,
    SceneryObjectPartImageAsset     = 30,
    AssetSound                      = 31,
    TextAsset                       = 32,
    StatString                      = 33,
    StatBool                        = 34,
    StatLongLong                    = 35,
    StatDouble                      = 36,
    InsertionSound                  = 37,
    Sentence                        = 38,
    Translation                     = 39,
    Voice                           = 40,
    AnimatorEffect                  = 41,
    AnimatorFilter                  = 42,
    AnimatorTransform               = 43,
    Character                       = 44,
    Scenery                         = 45 
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
