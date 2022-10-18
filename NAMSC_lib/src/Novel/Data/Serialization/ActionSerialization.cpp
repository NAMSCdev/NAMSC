#include "Global.h"
#include "Novel/Action/ActionsAll.h"

//Very ulgy collection of Serialization code
//Especially when there will be support for backwards compability

Action& Action::operator=(const Action& obj)
{
	if (this == &obj) return *this;

	label = obj.label;

	return *this;
}

void Action::serializableLoad(QDataStream &dataStream)
{
	dataStream >> label;
}

void Action::serializableSave(QDataStream &dataStream) const
{
	dataStream << getType() << label;
}

//-----AUDIO

void ActionAudio::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> settings.volume >> settings.stereo >> settings.timesPlayed;
}

void ActionAudio::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << settings.volume << settings.stereo << settings.timesPlayed;
}

void ActionChangeMusic::serializableLoad(QDataStream &dataStream) 
{
	ActionAudio::serializableLoad(dataStream);
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
	dataStream >> bRandomize >> bExclusive;
}

void ActionChangeMusic::serializableSave(QDataStream &dataStream) const
{
	ActionAudio::serializableSave(dataStream);
	dataStream << musicAssetsNames.size();
	for (const QString &name : musicAssetsNames)
		dataStream << name;
	dataStream << bRandomize << bExclusive;
}

void ActionPlaySound::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> soundAssetName >> bPersistToNewEvent;
	soundAsset = AssetManager::getInstance().findAssetSound(soundAssetName);
}


void ActionPlaySound::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << soundAssetName << bPersistToNewEvent;
}

//-----STAT

void ActionStat::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> statName;

	stat = Novel::getInstance().getNovelState()->getStat(statName); 
}

void ActionStat::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << statName;
}

void ActionStatHide::serializableLoad(QDataStream &dataStream)
{
	ActionStat::serializableLoad(dataStream);
}

void ActionStatHide::serializableSave(QDataStream &dataStream) const
{
	ActionStat::serializableSave(dataStream);
}

void ActionStatVisibility::serializableLoad(QDataStream &dataStream)
{
	ActionStat::serializableLoad(dataStream);
}

void ActionStatVisibility::serializableSave(QDataStream &dataStream) const
{
	ActionStat::serializableSave(dataStream);
}

void ActionStatChange::serializableLoad(QDataStream &dataStream)
{
	ActionStat::serializableLoad(dataStream);
	dataStream >> expression;
}

void ActionStatChange::serializableSave(QDataStream &dataStream) const
{
	ActionStat::serializableSave(dataStream);
	dataStream << expression;
}

//-----SCENERY_OBJECT

void ActionSceneryObject::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> sceneryObjectName;
	sceneryObject = Novel::getInstance().findSceneryObject(sceneryObjectName); 
}

void ActionSceneryObject::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << sceneryObjectName;
}

void ActionSceneryObjectImageChange::serializableLoad(QDataStream &dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> imageAssetName;
	imageAsset = AssetManager::getInstance().findSceneryObjectAssetImage(imageAssetName);
}

void ActionSceneryObjectImageChange::serializableSave(QDataStream &dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << imageAssetName;
}

//-----ANIM
template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableLoad(QDataStream &dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> animName >> speed >> bLoop;
}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableSave(QDataStream &dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << animName << speed << bLoop;
}

void ActionCharLive2DAnim::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> characterName >> animAssetName >> bSyncWithSpeech >> duration;
}

void ActionCharLive2DAnim::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << characterName << animAssetName << bSyncWithSpeech << duration;
}


void ActionSceneryObjectVisibilityChange::serializableLoad(QDataStream &dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> appearEffectType >> duration >> bAppear >> bPerserveAnimation;
}

void ActionSceneryObjectVisibilityChange::serializableSave(QDataStream &dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << appearEffectType << duration << bAppear << bPerserveAnimation;
}

//-----EFFECT

void ActionEffect::serializableLoad(QDataStream &dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> effectShape >> pos >> size >> strength;
}

void ActionEffect::serializableSave(QDataStream &dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << effectShape << pos << size << strength;
}

void ActionEffectBlur::serializableLoad(QDataStream &dataStream)
{
	ActionEffect::serializableLoad(dataStream);
	dataStream >> blurType;
}

void ActionEffectBlur::serializableSave(QDataStream &dataStream) const
{
	ActionEffect::serializableSave(dataStream);
	dataStream << blurType;
}

void ActionEffectDistort::serializableLoad(QDataStream &dataStream)
{
	ActionEffect::serializableLoad(dataStream);
}

void ActionEffectDistort::serializableSave(QDataStream &dataStream) const
{
	ActionEffect::serializableSave(dataStream);
}

void ActionEffectGlow::serializableLoad(QDataStream &dataStream)
{
	ActionEffect::serializableLoad(dataStream);
}

void ActionEffectGlow::serializableSave(QDataStream &dataStream) const
{
	ActionEffect::serializableSave(dataStream);
}

//-----FILTER

void ActionFilter::serializableLoad(QDataStream &dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> intensivness >> strength;
}

void ActionFilter::serializableSave(QDataStream &dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << intensivness << strength;
}

void ActionFilterBlur::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
	dataStream >> blurType;
}

void ActionFilterBlur::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
	dataStream << blurType;
}

void ActionFilterBrightness::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
	dataStream >> addedBrightness >> percentBrightness;
}

void ActionFilterBrightness::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
	dataStream << addedBrightness << percentBrightness;
}

void ActionFilterDilation::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
}

void ActionFilterDilation::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
}

void ActionFilterErosion::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
}

void ActionFilterErosion::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
}

void ActionFilterHue::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
	dataStream >> hueShift;
}

void ActionFilterHue::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
	dataStream << hueShift;
}

void ActionFilterNegative::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
}

void ActionFilterNegative::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
}

void ActionFilterSaturation::serializableLoad(QDataStream &dataStream)
{
	ActionFilter::serializableLoad(dataStream);
	dataStream >> addedSaturation >> percentSaturation;
}

void ActionFilterSaturation::serializableSave(QDataStream &dataStream) const
{
	ActionFilter::serializableSave(dataStream);
	dataStream << addedSaturation << percentSaturation;
}

//-----OTHER

void ActionSetBackground::serializableLoad(QDataStream &dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> backgroundAssetName >> transitionType >> transitionTime/* >> themeName*/;
}

void ActionSetBackground::serializableSave(QDataStream &dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << backgroundAssetName << transitionType << transitionTime/* << themeName*/;
}