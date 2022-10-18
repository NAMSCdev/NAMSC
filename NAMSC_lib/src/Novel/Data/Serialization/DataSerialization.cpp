#pragma once
#include "Novel/Data/Novel.h"
#include "Novel/Data/Asset/AssetManager.h"

#include "Novel/Data/Save/NovelState.h"

#include "Novel/Data/Audio/AudioSettings.h"
#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Audio/MusicPlaylist.h"

#include "Novel/Data/Text/Sentence.h"
#include "Novel/Data/Text/Translation.h"
#include "Novel/Data/Text/Voice.h"

#include "Novel/Data/Stat/Stat.h"

#include "Novel/Data/Visual/Animation/AnimNode.h"
#include "Novel/Data/Visual/Animation/AnimatorBase.h"
#include "Novel/Data/Visual/Animation/AnimatorInterface.h"
#include "Novel/Data/Visual/Animation/AnimatorTransform.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"
#include "Novel/Data/Visual/Scenery/Character.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

//------SAVE

void NovelState::serializableLoad(QDataStream &dataStream)
{
    uint statsSize = 0;
    dataStream >> saveSlot >> sceneID >> eventID >> date >> image >> statsSize;
    for (uint i = 0; i != statsSize; ++i)
    {
        Stat* stat = nullptr;
        switch (stats[i]->getType())
        {
            case SerializationID::StatString:
                stat = new StatString();
            case SerializationID::StatBool:
                stat = new StatBool();
                break;
            case SerializationID::StatLongLong:
                stat = new StatLongLong();
                break;
            case SerializationID::StatDouble:
                stat = new StatDouble();
                break;
            default:
                error(("Could not find a Stat's type: " + std::to_string((int)stats[i]->getType()) + '!').c_str());
                break;
        }
        dataStream >> *stat;
        stats.emplace_back(stat);
    }
}

void NovelState::serializableSave(QDataStream &dataStream) const
{
    dataStream << saveSlot << sceneID << eventID  << date << image << stats.size();
    for (const uPtr<Stat> &stat : stats)
        dataStream << *(stat.get());
}

//-----TEXT
//This constructor is a special guest here, because it needs to grab a Voice from Novel, which is impossible in header file due to looping
void Translation::serializableLoad(QDataStream& dataStream)
{
    uint translationsSize;
    dataStream >> translationsSize;

    for (uint i = 0; i != translationsSize; ++i)
    {
        QPair<QString, AssetText> pair;
        dataStream >> pair;
        translations.insert(pair.first, pair.second);
    }
}

void Translation::serializableSave(QDataStream& dataStream) const
{
    dataStream << SerializationID::Translation << translations.size();
    for (auto it = translations.constKeyValueBegin(); it != translations.constKeyValueEnd(); ++it)
        dataStream << *it;
}

Sentence::Sentence(Translation &&content, QString &&voiceName, uint cps, bool bEndWithInput, double waitBeforeContinueTime) : 
    content(move(content)), voiceName(move(voiceName)), cps(cps), bEndWithInput(bEndWithInput), waitBeforeContinueTime(waitBeforeContinueTime)
{
    voice = Novel::getInstance().findVoice(this->voiceName);
}

void Sentence::serializableLoad(QDataStream &dataStream)
{
    dataStream >> content >> voiceName >> cps >> bEndWithInput >> waitBeforeContinueTime;
    
    voice = Novel::getInstance().findVoice(voiceName);
}

void Sentence::serializableSave(QDataStream &dataStream) const
{
    dataStream << SerializationID::Sentence << content << voiceName << cps << bEndWithInput << waitBeforeContinueTime;
}

void Voice::serializableLoad(QDataStream& dataStream)
{
    dataStream >> fontAssetName >> fontSize >> bold >> italic >> underscore >> color >> alignment >> lipSync;
}

void Voice::serializableSave(QDataStream& dataStream) const
{
    dataStream << SerializationID::Voice << fontAssetName << fontSize << bold << italic << underscore << color << alignment << lipSync;
}

//-----AUDIO

void AudioSettings::serializableLoad(QDataStream& dataStream)
{
    dataStream >> volume >> stereo >> timesPlayed >> delayBetweenReplays;
}

void AudioSettings::serializableSave(QDataStream& dataStream) const
{
    dataStream << volume << stereo << timesPlayed << delayBetweenReplays;
}

void Sound::serializableLoad(QDataStream& dataStream)
{
    dataStream >> soundAssetName >> bPersistToNewEvent >> settings;
}

void Sound::serializableSave(QDataStream& dataStream) const
{
    dataStream << soundAssetName << bPersistToNewEvent << settings;
}

void MusicPlaylist::serializableLoad(QDataStream& dataStream)
{
    uint musicNamesSize;
    dataStream >> musicNamesSize;
    for (uint i = 0u; i != musicNamesSize; ++i)
    {
        QString name;
		dataStream >> name;
		musicAssetsNames.push_back(name);

		AssetMusic *asset = AssetManager::getInstance().findAssetMusic(name);
		musicAssets.push_back(asset);
	}
	dataStream >> bRandomize >> bExclusive >> settings;
}

void MusicPlaylist::serializableSave(QDataStream& dataStream) const
{
    uint musicNamesSize;
    dataStream << musicAssetsNames.size();
    for (const QString& name : musicAssetsNames)
        dataStream << name;
    dataStream << bRandomize << bExclusive << settings;
}

//-----ANIM

void AnimNodeBase::serializableLoad(QDataStream& dataStream)
{
    dataStream >> timeStamp >> interpolationMethod;
}

void AnimNodeBase::serializableSave(QDataStream& dataStream) const
{
    dataStream << timeStamp << interpolationMethod;
}

template<uint dimension>
void AnimNodeDouble<dimension>::serializableLoad(QDataStream& dataStream)
{
    AnimNodeBase::serializableLoad(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream >> state[dimension];
}

template<uint dimension>
void AnimNodeDouble<dimension>::serializableSave(QDataStream& dataStream) const
{
    AnimNodeBase::serializableSave(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream << state[dimension];
}

template<uint dimension>
void AnimNodeLongLong<dimension>::serializableLoad(QDataStream& dataStream)
{
    AnimNodeBase::serializableLoad(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream >> state[dimension];
}

template<uint dimension>
void AnimNodeLongLong<dimension>::serializableSave(QDataStream& dataStream) const
{
    AnimNodeBase::serializableSave(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream << state[dimension];
}

void AnimatorInterface::serializableLoad(QDataStream& dataStream)
{
    dataStream >> startTime >> speed >> timesPlayed >> animAssetName;
}

void AnimatorInterface::serializableSave(QDataStream& dataStream) const
{
    dataStream << startTime << speed << timesPlayed << animAssetName;
}

void AnimatorSceneryObjectInterface::serializableLoad(QDataStream& dataStream)
{
    AnimatorInterface::serializableLoad(dataStream);
    dataStream >> sceneryObjectName;

    sceneryObject = Novel::getInstance().findSceneryObject();
}

void AnimatorSceneryObjectInterface::serializableSave(QDataStream& dataStream) const
{
    AnimatorInterface::serializableSave(dataStream);
    dataStream << sceneryObjectName;
}

void AnimatorMove::serializableLoad(QDataStream& dataStream)
{
    AnimatorSceneryObject<AnimNodeDouble2D>::serializableLoad(dataStream);
    
    animAsset = AssetManager::getInstance().findAssetAnimMove(animAssetName);
}

void AnimatorScale::serializableLoad(QDataStream& dataStream)
{
    AnimatorSceneryObject<AnimNodeDouble2D>::serializableLoad(dataStream);
    
    animAsset = AssetManager::getInstance().findAssetAnimScale(animAssetName);
}

void AnimatorRotate::serializableLoad(QDataStream& dataStream)
{
    AnimatorSceneryObject<AnimNodeDouble1D>::serializableLoad(dataStream);
    
    animAsset = AssetManager::getInstance().findAssetAnimRotate(animAssetName);
}

void AnimatorColor::serializableLoad(QDataStream& dataStream)
{
    AnimatorSceneryObject<AnimNodeDouble4D>::serializableLoad(dataStream);
    
    animAsset = AssetManager::getInstance().findAssetAnimColor(animAssetName);
}

//-----STATS

void Stat::serializableLoad(QDataStream& dataStream)
{
    dataStream >> name >> displayName >> bShow >> priority >> showNotification;
}

void Stat::serializableSave(QDataStream& dataStream) const
{
    dataStream << getType() << name << displayName << bShow << priority << showNotification;
}

void StatString::serializableLoad(QDataStream& dataStream)
{
    Stat::serializableLoad(dataStream);
    dataStream >> value >> maxChars;
}

void StatString::serializableSave(QDataStream& dataStream) const
{
    Stat::serializableSave(dataStream);
    dataStream << value << maxChars;
}

void StatBool::serializableLoad(QDataStream& dataStream)
{
    Stat::serializableLoad(dataStream);
    dataStream >> value;
}

void StatBool::serializableSave(QDataStream& dataStream) const
{
    Stat::serializableSave(dataStream);
    dataStream << value;
}

void StatLongLong::serializableLoad(QDataStream& dataStream)
{
    Stat::serializableLoad(dataStream);
    dataStream >> value >> min >> max;
}

void StatLongLong::serializableSave(QDataStream& dataStream) const
{
    Stat::serializableSave(dataStream);
    dataStream << value << min << max;
}

void StatDouble::serializableLoad(QDataStream& dataStream)
{
    Stat::serializableLoad(dataStream);
    dataStream >> value >> min >> max;
}

void StatDouble::serializableSave(QDataStream& dataStream) const
{
    Stat::serializableSave(dataStream);
    dataStream << value << min << max;
}

//-----VISUAL
void SceneryObject::serializableLoad(QDataStream& dataStream)
{
    dataStream >> pos >> scale >> rotation >> color >> label >> imageAssetName;
    
    imageAsset = AssetManager::getInstance().findSceneryObjectAssetImage(imageAssetName);
}
    
void SceneryObject::serializableSave(QDataStream& dataStream) const
{
    dataStream << pos << scale << rotation << color << label << imageAssetName;
}

//This constructor is a special guest here, because it needs to grab a Voice from Novel, which is impossible in header file due to looping
Character::Character(QString&& defaultVoiceName) :
    defaultVoiceName(move(defaultVoiceName))
{
    defaultVoice = Novel::getInstance().findVoice(this->defaultVoiceName);
}

void Character::serializableLoad(QDataStream& dataStream)
{
    SceneryObject::serializableLoad(dataStream);
    dataStream >> defaultVoiceName;
    
    defaultVoice = Novel::getInstance().findVoice(this->defaultVoiceName);
}

void Character::serializableSave(QDataStream& dataStream) const
{
    SceneryObject::serializableSave(dataStream);
    dataStream << defaultVoiceName;
}

void Scenery::serializableLoad(QDataStream& dataStream)
{
}

void Scenery::serializableSave(QDataStream& dataStream) const
{

}