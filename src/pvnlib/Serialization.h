#pragma once

#include <QDataStream>

//[polish personal note; optional todo] Teoretycznie moglibysmy w Serializacji na samym poczatku zliczyc rozmiar calej struktury, tak ze jak wystapi blad przy wczytywaniu jednego obiektu z pliku, to dalo sie wczytac reszte (przeskoczyc znacznikiem do miejsca, gdzie jest nastepny obiekt). Mozna dodac kompresje zapisow

namespace NovelLib
{
    enum class SerializationID
    {
        Invalid                             = 0, 
        ActionAudioSetMusic                 = 1, 
        ActionAudioSetSounds                = 2, 
        ActionStatVisibility                = 3, 
        ActionStatSetValue                  = 4, 
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
        ActionLive2DModelChange             = 16,
        ActionSceneryObjectAnimColor        = 17,
        ActionSceneryObjectAnimMove         = 18,
        ActionSceneryObjectAnimRotate       = 19,
        ActionSceneryObjectAnimScale        = 20,
        ActionSceneryObjectAnimFade         = 21,
        ActionCharacterSetVoice             = 22,
        ActionSceneryObjectSetImage         = 23,
        ActionSetBackground                 = 24,
        SceneryBackgroundAssetImage         = 25,
        SceneryObjectPartAssetImage         = 26,
        StatString                          = 27,
        StatLongLong                        = 28,
        StatDouble                          = 29,
        EventRenPyScript                    = 30,
        EventChoice                         = 31,
        EventDialogue                       = 32,
        EventEndIf                          = 33,
        EventIf                             = 34,
        EventInput                          = 35,
        EventJump                           = 36,
        EventWait                           = 37
    };
}

/// Serialization loading
template<typename T>
concept SerializableLoad = requires(QDataStream& dataStream, T& t)
{
    t.serializableLoad(dataStream);
};

template<SerializableLoad T>
QDataStream& operator>>(QDataStream& dataStream, T& t)
{
    t.serializableLoad(dataStream);
    return dataStream;
}

/// Serialization saving
template<typename T>
concept SerializableSave = requires(QDataStream& dataStream, T& t)
{
    t.serializableSave(dataStream);
};

template<SerializableSave T>
QDataStream& operator<<(QDataStream& dataStream, const T& t)
{
    t.serializableSave(dataStream);
    return dataStream;
}