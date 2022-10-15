#pragma once
#include "Global.h"

#include "Story/Action/Visual/ActionSceneryObject.h"

#include "Story/Data/Asset/Type/AssetImage.h"
#include "Story/Data/Asset/AssetManager.h"

///Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectChange final : public ActionSceneryObject
{
public:
	ActionSceneryObjectChange() = default;
	ActionSceneryObjectChange(Event* parent, unsigned actionID, QString&& label, QString&& sceneryObjectName, QString&& imageAssetName) :
		ActionSceneryObject(actionID, move(label), move(sceneryObjectName)), imageAssetName(move(imageAssetName))
	{
		imageAsset = AssetManager::getInstance().findSceneryObjectAssetImage(imageAssetName);
	}
	ActionSceneryObjectChange(const ActionSceneryObjectChange& obj) { *this = obj; }
	ActionSceneryObjectChange& operator=(const ActionSceneryObjectChange& obj)
	{
		if (this == &obj) return *this;

		ActionSceneryObject::operator=(obj);
		imageAssetName = obj.imageAssetName;
		imageAsset     = obj.imageAsset;

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectChange(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject* sceneryObject, QImage* image);

private:
	///Ensures Assets are loaded and if not - loads it
	void ensureAssetsAreLoaded() override
	{
		ActionSceneryObject::ensureAssetsAreLoaded();
		if (imageAsset->isLoaded())
			imageAsset->load();
	}

	//@todo [optional] Replace single images with an array of them
	//name to the Images that will replace SceneryObjectPart's images identified by IDs
	//QVector<QPair<unsigned, QString>>	sceneryObjectParts;

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