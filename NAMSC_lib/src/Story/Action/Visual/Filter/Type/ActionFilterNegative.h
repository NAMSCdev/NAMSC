#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Negation Filter at a SceneryObject or the viewport
///"Flips" colors
class ActionFilterNegative final : public ActionFilter
{
public:
	ActionFilterNegative() = default;
	ActionFilterNegative(Event *parent, unsigned actionID, double intensivness, 
						 double strength, QString &&sceneryObjectName, QString &&label) :
		ActionFilter(parent, actionID, move(label), move(sceneryObjectName), intensivness, strength) {}
	ActionFilterNegative(const ActionFilterNegative& obj) {
		*this = obj;
	}
	ActionFilterNegative& operator=(const ActionFilterNegative& obj) {
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterNegative(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterNegative; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};