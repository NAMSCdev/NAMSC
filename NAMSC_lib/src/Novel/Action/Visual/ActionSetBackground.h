#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectBackgroundAssetImage;

/// Changes Scene's **background** Image
class ActionSetBackground final : public Action
{
	friend ActionVisitorCorrectBackgroundAssetImage;
	/// Swap trick
	friend void swap(ActionSetBackground& first, ActionSetBackground& second) noexcept;
public:
	/// Blends the background Image change with a simple Animation
	enum class TransitionType
	{
		CrossFade,
		FadeOutToFadeIn,
		SweepRight	//[optional]
	};

	explicit ActionSetBackground(Event* const parentEvent)         noexcept;
	/// \param transitionTime In milliseconds
	/// \param assetImage Copies the AssetImage pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization
	/// \exception Error Couldn't find the AssetImage named `assetImageName`
	ActionSetBackground(Event* const parentEvent, const QString& assetImageName, const TransitionType transitionType, uint transitionTime, AssetImage* assetImage = nullptr);
	ActionSetBackground(const ActionSetBackground& obj)            noexcept = delete;
	ActionSetBackground(ActionSetBackground&& obj)                 noexcept;
	ActionSetBackground& operator=(const ActionSetBackground& obj) noexcept = delete;
	//ActionSetBackground& operator=(ActionSetBackground obj)        noexcept;
	bool operator==(const ActionSetBackground& obj) const          noexcept = delete;
	bool operator!=(const ActionSetBackground& obj) const          noexcept = delete;

	/// \exception Error 'assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const override;

	void run() override;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSetBackground's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it. `image` is NOT castable
	void setOnRunListener(std::function<void(const Event* const parentEvent, const QImage* const background, const ActionSetBackground::TransitionType& transitionType, const uint& transitionTime)> onRun) noexcept;

	QString getAssetImageName()       const noexcept;
	const AssetImage* getAssetImage() const noexcept;
	AssetImage*       getAssetImage()       noexcept;
	void setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept;

	TransitionType transitionType = TransitionType::CrossFade;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// In milliseconds
	uint transitionTime           = 600;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSetBackground's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it. `image` is NOT castable
	std::function<void(const Event* const parentEvent, const QImage* const background, const ActionSetBackground::TransitionType& transitionType, const uint& transitionTime)> onRun_;

	QString     assetImageName_    = "";
	AssetImage* assetImage_        = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};