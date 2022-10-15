#pragma once
#include "Global.h"

#include "Story/Action/Visual/Effect/ActionEffect.h"

///[optional] Creates a Glow Effect at some point in a SceneryObject or the viewport
class ActionEffectGlow final : public ActionEffect
{
public:
	ActionEffectGlow() = default;
	ActionEffectGlow(unsigned actionID, QString &&label, QString &&sceneryObjectName, EffectShape effectShape, QPoint pos,
					 QSize size, unsigned strength) :
		ActionEffect(actionID, move(label), move(sceneryObjectName), effectShape, pos, size, strength) {}
	ActionEffectGlow(const ActionEffectGlow& obj) { *this = obj; }
	ActionEffectGlow& operator=(const ActionEffectGlow& obj) 
	{
		if (this == &obj) return *this;

		ActionEffect::operator=(obj);

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionEffectGlow(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, EffectShape effectShape, QPoint pos, QSize size, unsigned strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionEffectGlow; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};