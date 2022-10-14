#pragma once
#include "Global.h"

#include "Story/Action/Visual/Animation/ActionSceneryObjectShow.h"

///Makes an Scene Object dissapear
class ActionSceneryObjectHide final : public ActionSceneryObjectShow
{
public:
	ActionSceneryObjectHide() = default;
	ActionSceneryObjectHide(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, AppearEffectType appearEffectType, 
							double duration, bool bAppear, bool bPerserveAnimation) :
		ActionSceneryObjectShow(parent, actionID, move(sceneryObjectName), move(label), appearEffectType, duration, bAppear, bPerserveAnimation) {}
	ActionSceneryObjectHide(const ActionSceneryObjectHide& asset)				= default;
	ActionSceneryObjectHide& operator=(const ActionSceneryObjectHide& asset)	= default;

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectHide(this); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override	 { return SerializationID::ActionSceneryObjectHide; }
};
