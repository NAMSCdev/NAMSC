#pragma once
#include "Global.h"

#include "Novel/Action/Audio/ActionAudio.h"

#include "Novel/Data/Audio/Sound.h"

#include "Novel/Data/Asset/Type/AssetSound.h"
#include "Novel/Data/Asset/AssetManager.h"

///Changes background Music played along while the Scene is displayed
class ActionPlaySound final : public ActionAudio
{
public:
	ActionPlaySound() = default;
	ActionPlaySound(AudioSettings settings, QVector<QString>&& soundAssetName, bool bPersistToNewEvent);
	ActionPlaySound(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, 
					QVector<QString>&& soundAssetName, bool bPersistToNewEvent);
	ActionPlaySound(const ActionPlaySound& obj) { *this = obj; }
	ActionPlaySound& operator=(const ActionPlaySound& obj);

	///Executes this Action's logic
	void run() override;

	///Checks if the Action can load the `assetSoundList`
	bool checkForErrors() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionPlaySound(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Sound* sound);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionPlaySound; }

	///Ensures Assets are loaded and if not - loads them
	void ensureResourcesAreLoaded() override;
	
	///Names of the AssetSounds, so they can be loaded (if needed) and played
	QVector<QString> assetSoundNames;
	///SoundsAsset to be played
	QVector<AssetSound*> assetSoundList;

	///Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	///@todo implement this
	bool bPersistToNewEvent = false;
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};




inline ActionPlaySound::ActionPlaySound(AudioSettings settings, QVector<QString>&& soundAssetName, bool bPersistToNewEvent) :
	ActionAudio(settings), assetSoundNames(move(assetSoundNames)), bPersistToNewEvent(bPersistToNewEvent)
{
	for (QString& soundAssetName : this->assetSoundNames)
		this->assetSoundList.push_back(AssetManager::getInstance().findAssetSound(soundAssetName));
}

inline ActionPlaySound::ActionPlaySound(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, QVector<QString>&& soundAssetName, bool bPersistToNewEvent) :
	ActionPlaySound(AudioSettings(volume, stereo, timesPlayed, delayBetweenReplays), move(assetSoundNames), bPersistToNewEvent)
{
}

inline ActionPlaySound& ActionPlaySound::operator=(const ActionPlaySound& obj)
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	assetSoundNames = obj.assetSoundNames;
	assetSoundList = obj.assetSoundList;
	bPersistToNewEvent = obj.bPersistToNewEvent;

	return *this;
}

inline void ActionPlaySound::ensureResourcesAreLoaded()
{ 
	for (AssetSound* assetSound : assetSoundList)
		if (!assetSound->isLoaded())
			assetSound->load();
}
