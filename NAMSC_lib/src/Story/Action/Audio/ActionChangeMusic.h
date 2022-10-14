#pragma once
#include "Global.h"

#include "Story/Action/Audio/ActionAudio.h"

#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

///Changes background Music played along the Scene
class ActionChangeMusic final : public ActionAudio
{
public:
	ActionChangeMusic() = default;
	ActionChangeMusic(	Event *parent, unsigned actionID, QVector<QString> &&musicAssetsNames, double volume, double stereo,
						bool bLoop, bool bRandomize, bool bExclusive, QString &&label) :
		ActionAudio(parent, actionID, volume, stereo, (bLoop ? -1 : 1), move(label)), musicAssetsNames(move(musicAssetsNames)), 
		bRandomize(bRandomize), bExclusive(bExclusive)
	{ 
		for (const QString &name : this->musicAssetsNames) 
		{
			//Might throw an exception
			MusicAsset* asset = AssetManager::getInstance().findMusicAsset(name);
			musicAssets.push_back(asset);
		}
	}
	ActionChangeMusic(const ActionChangeMusic& asset)				= default;
	ActionChangeMusic& operator=(const ActionChangeMusic& asset)	= default;

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionChangeMusic(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(AudioSettings settings, QVector<MusicAsset*> musicAssets, bool bRandomized, bool bExclusive);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	{ return SerializationID::ActionChangeMusic; }

	///Ensures Assets are loaded and if not - loads them
	void ensureAssetsAreLoaded() override		
	{ 
		for (MusicAsset *musicAsset : musicAssets) 
			if (!musicAsset->isLoaded()) 
				musicAsset->load();
	}

	///Names of the MusicAssets, so they can be loaded (if needed) and played
	QVector<QString>	musicAssetsNames;
	///MusicAssets to be played
	QVector<MusicAsset*>musicAssets;

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