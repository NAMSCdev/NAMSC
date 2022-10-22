#pragma once
#include "Global.h"

#include "Novel/Data/Text/Voice.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/AssetManager.h"

/// Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectVoiceChange final : public ActionSceneryObject
{
public:
	ActionSceneryObjectVoiceChange() = default;
	ActionSceneryObjectVoiceChange(QString&& sceneryObjectName, QString&& voiceName);
	ActionSceneryObjectVoiceChange(const ActionSceneryObjectVoiceChange& obj) { *this = obj; }
	ActionSceneryObjectVoiceChange& operator=(const ActionSceneryObjectVoiceChange& obj);

	/// Executes the Action's logic
	void run() override;

	/// Accepts an ActionVisitor/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectVoiceChange(this); }

signals:
	/// A Qt signal emitted after the Action's `void run()` allowing for data read
	void onRun(SceneryObject* sceneryObject, QImage* image);

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID getType() const override { return SerializationID::ActionSetBackground; }

	//@todo [optional] Replace single images with an array of them
	//name to the Images that will replace SceneryObjectPart's images identified by IDs
	//QVector<QPair<uint, QString>>	sceneryObjectParts;

	/// Name to the Voice that will replace the old `defaultVoice` in the affected SceneryObject
	QString voiceName;
	/// Voice that will replace the old `defaultVoice` in the affected SceneryObject
	Voice*  voice;

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline ActionSceneryObjectVoiceChange& ActionSceneryObjectVoiceChange::operator=(const ActionSceneryObjectVoiceChange& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObject::operator=(obj);
	voiceName = obj.voiceName;
	voice     = obj.voice;

	return *this;
}