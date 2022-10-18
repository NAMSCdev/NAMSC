#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Data/Asset/Type/AssetLive2DAnim.h"

#include "Novel/Data/Visual/Scenery/Character.h"

class ActionVisitorCorrectLive2DAnimAsset;

///[optional] Animates a Character with Live2D
///Could be synced with the Speech, have custom duration, or an infinite one
///@todo [optional]Animations should be able to be queued, so instead of changing one animation, there should be a more robust struct for holding data about it and every Character should store currently played LIST of animations 
class ActionLive2DAnim final : public Action
{
	friend ActionVisitorCorrectLive2DAnimAsset;
public:
	ActionLive2DAnim() = default;
	ActionLive2DAnim(QString&& characterName, QString&& animAssetName, bool bSyncWithSpeech, int duration);
	ActionLive2DAnim(const ActionLive2DAnim& obj) {	*this = obj; }
	ActionLive2DAnim& operator=(const ActionLive2DAnim& obj);

	///Executes this Action's logic
	void run() override;
	
	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionLive2DAnim(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	///@todo include anim
	void onRun(Character* character, bool bSyncWithSpeech, double duration);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionLive2DAnim; }

	///Ensures Assets are loaded and if not - loads it
	void ensureResourcesAreLoaded() override;

	///ID of the animated Character
	QString   characterName;
	///TODO: load Character
	Character *character;

	///Animation to be played
	QString			 assetLive2DAnimName;
	///TODO: load asset
	AssetLive2DAnim* animLive2DAsset;

	///Whether animation should be started with the beginning of the speech
	///If this is set to `true` and `duration` is set to `0.0`, the animation will end with the ending of the Speech
	bool bSyncWithSpeech = false;

	///Duration of the animation in seconds
	///Negative time stands for infinite
	///If `bSyncWithSpeech` is set to `true` and this is set to `0.0`, the animation will end with the ending of the Speech
	double duration = 0.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};




inline ActionLive2DAnim::ActionLive2DAnim(QString&& characterName, QString&& assetLive2DAnimName, bool bSyncWithSpeech, int duration) :
	Action(), characterName(move(characterName)), assetLive2DAnimName(move(assetLive2DAnimName)), bSyncWithSpeech(bSyncWithSpeech), duration(duration)
{
	animLive2DAsset = AssetManager::getInstance().findAssetLive2DAnim(assetLive2DAnimName);
}
	
inline ActionLive2DAnim& ActionLive2DAnim::operator=(const ActionLive2DAnim& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	characterName       = obj.characterName;
	character           = obj.character;
	assetLive2DAnimName = obj.assetLive2DAnimName;
	animLive2DAsset     = obj.animLive2DAsset;
	bSyncWithSpeech     = obj.bSyncWithSpeech;
	duration            = obj.duration;

	return *this;
}

inline void ActionLive2DAnim::ensureResourcesAreLoaded()
{
	if (!animLive2DAsset->isLoaded())
		animLive2DAsset->load();
}
