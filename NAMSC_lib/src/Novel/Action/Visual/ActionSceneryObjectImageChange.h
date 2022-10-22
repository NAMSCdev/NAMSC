#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/Type/AssetImage.h"
#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectSceneryObjectAssetImage;
/// Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectImageChange final : public ActionSceneryObject
{
	friend ActionVisitorCorrectSceneryObjectAssetImage;
public:
	ActionSceneryObjectImageChange() = default;
	ActionSceneryObjectImageChange(QString&& sceneryObjectName, QString&& imageAssetName);
	ActionSceneryObjectImageChange(const ActionSceneryObjectImageChange& obj) { *this = obj; }
	ActionSceneryObjectImageChange& operator=(const ActionSceneryObjectImageChange& obj);

	/// Executes the Action's logic
	void run() override;

	/// Accepts an ActionVisitor
	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectImageChange(this); }

signals:
	/// A Qt signal emitted after the Action's `void run()` allowing for data read
	void onRun(SceneryObject* sceneryObject, QImage* image);

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID getType() const override { return SerializationID::ActionSetBackground; }

	/// Ensures Assets are loaded and if not - loads it
	void ensureResourcesAreLoaded() override;

	//@todo [optional] Replace single images with an array of them
	//name to the Images that will replace SceneryObjectPart's images identified by IDs
	//QVector<QPair<uint, QString>>	sceneryObjectParts;

	/// Name to the AssetImage that will replace the old Image in the affected *SceneryObject*
	QString		assetImageName;
	/// Asset of the Image that will replace the old Image in the affected *SceneryObject*
	AssetImage* assetImage;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline ActionSceneryObjectImageChange::ActionSceneryObjectImageChange(QString&& sceneryObjectName, QString&& assetImageName) :
	ActionSceneryObject(move(sceneryObjectName)), assetImageName(move(assetImageName))
{
	assetImage = AssetManager::getInstance().findSceneryObjectAssetImage(assetImageName);
}

inline ActionSceneryObjectImageChange& ActionSceneryObjectImageChange::operator=(const ActionSceneryObjectImageChange& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObject::operator=(obj);
	assetImageName = obj.assetImageName;
	assetImage     = obj.assetImage;

	return *this;
}

inline void ActionSceneryObjectImageChange::ensureResourcesAreLoaded()
{
	ActionSceneryObject::ensureResourcesAreLoaded();

	if (assetImage->isLoaded())
		assetImage->load();
}