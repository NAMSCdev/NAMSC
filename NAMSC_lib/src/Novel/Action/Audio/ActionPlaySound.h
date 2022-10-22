#pragma once
#include "Global.h"

#include "Novel/Action/Audio/ActionAudio.h"
#include "Novel/Data/Audio/Sound.h"
#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectSoundAssetAudio;

/// Changes Sounds queued in the Scenery to be played at the right `timespan`
class ActionPlaySound final : public ActionAudio
{
	friend ActionVisitorCorrectSoundAssetAudio;
public:
	ActionPlaySound() noexcept = default;
	ActionPlaySound(AudioSettings settings, QVector<QString>&& assetAudioNames, bool bPersistToNewEvent);
	ActionPlaySound(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, 
					QVector<QString>&& assetAudioNames, bool bPersistToNewEvent);
	ActionPlaySound(const ActionPlaySound& obj) noexcept { *this = obj; }
	ActionPlaySound& operator=(const ActionPlaySound& obj) noexcept;

	/// Executes the ActionPlaySound's logic
	void run() override;

	/// Checks if the ActionPlaySound can load Resources associated with it
	bool checkForErrors() const override;

	/// Accepts an ActionVisitor
	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionPlaySound(this); }

signals:
	/// A Qt signal emitted after the ActionPlaySound's `void run()` allowing for data read
	/// \param sound AssetAudio list of Sounds that overwrote the Scenery's one
	void onRun(const QVector<Sound>* sound) const;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionPlaySound; }

	/// Ensures Assets are loaded and if not - loads them
	void ensureResourcesAreLoaded() override;
	
	/// [optional] Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	bool bPersistToNewEvent = false;
	
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline ActionPlaySound::ActionPlaySound(AudioSettings settings, QVector<QString>&& soundAssetName, bool bPersistToNewEvent) :
	ActionAudio(settings, move(assetAudioNames)), bPersistToNewEvent(bPersistToNewEvent)
{
	for (QString& soundAssetName : this->assetAudioNames)
		this->assetAudioList.push_back(AssetManager::getInstance().findSoundAssetAudio(soundAssetName));
}

inline ActionPlaySound::ActionPlaySound(double volume, double stereo, int timesPlayed, uint delayBetweenReplays, QVector<QString>&& assetAudioNames, bool bPersistToNewEvent) :
	ActionPlaySound(AudioSettings(volume, stereo, timesPlayed, delayBetweenReplays), move(assetAudioNames), bPersistToNewEvent)
{
}

inline ActionPlaySound& ActionPlaySound::operator=(const ActionPlaySound& obj)
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	bPersistToNewEvent = obj.bPersistToNewEvent;

	return *this;
}

inline void ActionPlaySound::ensureResourcesAreLoaded()
{ 
	for (AssetAudio* assetAudio : assetAudioList)
		if (!assetAudio->isLoaded())
			assetAudio->load();
}

inline bool ActionPlaySound::checkForErrors() const
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
			const AssetAudio* assetAudio = assetManager.findSoundAssetAudio(name);
			if (assetAudio == nullptr)
			{
				qDebug() << "Sound AssetAudio \"" + name + "\" not found by the AssetManager. Definition file might be corrupted.";
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