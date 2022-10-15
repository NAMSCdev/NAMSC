#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Dilation Filter at a SceneryObject or the viewport
class ActionFilterDilation final : public ActionFilter
{
public:
	ActionFilterDilation() = default;
	ActionFilterDilation(unsigned actionID, QString &&label, QString &&sceneryObjectName, 
						 double intensivness, double strength) :
		ActionFilter(actionID, move(label), move(sceneryObjectName), intensivness, strength) {}
	ActionFilterDilation(const ActionFilterDilation& obj) { *this = obj; }
	ActionFilterDilation& operator=(const ActionFilterDilation& obj) 
	{
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);

		return *this;
	}
	
	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionFilterDilation(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionFilterDilation; }
	
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};