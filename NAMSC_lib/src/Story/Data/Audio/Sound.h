#pragma once
#include "Global.h"
#include "Story/Data/Asset/AssetManager.h"
#include "Story/Data/Asset/Audio/AudioSettings.h"

class Sound {
public:
	Sound() = default;
	Sound(Sound& obj) {
		*this = obj;
	}
	Sound& operator=(const Sound& obj) {
		if (this == &obj) return *this;

		soundAssetName = obj.soundAssetName;
		soundAsset = obj.soundAsset;
		bPersistToNewEvent = obj.bPersistToNewEvent;

		return *this;
	}

	///Name of the AssetSound, so it can be loaded (if needed) and played
	QString soundAssetName = "";
	///SoundsAsset to be played
	AssetSound* soundAsset = nullptr;

	///Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	///@todo implement this
	bool bPersistToNewEvent = false;

	///Common properties of Actions that manage Audio
	AudioSettings settings;
};