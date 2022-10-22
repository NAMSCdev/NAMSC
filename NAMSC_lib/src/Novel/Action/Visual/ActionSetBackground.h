#pragma once
#include "Global.h"

#include "Novel/Action/Action.h"

#include "Novel/Data/Asset/AssetManager.h"

class ActionVisitorCorrectBackgroundAssetImage;
/// Changes Scene's background Image and/or UI theme
class ActionSetBackground final : public Action
{
	friend ActionVisitorCorrectBackgroundAssetImage;
public:
	/// Blends the scene change with an animation
	enum class TransitionType
	{
		CrossFade,
		SweepRight	//[optional]
	};

	ActionSetBackground() = default;
	ActionSetBackground(QString&& imageAssetName, TransitionType transitionType, double transitionTime);
	ActionSetBackground(const ActionSetBackground& obj) { *this = obj; }
	ActionSetBackground& operator=(const ActionSetBackground& obj);

	/// Executes the Action's logic
	void run() override;

	/// Accepts an ActionVisitor/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSetBackground(this); }

signals:
	/// A Qt signal emitted after the Action's `void run()` allowing for data read
	void onRun(QImage *background, ActionSetBackground::TransitionType transitionType, double transitionTime);

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID getType() const override { return SerializationID::ActionSetBackground; }

	/// Name to the background Image that will replace the old *background* Image in the *Scenery*
	QString		assetImageName;
	/// Asset of the Image that will replace the old *background* Image in the *Scenery*
	AssetImage* assetImage;


	/// Blends the scene change with an animation
	TransitionType transitionType = TransitionType::CrossFade;

	/// Time the transtition takes to move from one Image into another in seconds
	double transitionTime = 1.0;

	//[optional]name to the UI theme, so it can be loaded (if needed) and replaced
	//QString			themeName		= "";

	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline ActionSetBackground::ActionSetBackground(QString&& assetImageName, TransitionType transitionType, double transitionTime) :
	Action(), assetImageName(move(assetImageName)), transitionType(transitionType), transitionTime(transitionTime)
{
	assetImage = AssetManager::getInstance().findSceneryBackgroundAssetImage(this->assetImageName);
}

inline ActionSetBackground& ActionSetBackground::operator=(const ActionSetBackground& obj)
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	assetImageName = obj.assetImageName;
	assetImage     = obj.assetImage;

	return *this;
}