#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Asset/AssetManager.h"

///Changes Scene's background Image and/or UI theme
class ActionSetBackground final : public Action
{
public:
	///Blends the scene change with an animation
	enum class TransitionType
	{
		CrossFade,
		SweepRight	//[optional]
	};

	ActionSetBackground() = default;
	ActionSetBackground(unsigned actionID, QString &&label, QString &&backgroundAssetName, TransitionType transitionType, 
						double transitionTime/*, QString &&themeName*/) :
		Action(actionID, move(label)), backgroundAssetName(move(backgroundAssetName)), transitionType(transitionType),
		transitionTime(transitionTime)/*, themeName(move(themeName))*/ 
			{ backgroundAsset = AssetManager::getInstance().findSceneryBackgroundAssetImage(this->backgroundAssetName); }
	ActionSetBackground(const ActionSetBackground& obj) { *this = obj; }
	ActionSetBackground& operator=(const ActionSetBackground& obj) 
	{
		if (this == &obj) return *this;

		Action::operator=(obj);
		backgroundAssetName = obj.backgroundAssetName;
		backgroundAsset     = obj.backgroundAsset;

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSetBackground(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(QImage *background, TransitionType transitionType, double transitionTime);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID getType() const override { return SerializationID::ActionSetBackground; }

	///Name to the background Image, so it can be loaded (if needed) and replaced
	QString	backgroundAssetName;
	AssetImage *backgroundAsset = nullptr;


	///Blends the scene change with an animation
	TransitionType transitionType = TransitionType::CrossFade;

	///Time the transtition takes to move from one Image into another in seconds
	double transitionTime = 1.0;

	//[optional]name to the UI theme, so it can be loaded (if needed) and replaced
	//QString			themeName		= "";

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};