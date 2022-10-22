#pragma once
#include "Global.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"

/// Makes a SceneObject appear or disappear
class ActionSceneryObjectVisibility : public ActionSceneryObject
{
public:
	/// Available effects for the appearing Animation
	enum class AppearEffectType
	{
		FadeIn
	};

	ActionSceneryObjectVisibility() noexcept = default;
	ActionSceneryObjectVisibility(QString&& sceneryObjectName, AppearEffectType appearEffectType, double duration,
										bool bAppear, bool bPerserveAnimation);
	ActionSceneryObjectVisibility(const ActionSceneryObjectVisibility& obj) noexcept { *this = obj; }
	ActionSceneryObjectVisibility& operator=(const ActionSceneryObjectVisibility& obj) noexcept;

	/// Executes the ActionSceneryObjectVisibility's logic
	void run() override;

	/// Accepts an ActionVisitor
	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionSceneryObjectVisibility(this); }

signals:
	/// A Qt signal emitted after the ActionSceneryObjectVisibility's `void run()` allowing for data read
	/// \param sceneryObject The SceneryObject that appears or dissapears
	/// \param appearEffectType Available effects for the appearing Animation
	/// \param duration Duration of the Animation in milliseconds
	/// \param bAppear Whether to appear or disappear
	/// \param bPerserveAnimation Whether its Idle Animation should be played during the appear/dissapear Animation
	void onRun(const SceneryObject* sceneryObject, AppearEffectType appearEffectType, double duration, bool bAppear, bool bPerserveAnimation);

protected:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	virtual SerializationID	getType() const override { return SerializationID::ActionSceneryObjectVisibility; }

	/// Available effects for the appearing Animation
	AppearEffectType appearEffectType = AppearEffectType::FadeIn;

	/// Duration of the Animation in milliseconds
	uint duration = 100;

	/// Whether to appear or disappear
	bool bAppear = true;

	/// If it is a GIF, play its Animation during the appear Animation
	/// [optional] If it is a Live2D animated, it will keep on playing its Animation during the appear Animation
	bool bPerserveAnimation	= false;
	
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};




inline ActionSceneryObjectVisibility::ActionSceneryObjectVisibility(QString&& sceneryObjectName, AppearEffectType appearEffectType,
																	double duration, bool bAppear, bool bPerserveAnimation) : 
	ActionSceneryObject(move(sceneryObjectName)), appearEffectType(appearEffectType), duration(duration), bAppear(bAppear), bPerserveAnimation(bPerserveAnimation)
{
}

inline ActionSceneryObjectVisibility& ActionSceneryObjectVisibility::operator=(const ActionSceneryObjectVisibility& obj)
{
	if (this == &obj) return *this;

	ActionSceneryObject::operator=(obj);
	appearEffectType   = obj.appearEffectType;
	duration           = obj.duration;
	bAppear            = obj.bAppear;
	bPerserveAnimation = obj.bPerserveAnimation;

	return *this;
}