#pragma once
#include "Global.h"

#include "Novel/Action/Audio/ActionAudio.h"

#include "Novel/Data/Audio/MusicPlaylist.h"

#include "Novel/Data/Asset/Type/AssetMusic.h"
#include "Novel/Data/Asset/AssetManager.h"

///Changes background Music played along the Scene
class ActionChangeMusic final : public ActionAudio
{
public:
	ActionChangeMusic() = default;
	ActionChangeMusic(AudioSettings settings, QVector<QString>&& musicAssetsNames, bool bRandomize, bool bExclusive);
	ActionChangeMusic(double volume, double stereo, bool bLoop, uint delayBetweenReplays, 
					  QVector<QString>&& musicAssetsNames, bool bRandomize, bool bExclusive);
	ActionChangeMusic(const ActionChangeMusic& obj) { *this = obj; }
	ActionChangeMusic& operator=(const ActionChangeMusic& obj);

	///Executes this Action's logic
	void run() override;

	///Checks if the Action can load the `assetMusicPlaylist`
	//TODO:
	//  CHECK IF:
	//    - != ""
	//    - AssetManager::find != vector.end()
	//    - QFile::exists
	bool checkForErrors() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionChangeMusic(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(MusicPlaylist* musicPlaylist);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionChangeMusic; }

	///Ensures Assets are loaded and if not - loads them
	void ensureResourcesAreLoaded() override;

	///Names of the AssetMusics, so they can be loaded (if needed) and played
	QVector<QString> assetMusicNames;
	///AssetMusics to be played
	QVector<AssetMusic*> assetMusicPlaylist;

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




inline ActionChangeMusic::ActionChangeMusic(AudioSettings settings, QVector<QString>&& musicAssetsNames, bool bRandomize, bool bExclusive) :
	ActionAudio(settings), assetMusicNames(move(assetMusicNames)), bRandomize(bRandomize), bExclusive(bExclusive)
{
	for (const QString& name : this->assetMusicNames)
	{
		//Might throw an exception
		AssetMusic* asset = AssetManager::getInstance().findAssetMusic(name);
		assetMusicPlaylist.push_back(asset);
	}
}

inline ActionChangeMusic::ActionChangeMusic(double volume, double stereo, bool bLoop, uint delayBetweenReplays, 
											QVector<QString>&& musicAssetsNames, bool bRandomize, bool bExclusive) :
	ActionChangeMusic(AudioSettings(volume, stereo, (bLoop ? -1 : 1), delayBetweenReplays), (move(musicAssetsNames)), bRandomize, bExclusive)
{
}

inline ActionChangeMusic& ActionChangeMusic::operator=(const ActionChangeMusic& obj)
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	assetMusicNames = obj.assetMusicNames;
	assetMusicPlaylist = obj.assetMusicPlaylist;
	bRandomize = obj.bRandomize;
	bExclusive = obj.bExclusive;

	return *this;
}

inline void ActionChangeMusic::ensureResourcesAreLoaded()
{
	for (AssetMusic* assetMusic : assetMusicPlaylist)
		if (!assetMusic->isLoaded())
			assetMusic->load();
}