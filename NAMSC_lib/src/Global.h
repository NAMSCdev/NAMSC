#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <thread>

#include <QtCore/qglobal.h>
#include <QObject>
#include <QString>
#include <QFont>
#include <QImage>
#include <QPair>
#include <QTimer>
#include <QMediaPlayer>
#include <QFile>
#include <QFlags>

#include "Story/Evaluators.h"
#include "Exceptions.h"
#include "Story/Data/StorySettings.h"

enum class SerializationID
{
    ActionChangeMusic               = 0,
    ActionPlaySound                 = 1,
    ActionStatViibility             = 2,
    ActionStatChange                = 3,
    ActionEffectBlur                = 4,
    ActionEffectDistort             = 5,
    ActionEffectGlow                = 6,
    ActionFilterBlur                = 7,
    ActionFilterBrightness          = 8,
    ActionFilterDilation            = 9,
    ActionFilterErosion             = 10,
    ActionFilterHue                 = 11,
    ActionFilterNegative            = 12,
    ActionFilterSaturation          = 13,
    ActionCharLive2DAnim            = 14,
    ActionSceneryObjectAnim         = 15,
    ActionSceneryObjectApperance    = 16,
    ActionSceneryChange             = 17,
    ActionSceneryObjectChange       = 18,
    AnimAsset                       = 19,   //TODO: fix this
    FontAsset                       = 20,
    Live2DAnimAsset                 = 21,
    Live2DCharacterModelAsset       = 22,
    MusicAsset                      = 23,
    SceneryBackgroundImageAsset     = 24,
    SceneryObjectPartImageAsset     = 25,
    SoundAsset                      = 26,
    StorySave                       = 27,
    TextAsset                       = 28,
    //TODO: fill this list with the rest of the IDs, once they become certain they are needed and implicit serialization cannot be done

};

template <class T>
using uPtr = std::unique_ptr<T>;
using std::move;

//Serialization loading
template<typename T>
concept SerializableLoad = requires(QIODevice  &device, T const &t)
{
    t.serializableLoad(device);
};
template<SerializableLoad T>
QIODevice &operator>>(QIODevice &device, T &t)
{
    t.serializableLoad(device);
    return device;
}

//Serialization saving
template<typename T>
concept SerializableSave = requires(QIODevice  &device, T const &t)
{
    t.serializableSave(device);
};
template<SerializableSave T>
QIODevice &operator<<(QIODevice &device, const T &t)
{
    t.serializableSave(device);
    return device;
}