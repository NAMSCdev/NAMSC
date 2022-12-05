#pragma once
#include "Novel/Action/Action.h"

#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectBackgroundAssetImage;

/// Changes Scene's **background** Image
class ActionSetBackground final : public Action
{
	friend ActionVisitorCorrectBackgroundAssetImage;
public:
	/// Blends the background Image change with a simple Animation
	enum class TransitionType
	{
		CrossFade,
		FadeOutToFadeIn,
		SweepRight	//[optional]
	};

	ActionSetBackground(Event* const parentEvent, Scene* const parentScene) noexcept;
	/// \exception Error Couldn't find the AssetImage named `assetImageName`
	ActionSetBackground(Event* const parentEvent, Scene* const parentScene, const QString& assetImageName, const TransitionType transitionType, double transitionTime);
	ActionSetBackground(const ActionSetBackground& obj)   = delete;
	ActionSetBackground& operator=(const ActionSetBackground& obj) noexcept;
	bool operator==(const ActionSetBackground& obj) const noexcept;
	bool operator!=(const ActionSetBackground& obj) const = default; //{ return !(*this == obj); }

	/// \exception Error 'assetImage_` is invalid
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const override;

	void run() override;

	void acceptVisitor(ActionVisitor* visitor) override;

	/// Sets a function pointer that is called (if not nullptr) after the ActionSetBackground's `void run()` allowing for data read
	void setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QImage* background, ActionSetBackground::TransitionType transitionType, double transitionTime)> onRun) noexcept;

	const AssetImage* getAssetImage() const noexcept;
	AssetImage* getAssetImage() noexcept;
	QString getAssetImageName() const noexcept;
	void setAssetImage(const QString& assetImageName) noexcept;

	TransitionType transitionType = TransitionType::CrossFade;

	/// In milliseconds
	uint transitionTime           = 600;

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	NovelLib::SerializationID getType() const noexcept override;

	/// A function pointer that is called (if not nullptr) after the ActionSetBackground's `void run()` allowing for data read
	std::function<void(Event* const parentEvent, Scene* const parentScene, QImage* background, ActionSetBackground::TransitionType transitionType, double transitionTime)> onRun_;

	QString     assetImageName_    = "";
	AssetImage* assetImage_        = nullptr;

	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};