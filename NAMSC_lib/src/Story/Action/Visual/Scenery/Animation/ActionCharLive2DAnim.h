#pragma once
#include "Global.h"

#include "Story/Action/Action.h"
#include "Story/Data/Asset/Type/Live2DAnimAsset.h"
#include "Story/Data/Visual/Scenery/Character.h"

//[optional] Animates a Character with Live2D
//Could be synced with the Speech, have custom duration, or an infinite one
class ActionCharLive2DAnim final : public Action
{
public:
	ActionCharLive2DAnim() = default;
	ActionCharLive2DAnim(unsigned sceneID, unsigned eventExecutionOrder, QString &&characterURI, QString &&animURI,
		bool bSyncWithSpeech = false, int duration = -1, QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), characterURI(move(characterURI)), animURI(move(animURI)),
				bSyncWithSpeech(bSyncWithSpeech), duration(duration) {}

	//Executes Action's logic
	void					run						() override;
	
	//Accepts ActionVisitor
	void					accept					(ActionVisitor* visitor) override	{ visitor->visitActionCharLive2DAnim(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType					() const override					{ return SerializationID::ActionCharLive2DAnim; }

	//Ensures Assets are loaded and if not - loads it
	void					ensureAssetsAreLoaded	() override							{ anim->load(); }

	//ID of the animated Character
	QString					characterURI;
	//TODO: load Character
	Character				*character;

	//Animation to be played
	QString					animURI;
	//TODO: load asset
	Live2DAnimAsset			*anim;

	//Whether animation should be started with the beginning of the speech
	//If this is set to [true] and [duration] is set to -2, the animation will end with the ending of the Speech
	bool					bSyncWithSpeech												= false;

	//Duration of the animation in seconds
	//0 stands for infinite
	double					duration													= 0.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> characterURI >> animURI >> bSyncWithSpeech >> duration;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << characterURI << animURI << bSyncWithSpeech << duration;
	}
};
