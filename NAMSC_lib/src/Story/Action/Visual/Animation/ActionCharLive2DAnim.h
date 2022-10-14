#pragma once
#include "Global.h"

#include "Story/Action/Action.h"
#include "Story/Data/Asset/Type/Live2DAnimAsset.h"
#include "Story/Data/Visual/Scenery/Character.h"

///[optional] Animates a Character with Live2D
///Could be synced with the Speech, have custom duration, or an infinite one
class ActionCharLive2DAnim final : public Action
{
public:
	ActionCharLive2DAnim() = default;
	ActionCharLive2DAnim(	Event *parent, unsigned actionID, QString &&label, QString &&characterName, QString &&animAssetName,
							bool bSyncWithSpeech, int duration) :
		Action(parent, actionID, move(label)), characterName(move(characterName)), animAssetName(move(animAssetName)),
		bSyncWithSpeech(bSyncWithSpeech), duration(duration) 
	{	
		//animAsset = ??
	}
	ActionCharLive2DAnim(const ActionCharLive2DAnim& obj) {
		*this = obj;
	}
	ActionCharLive2DAnim& operator=(const ActionCharLive2DAnim& obj) {
		if (this == &obj) return *this;

		Action::operator=(obj);
		characterName = obj.characterName;
		character = obj.character;
		animAssetName = obj.animAssetName;
		animAsset = obj.animAsset;
		bSyncWithSpeech = obj.bSyncWithSpeech;
		duration = obj.duration;

		return *this;
	}

	///Executes Action's logic
	void run() override;
	
	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionCharLive2DAnim(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Character *character, QString animName, Live2DAnimAsset *anim);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionCharLive2DAnim; }

	///Ensures Assets are loaded and if not - loads it
	void			ensureAssetsAreLoaded() override{ if (!animAsset->isLoaded()) animAsset->load(); }

	///ID of the animated Character
	QString			characterName;
	///TODO: load Character
	Character		*character;

	///Animation to be played
	QString			animAssetName;
	///TODO: load asset
	Live2DAnimAsset	*animAsset;

	///Whether animation should be started with the beginning of the speech
	///If this is set to [true] and [duration] is set to -2, the animation will end with the ending of the Speech
	bool			bSyncWithSpeech	= false;

	///Duration of the animation in seconds
	///0 stands for infinite
	double			duration		= 0.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};
