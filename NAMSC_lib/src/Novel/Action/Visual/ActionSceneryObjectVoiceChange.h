#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/Type/AssetFont.h"
#include "Novel/Data/Asset/AssetManager.h"

///Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectVoiceChange final : public ActionSceneryObject
{
public:
	ActionSceneryObjectVoiceChange() = default;
	ActionSceneryObjectVoiceChange(Event* parent, uint actionID, QString&& label, QString&& sceneryObjectName, QString&& imageAssetName) :
		ActionSceneryObject(move(label), move(sceneryObjectName)), imageAssetName(move(imageAssetName))
	{
		voice = Novel::getInstance().findVoice(imageAssetName);
	}
	ActionSceneryObjectVoiceChange(const ActionSceneryObjectVoiceChange& obj) { *this = obj; }
	ActionSceneryObjectVoiceChange& operator=(const ActionSceneryObjectVoiceChange& obj)
	{
		if (this == &obj) return *this;
		voiceName = obj.voiceName;
		voice     = obj.voice;

		return *this;
	}

	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectVoiceChange(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject* sceneryObject, QImage* image);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID getType() const override { return SerializationID::ActionSetBackground; }

	///Ensures Assets are loaded and if not - loads it
	void ensureResourcesAreLoaded() override
	{
		ActionSceneryObject::ensureResourcesAreLoaded();
		if (voice->isLoaded())
			voice->load();
	}

	//@todo [optional] Replace single images with an array of them
	//name to the Images that will replace SceneryObjectPart's images identified by IDs
	//QVector<QPair<uint, QString>>	sceneryObjectParts;

	///Name to the Voice that will replace the old `defaultVoice` in the affected SceneryObject
	QString voiceName;
	///Voice that will replace the old `defaultVoice` in the affected SceneryObject
	Voice*  voice;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};