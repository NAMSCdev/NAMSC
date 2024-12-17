//#pragma once
//#include "Global.h"
//
//#include "pvnLib/Novel/Action/Action.h"
//#include "pvnLib/Novel/Data/Asset/Type/AssetLive2DAnim.h"
//#include "pvnLib/Novel/Data/Visual/Scenery/Character.h"
//
//class ActionVisitorCorrectAssetLive2DAnim;
//
///// [optional] Animates a Character with Live2D
///// Could be synced with the Sentence, have a custom duration, or an infinite one
///// @todo [optional]Animations should be able to be queued, so instead of changing one animation, there should be a more robust struct for holding data about it and every Character should store currently played LIST of animations 
//class ActionLive2DAnim final : public Action
//{
//	friend ActionVisitorCorrectAssetLive2DAnim;
//public:
//	ActionLive2DAnim() noexcept = default;
//	ActionLive2DAnim(QString&& characterName, QString&& assetAnimName, bool bSyncWithSpeech, int duration);
//	ActionLive2DAnim(const ActionLive2DAnim& obj) noexcept { *this = obj; }
//	ActionLive2DAnim& operator=(const ActionLive2DAnim& obj) noexcept;
//
//	/// Executes the ActionLive2DAnim's logic
//	void run() override;
//	
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionLive2DAnim(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionLive2DAnim's `void run()` allowing for data read
//	/// @todo include anim
//	void onRun(Character* character, bool bSyncWithSpeech, double duration) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionLive2DAnim; }
//
//	/// Ensures Assets are loaded and if not - loads it
//	void ensureResourcesAreLoaded() override;
//
//	/// ID of the animated Character
//	QString   characterName;
//	/// TODO: load Character
//	Character *character;
//
//	/// Animation to be played
//	QString			 assetLive2DAnimName;
//	/// TODO: load asset
//	AssetLive2DAnim* animLive2DAsset;
//
//	/// Whether animation should be started with the beginning of the speech
//	/// If this is set to `true` and `duration` is set to `0.0`, the animation will end with the ending of the Speech
//	bool bSyncWithSpeech = false;
//
//	/// Duration of the animation in seconds
//	/// Negative time stands for infinite
//	/// If `bSyncWithSpeech` is set to `true` and this is set to `0.0`, the animation will end with the ending of the Speech
//	double duration = 0.0;
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to read from
//	void serializableLoad(QDataStream& dataStream) override;
//	/// Saving an object to a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to save to
//	void serializableSave(QDataStream& dataStream) const override;
//};
//
//
//
//
//inline ActionLive2DAnim::ActionLive2DAnim(QString&& characterName, QString&& assetLive2DAnimName, bool bSyncWithSpeech, int duration) :
//	Action(true), characterName(move(characterName)), assetLive2DAnimName(move(assetLive2DAnimName)), bSyncWithSpeech(bSyncWithSpeech), duration(duration)
//{
//	animLive2DAsset = AssetManager::getInstance().findAssetLive2DAnim(assetLive2DAnimName);
//}
//	
//inline ActionLive2DAnim& ActionLive2DAnim::operator=(const ActionLive2DAnim& obj)
//{
//	if (this == &obj) return *this;
//
//	Action::operator=(obj);
//	characterName       = obj.characterName;
//	character           = obj.character;
//	assetLive2DAnimName = obj.assetLive2DAnimName;
//	animLive2DAsset     = obj.animLive2DAsset;
//	bSyncWithSpeech     = obj.bSyncWithSpeech;
//	duration            = obj.duration;
//
//	return *this;
//}
//
//inline void ActionLive2DAnim::ensureResourcesAreLoaded()
//{
//	if (!animLive2DAsset->isLoaded())
//		animLive2DAsset->load();
//}
