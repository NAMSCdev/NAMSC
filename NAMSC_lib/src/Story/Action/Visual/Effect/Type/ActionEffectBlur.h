#pragma once
#include "Global.h"

#include "Story/Action/Visual/Effect/ActionEffect.h"

///[optional] Creates a Blur Effect at some point in a SceneryObject or the viewport
class ActionEffectBlur final : public ActionEffect
{
public:
	///Algorithm used for blurring
	enum class BlurType
	{
		Gaussian
	};

	ActionEffectBlur() = default;
	ActionEffectBlur(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, EffectShape effectShape, QPoint pos,
					 QSize size, unsigned strength, BlurType blurType) :
		ActionEffect(parent, actionID, move(label), move(sceneryObjectName), effectShape, pos, size, strength), blurType(blurType) {}
	ActionEffectBlur(const ActionEffectBlur& asset)				= default;
	ActionEffectBlur& operator=(const ActionEffectBlur& asset)	= default;

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionEffectBlur(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, EffectShape effectShape, QPoint pos, QSize size, unsigned strength, BlurType blurType);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionEffectBlur; }

	///Algorithm used for blurring
	BlurType blurType = BlurType::Gaussian;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};