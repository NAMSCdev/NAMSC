#pragma once
#include "Global.h"

#include "Story/Action/Audio/ActionAudio.h"

#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

///Changes background Music played along while the Scene is displayed
class ActionPlaySound final : public ActionAudio
{
public:
	ActionPlaySound() = default;
	ActionPlaySound(Event *parent, unsigned actionID, double volume, double stereo,
					int timesPlayed, QString &&label, QString &&soundAssetName, bool bPersistToNewEvent) :
		ActionAudio(parent, actionID, stereo, volume, timesPlayed, move(label)), 
		soundAssetName(move(soundAssetName)), bPersistToNewEvent(bPersistToNewEvent) 
	{
		soundAsset = AssetManager::getInstance().findSoundAsset(this->soundAssetName);
	}
	ActionPlaySound(const ActionPlaySound& obj) {
		*this = obj;
	}
	ActionPlaySound& operator=(const ActionPlaySound& obj) {
		if (this == &obj) return *this;

		ActionAudio::operator=(obj);
		soundAssetName = obj.soundAssetName;
		soundAsset = obj.soundAsset;
		bPersistToNewEvent = obj.bPersistToNewEvent;
		
		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor *visitor) override { visitor->visitActionPlaySound(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(AudioSettings settings, SoundAsset *soundAsset, bool bPersistToNewEvent);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionPlaySound; }

	///Ensures Assets are loaded and if not - loads them
	void ensureAssetsAreLoaded() override { if (!soundAsset->isLoaded()) soundAsset->load(); }

	///Name of the SoundAsset, so it can be loaded (if needed) and played
	QString soundAssetName;
	///SoundsAsset to be played
	SoundAsset *soundAsset = nullptr;

	///Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	///@todo implement this
	bool bPersistToNewEvent = false;
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};