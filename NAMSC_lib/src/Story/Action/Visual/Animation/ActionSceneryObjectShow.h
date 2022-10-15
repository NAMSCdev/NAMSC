#pragma once
#include "Global.h"

#include "Story/Action/Visual/ActionSceneryObject.h"

///Makes an Scene Object appear
class ActionSceneryObjectShow : public ActionSceneryObject
{
public:
	///Available effects for the appearing animatio
	enum class AppearEffectType
	{
		FadeIn
	};

	ActionSceneryObjectShow() = default;
	ActionSceneryObjectShow(unsigned actionID, QString &&label, QString &&sceneryObjectName,
							AppearEffectType appearEffectType, double duration, bool bAppear, bool bPerserveAnimation, bool bShow) :
		ActionSceneryObject(actionID, move(label), move(sceneryObjectName)), appearEffectType(appearEffectType),
		duration(duration), bAppear(bAppear), bPerserveAnimation(bPerserveAnimation), bShow(bShow) {}
	ActionSceneryObjectShow(const ActionSceneryObjectShow& obj) { *this = obj; }
	ActionSceneryObjectShow& operator=(const ActionSceneryObjectShow& obj)
	{
		if (this == &obj) return *this;

		ActionSceneryObject::operator=(obj);
		appearEffectType   = obj.appearEffectType;
		duration           = obj.duration;
		bAppear            = obj.bAppear;
		bPerserveAnimation = obj.bPerserveAnimation;
		bShow              = obj.bShow;
		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor *visitor) override { visitor->visitActionSceneryObjectShow(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, AppearEffectType appearEffectType, double duration, bool bAppear, bool bPerserveAnimation);

protected:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	virtual SerializationID	getType() const override { return SerializationID::ActionSceneryObjectShow; }

	///Available effects for the appearing animatio
	AppearEffectType appearEffectType = AppearEffectType::FadeIn;

	///Duration of the [appearEffect] in seconds
	double duration	= 0.1;

	///Whether is it Appear animation or Dissapear animation
	bool bAppear = true;

	///If it is a GIF, play its animation dNameng the appear animation
	///[optional] If it is a Live2D animated, it will keep on playing its animation dNameng the appear animation
	bool bPerserveAnimation	= false;

	///Whether the SceneryObject will appear or disappear
	bool bShow = true;
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};
