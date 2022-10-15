#pragma once
#include "Global.h"

#include "Story/Action/Audio/ActionAudio.h"

#include "Story/Data/Audio/Sound.h"

#include "Story/Data/Asset/Type/AssetSound.h"
#include "Story/Data/Asset/AssetManager.h"

///Changes background Music played along while the Scene is displayed
class ActionPlaySound final : public ActionAudio
{
public:
	ActionPlaySound() = default;
	ActionPlaySound(unsigned actionID, double volume, double stereo,
					int timesPlayed, QString&& label, QVector<QString>&& soundAssetName, bool bPersistToNewEvent) :
		ActionAudio(actionID, stereo, volume, timesPlayed, move(label)), 
		soundAssetNames(move(soundAssetNames)), bPersistToNewEvent(bPersistToNewEvent)
	{
		for (QString &soundAssetName : this->soundAssetNames)
			this->soundAssets.push_back(AssetManager::getInstance().findAssetSound(soundAssetName));
	}
	ActionPlaySound(const ActionPlaySound& obj) { *this = obj; }
	ActionPlaySound& operator=(const ActionPlaySound& obj) 
	{
		if (this == &obj) return *this;

		ActionAudio::operator=(obj);
		soundAssetNames    = obj.soundAssetNames;
		soundAssets        = obj.soundAssets;
		bPersistToNewEvent = obj.bPersistToNewEvent;
		
		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionPlaySound(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Sound* sound);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::ActionPlaySound; }

	///Ensures Assets are loaded and if not - loads them
	void ensureAssetsAreLoaded() override		{ for (AssetSound* soundAsset: soundAssets) if (!soundAsset->isLoaded()) soundAsset->load(); }

	///Names of the AssetSounds, so they can be loaded (if needed) and played
	QVector<QString> soundAssetNames;
	///SoundsAsset to be played
	QVector<AssetSound*> soundAssets;

	///Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	///@todo implement this
	bool bPersistToNewEvent = false;
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};