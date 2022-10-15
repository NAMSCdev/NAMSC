#pragma once
#include "Global.h"

#include "Story/Action/Visual/Effect/ActionEffect.h"

///[optional] Creates a Distort Effect at some point in a SceneryObject or the viewport
class ActionEffectDistort final : public ActionEffect
{
public:
	ActionEffectDistort() = default;
	ActionEffectDistort(unsigned actionID, QString &&label, QString &&sceneryObjectName, EffectShape effectShape, QPoint pos,
						QSize size, unsigned strength) :
		ActionEffect(actionID, move(label), move(sceneryObjectName), effectShape, pos, size, strength) {}
	ActionEffectDistort(const ActionEffectDistort& obj) { *this = obj; }
	ActionEffectDistort& operator=(const ActionEffectDistort& obj) 
	{
		if (this == &obj) return *this;

		ActionEffect::operator=(obj);

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionEffectDistort(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, EffectShape effectShape, QPoint pos, QSize size, unsigned strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionEffectDistort; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};