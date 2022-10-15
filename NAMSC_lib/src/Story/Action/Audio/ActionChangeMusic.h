#pragma once
#include "Global.h"

#include "Story/Action/Audio/ActionAudio.h"

#include "Story/Data/Audio/MusicPlaylist.h"

#include "Story/Data/Asset/Type/AssetMusic.h"
#include "Story/Data/Asset/AssetManager.h"

///Changes background Music played along the Scene
class ActionChangeMusic final : public ActionAudio
{
public:
	ActionChangeMusic() = default;
	ActionChangeMusic(Event *parent, unsigned actionID, QVector<QString> &&musicAssetsNames, double volume, double stereo,
					 bool bLoop, bool bRandomize, bool bExclusive, QString &&label) :
		ActionAudio(parent, actionID, volume, stereo, (bLoop ? -1 : 1), move(label)), musicAssetsNames(move(musicAssetsNames)), 
		bRandomize(bRandomize), bExclusive(bExclusive)
	{ 
		for (const QString &name : this->musicAssetsNames) 
		{
			//Might throw an exception
			AssetMusic* asset = AssetManager::getInstance().findMusicAsset(name);
			musicAssets.push_back(asset);
		}
	}
	ActionChangeMusic(const ActionChangeMusic& obj) { *this = obj; }
	ActionChangeMusic& operator=(const ActionChangeMusic& obj)
	{
		if (this == &obj) return *this;

		ActionAudio::operator=(obj);
		musicAssetsNames = obj.musicAssetsNames;
		musicAssets      = obj.musicAssets;
		bRandomize       = obj.bRandomize;
		bExclusive       = obj.bExclusive;

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionChangeMusic(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(MusicPlaylist* musicPlaylist);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionChangeMusic; }

	///Ensures Assets are loaded and if not - loads them
	void ensureAssetsAreLoaded() override		
	{ 
		for (AssetMusic *musicAsset : musicAssets) 
			if (!musicAsset->isLoaded()) 
				musicAsset->load();
	}

	///Names of the MusicAssets, so they can be loaded (if needed) and played
	QVector<QString> musicAssetsNames;
	///MusicAssets to be played
	QVector<AssetMusic*>musicAssets;

	///[low optional] Whether to randomize Music order
	bool bRandomize = false;

	///[low optional] Whether every Music should be played at least once
	bool bExclusive	= false;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};