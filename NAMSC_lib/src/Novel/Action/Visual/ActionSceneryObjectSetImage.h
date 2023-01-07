#pragma once
#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/AssetImage.h"

class ActionVisitorCorrectSceneryObjectAssetImage;

/// Changes the SceneryObject's `assetImage_`
class ActionSceneryObjectSetImage final : public ActionSceneryObject
{
	friend ActionVisitorCorrectSceneryObjectAssetImage;
public:
	ActionSceneryObjectSetImage(Event* const parentEvent) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName` or couldn't find/read the AssetImage named `assetImageName`
	ActionSceneryObjectSetImage(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetImageName);
	ActionSceneryObjectSetImage(const ActionSceneryObjectSetImage& obj) noexcept;
	ActionSceneryObjectSetImage& operator=(const ActionSceneryObjectSetImage& obj) noexcept;
	bool operator==(const ActionSceneryObjectSetImage& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectSetImage& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error `sceneryObject_`/`imageAsset_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	Action* clone() const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObject's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, SceneryObject* sceneryObject, QImage* image)> onRun) noexcept;

	const AssetImage* getAssetImage() const noexcept;
	AssetImage* getAssetImage() noexcept;
	QString getAssetImageName() const noexcept;
	void setAssetImage(const QString& assetImageName) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	void ensureResourcesAreLoaded() override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectSetImage's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, SceneryObject* sceneryObject, QImage* image)> onRun_ = nullptr;

	///\todo [optional] Replace single images with an array of them
	///Names of the Images that will replace SceneryObjectPart's images identified by IDs
	//std::vector<std::pair<uint, QString>>	sceneryObjectParts;

	QString     assetImageName_ = "";
	AssetImage* assetImage_     = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};