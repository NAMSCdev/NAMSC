#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Asset/Type/MusicAsset.h"
#include "Story/Data/Asset/AssetManager.h"

//Changes background Music played along the Scene
class ActionPlaySound final : public Action
{
public:
	ActionPlaySound() = default;
	ActionPlaySound(unsigned sceneID, unsigned eventExecutionOrder, QString &&soundURI, double volume = 1.0, double stereo = 0.5, int timesPlayed = 1,
		bool bPersistToNewEvent = false , QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), soundURI(move(soundURI)), timesPlayed(timesPlayed), stereo(stereo), volume(volume) 
				{ soundAsset = AssetManager::findSoundAsset(soundURI); }

	//Executes Action's logic
	void					run						() override;

	//Accepts ActionVisitor
	void					accept					(ActionVisitor* visitor) override	{ visitor->visitActionPlaySound(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType					() const override					{ return SerializationID::ActionPlaySound; }

	//Ensures Assets are loaded and if not - loads it
	void					ensureAssetsAreLoaded	() override							{ if (!soundAsset->isLoaded()) soundAsset->load(); }

	//URI to the background Sound, so it can be loaded (if needed) and played
	QString					soundURI;
	SoundAsset				*soundAsset;

	//Volume of the played Sound
	double					volume														= 1.0;

	//How the sound is played in stereo headphones
	//0.0 - left only, 0.5 - both, 1.0 - right only
	//Accepted values: 0.0 - 1.0
	//[optional] Allow more channels
	double					stereo														= 0.5;

	//How many times it will be played
	//Can be set to -1, so it will be played infinite amount of times
	int						timesPlayed													= 1;

	//Whether the Sound should be cut if user gets to the next Scene's Event before the end of this Sound
	bool					bPersistToNewEvent											= false;
	
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> soundURI >> volume >> stereo >> volume >> bPersistToNewEvent;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << soundURI << volume << stereo << volume << bPersistToNewEvent;
	}
};