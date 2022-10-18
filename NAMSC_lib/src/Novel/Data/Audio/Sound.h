#pragma once
#include "Global.h"

#include "Novel/Data/Audio/AudioSettings.h"

#include "Novel/Data/Asset/AssetManager.h"

class Sound 
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Sound&);
	friend QDataStream& operator<<(QDataStream&, const Sound&);
public:
	Sound() = default;
	Sound(QString &&soundAssetName, bool bPersistToNewEvent, double volume, double stereo, int timesPlayed, uint delay) :
		soundAssetName(move(soundAssetName)), bPersistToNewEvent(bPersistToNewEvent), settings(volume, stereo, timesPlayed, delay)
	{
		soundAsset = AssetManager::getInstance().findAssetSound(this->soundAssetName);
	}
	Sound(Sound& obj) { *this = obj; }
	Sound& operator=(const Sound& obj) 
	{
		if (this == &obj) return *this;

		soundAssetName     = obj.soundAssetName;
		soundAsset         = obj.soundAsset;
		bPersistToNewEvent = obj.bPersistToNewEvent;
		settings           = obj.settings;

		return *this;
	}

	///Tries to load an AssetSound
	void load()		{ if (!soundAsset->isLoaded()) soundAsset->load(); player = soundAsset->getSoundPlayer(); }

	///Returns whether the asset is currently loaded
	bool isLoaded() { return player != nullptr; }
	
	///todo: describe
	QMediaPlayer* player;

private:
	///Name of the AssetSound, so it can be loaded (if needed) and played
	QString soundAssetName;
	///SoundsAsset to be played
	AssetSound* soundAsset;

	///Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	///@todo implement this
	bool bPersistToNewEvent = false;
	
	uint timestamp = 0;

	///Common properties of Actions that manage Audio
	AudioSettings settings;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};