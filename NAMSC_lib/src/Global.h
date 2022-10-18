#pragma once
#include <thread>
#include <typeinfo>

#include <QPlainTextEdit>

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

#include "Novel/Evaluators.h"
#include "Exceptions.h"
#include "Novel/Data/NovelSettings.h"

enum class SerializationID
{
    ActionChangeMusic                   = 0,
    ActionPlaySound                     = 1,
    ActionStatHide                      = 2, 
    ActionStatVisibility                      = 3, 
    ActionStatChange                    = 4, 
    ActionEffectBlur                    = 5, 
    ActionEffectDistort                 = 6, 
    ActionEffectGlow                    = 7, 
    ActionFilterBlur                    = 8, 
    ActionFilterBrightness              = 9, 
    ActionFilterDilation                = 10,
    ActionFilterErosion                 = 11,
    ActionFilterHue                     = 12,
    ActionFilterNegative                = 13,
    ActionFilterSaturation              = 14,
    ActionLive2DAnim                    = 15,
    ActionLive2DModelChange             = 16,   //placeholder
    ActionSceneryObjectAnimMove         = 17,
    ActionSceneryObjectAnimScale        = 18,
    ActionSceneryObjectAnimRotate       = 19,
    ActionSceneryObjectAnimColor        = 20,
    ActionSceneryObjectVisibilityChange = 21,
    ActionSceneryObjectImageChange      = 22,  
    ActionSceneryObjectVoiceChange      = 23,
    ActionSetBackground                 = 24,
    AssetLive2DAnim                     = 25,
    AssetLive2DModel                    = 26,
    AssetAnim                           = 27,
    AssetFont                           = 28,
    AssetImage                          = 29,
    AssetMusic                          = 30,
    SceneryBackgroundAssetImage         = 31,
    SceneryObjectPartAssetImage         = 32,
    AssetSound                          = 33,
    AssetText                           = 34,
    StatString                          = 35,
    StatBool                            = 36,
    StatLongLong                        = 37,
    StatDouble                          = 38,
    InsertionSound                      = 39,
    Sentence                            = 40,
    Translation                         = 41,
    Voice                               = 42,
    AnimatorEffect                      = 43,
    AnimatorFilter                      = 44,
    AnimatorTransform                   = 45,
    Character                           = 46,
    Scenery                             = 47,
    EventRenPyScript                    = 48,
    EventChoice                         = 49,
    EventEndIf                          = 50,
    EventIf                             = 51,
    EventInput                          = 52,
    EventJump                           = 53,
    EventNarrate                        = 54,
    EventSpeak                          = 55,
    EventWait                           = 56
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
