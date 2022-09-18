#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

//Changes background Music played along the Scene
class ActionChangeMusic final : public Action
{
public:
	ActionChangeMusic() = default;
	//TODO: add Exception on musicAsset on found (check for nullptr)
	ActionChangeMusic(unsigned sceneID, unsigned eventExecutionOrder, std::vector<QString> &&musicURIs, double volume = 1.0, double stereo = 0.5,
		bool bLoop = true, bool bRandomized = false, bool bExclusive = false, QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), musicURIs(move(musicURIs)), bLoop(bLoop), bRandomized(bRandomized),
				bExclusive(bExclusive), stereo(stereo), volume(volume) { for (const QString &uri : musicURIs) musicAssets.push_back(AssetManager::findMusicAsset(uri)); }

	//Executes Action's logic
	void					run						() override;

	//Accepts ActionVisitor
	void					accept					(ActionVisitor* visitor) override	{ visitor->visitActionChangeMusic(this); }
	
protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType					() const override					{ return SerializationID::ActionChangeMusic; }

	//Ensures Assets are loaded and if not - loads it
	void					ensureAssetsAreLoaded	() override							{ for (MusicAsset *musicAsset : musicAssets) if (!musicAsset->isLoaded()) musicAsset->load(); }

	//URI to the background Music, so it can be loaded (if needed) and played
	std::vector<QString>	musicURIs;
	std::vector<MusicAsset*>musicAssets;

	//Volume of the played Sound
	double					volume														= 1.0;

	//How the sound is played in stereo headphones
	//0.0 - left only, 0.5 - both, 1.0 - right only
	//Accepted values: 0.0 - 1.0
	//[optional] Allow more channels
	double					stereo														= 0.5;

	//Whether the Music should be looped infinitely
	bool					bLoop														= true;

	//Whether to randomize Music order
	bool					bRandomized													= false;

	//Whether every Music should be played at least one
	bool					bExclusive													= false;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		unsigned musicURIsSize;
		dataStream >> musicURIsSize;
		for (unsigned i = 0u; i != musicURIsSize; ++i)
		{
			QString uri;
			dataStream >> uri;
			musicURIs.push_back(uri);
		}
		dataStream >> volume >> stereo >> bLoop >> bRandomized >> bExclusive;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << musicURIs.size();

		for (const QString &uri : musicURIs)
			dataStream << uri;

		dataStream << volume << stereo << bLoop << bRandomized << bExclusive;
	}
};