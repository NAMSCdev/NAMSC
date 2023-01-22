#pragma once
#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/AssetImage.h"

class ActionVisitorCorrectSceneryObjectAssetImage;

/// Changes the SceneryObject's `assetImage_`
class ActionSceneryObjectSetImage final : public ActionSceneryObject
{
	friend ActionVisitorCorrectSceneryObjectAssetImage;
	/// Swap trick
	friend void swap(ActionSceneryObjectSetImage& first, ActionSceneryObjectSetImage& second) noexcept;
public:
	explicit ActionSceneryObjectSetImage(Event* const parentEvent) noexcept;
	/// \param sceneryObject Copies the SceneryObject pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param assetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName` or couldn't find/read the AssetImage named `assetImageName`
	ActionSceneryObjectSetImage(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetImageName = "", SceneryObject* sceneryObject = nullptr, AssetImage* assetImage = nullptr);
	ActionSceneryObjectSetImage(const ActionSceneryObjectSetImage& obj)     noexcept;
	ActionSceneryObjectSetImage(ActionSceneryObjectSetImage&& obj)          noexcept;
	ActionSceneryObjectSetImage& operator=(ActionSceneryObjectSetImage obj) noexcept;
	bool operator==(const ActionSceneryObjectSetImage& obj) const           noexcept;
	bool operator!=(const ActionSceneryObjectSetImage& obj) const           noexcept = default;

	/// \exception Error `sceneryObject_`/`imageAsset_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSceneryObject's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it. `image` is NOT castable
	void setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const QImage* const image)> onRun) noexcept;

	QString getAssetImageName()       const noexcept;
	const AssetImage* getAssetImage() const noexcept;
	AssetImage*       getAssetImage()       noexcept;
	void setAssetImage(const QString& assetImageName, AssetImage* assetImage = nullptr) noexcept;

	void acceptVisitor(ActionVisitor* visitor) override;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	/// \return NovelLib::SerializationID corresponding to the class of a serialized object
	NovelLib::SerializationID getType() const noexcept override;

	void ensureResourcesAreLoaded() override;

	/// A function pointer that is called (if not nullptr) after the ActionSceneryObjectSetImage's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it. `image` is NOT castable
	std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const QImage* const image)> onRun_ = nullptr;

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