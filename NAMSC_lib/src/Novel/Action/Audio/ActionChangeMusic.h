#pragma once
#include "Global.h"

#include "Novel/Action/Audio/ActionAudio.h"
#include "Novel/Data/Audio/MusicPlaylist.h"
#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectMusicAssetAudio;

/// Changes background Music played along the Scene
class ActionChangeMusic final : public ActionAudio
{
	friend ActionVisitorCorrectMusicAssetAudio;
public:
	ActionChangeMusic() noexcept = default;
	/// \exception Error Failed search for an AssetAudio (fetched by the AssetManager using `assetAudioNames`)
	ActionChangeMusic(AudioSettings settings, QVector<QString>&& assetAudioNames, bool stopCurrent, bool bRandomize, bool bExclusive);
	/// \exception Error Failed search for an AssetAudio (fetched by the AssetManager using `assetAudioNames`)
	ActionChangeMusic(double volume, double stereo, bool bLoop, uint delayBetweenReplays,
					  QVector<QString>&& assetAudioNames, bool stopCurrent, bool bRandomize, bool bExclusive);
	ActionChangeMusic(const ActionChangeMusic& obj) noexcept { *this = obj; }
	ActionChangeMusic& operator=(const ActionChangeMusic& obj) noexcept;

	/// Executes the ActionChangeMusic's logic
	void run() override;

	/// Checks if the ActionChangeMusic can load Resources associated with it
	bool checkForErrors() const override;

	/// Accepts an ActionVisitor
	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionChangeMusic(this); }

signals:
	/// A Qt signal emitted after the ActionChangeMusic's `void run()` allowing for data read
	/// \param musicPlaylist AssetAudio list of Music that overwrote the Scenery's one
	void onRun(const MusicPlaylist* musicPlaylist) const;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionChangeMusic; }

	/// Ensures Assets are loaded and if not - loads them
	void ensureResourcesAreLoaded() override;

	/// Whether we should stop the currently played Music or wait until it ends before switching to a new one from the assigned playlist
	bool stopCurrent = false;

	/// [optional] Whether to randomize Music order
	bool bRandomize = false;

	/// [optional] Whether every Music should be played at least once
	bool bExclusive	= false;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};



	
inline ActionChangeMusic::ActionChangeMusic(AudioSettings settings, QVector<QString>&& assetAudioNames, bool stopCurrent, bool bRandomize, bool bExclusive) :
	ActionAudio(settings, move(assetAudioNames)), stopCurrent(stopCurrent), bRandomize(bRandomize), bExclusive(bExclusive)
{
	for (const QString& name : this->assetAudioNames)
	{
		//Might throw an exception
		AssetAudio* asset = AssetManager::getInstance().findMusicAssetAudio(name);
		assetAudioList.push_back(asset);
	}
}

inline ActionChangeMusic::ActionChangeMusic(double volume, double stereo, bool bLoop, uint delayBetweenReplays, 
											QVector<QString>&& musicAssetsNames, bool stopCurrent, bool bRandomize, bool bExclusive) :
	ActionChangeMusic(AudioSettings(volume, stereo, (bLoop ? -1 : 1), delayBetweenReplays), (move(musicAssetsNames)), stopCurrent, bRandomize, bExclusive)
{
}

inline ActionChangeMusic& ActionChangeMusic::operator=(const ActionChangeMusic& obj)
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	stopCurrent = obj.stopCurrent;
	bRandomize  = obj.bRandomize;
	bExclusive  = obj.bExclusive;

	return *this;
}

inline void ActionChangeMusic::ensureResourcesAreLoaded()
{
	for (AssetAudio* assetMusic : assetAudioList)
		if (!assetMusic->isLoaded()) assetMusic->load();
}

inline bool ActionChangeMusic::checkForErrors() const
{
	try
	{
		const AssetManager& assetManager = AssetManager::getInstance();
		for (const QString& name : assetAudioNames)
		{
			//Check if name is undefined
			if (name == "")
			{
				qDebug() << "No AssetAudio assigned. Was it deleted and not replaced?";
				return true;
			}

			//Check if there is an object with this name in the AssetManager's container 
			const AssetAudio* assetAudio = assetManager.findMusicAssetAudio(name);
			if (assetAudio == nullptr)
			{
				qDebug() << "Music AssetAudio \"" + name + "\" not found by the AssetManager. Definition file might be corrupted.";
				return true;
			}

			//Check if the Asset is still there in the User's filesystem
			const QPair<bool, QString> fileExistence = assetAudio->checkFileExistence();
			if (!fileExistence.first)
			{
				qDebug() << "Could not find a file \"" + fileExistence.second + "\".";
				return true;
			}
		}
	}
	catch (...)
	{
		return true;
	}
	return false;
}