#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/Type/AssetImage.h"
#include "Novel/Data/Asset/AssetManager.h"

///Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectImageChange final : public ActionSceneryObject
{
public:
	ActionSceneryObjectImageChange() = default;
	ActionSceneryObjectImageChange(Event* parent, uint actionID, QString&& label, QString&& sceneryObjectName, QString&& imageAssetName);
	ActionSceneryObjectImageChange(const ActionSceneryObjectImageChange& obj) { *this = obj; }
	ActionSceneryObjectImageChange& operator=(const ActionSceneryObjectImageChange& obj);

	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectImageChange(this); }

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
		if (imageAsset->isLoaded())
			imageAsset->load();
	}

	//@todo [optional] Replace single images with an array of them
	//name to the Images that will replace SceneryObjectPart's images identified by IDs
	//QVector<QPair<uint, QString>>	sceneryObjectParts;

	///Name to the AssetImage that will replace the old Image in the affected SceneryObject
	QString imageAssetName;
	///Image that will replace the old Image in the affected SceneryObject
	AssetImage* imageAsset;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline ActionSceneryObjectImageChange::ActionSceneryObjectImageChange(Event* parent, uint actionID, QString&& label, QString&& sceneryObjectName, QString&& imageAssetName) :
	ActionSceneryObject(move(label), move(sceneryObjectName)), imageAssetName(move(imageAssetName))
{
	imageAsset = AssetManager::getInstance().findSceneryObjectAssetImage(imageAssetName);
}

inline ActionSceneryObjectImageChange& ActionSceneryObjectImageChange::operator=(const ActionSceneryObjectImageChange& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObject::operator=(obj);
	imageAssetName = obj.imageAssetName;
	imageAsset = obj.imageAsset;

	return *this;
}