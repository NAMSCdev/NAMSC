#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Erosion Filter at a SceneryObject or the viewport
class ActionFilterErosion final : public ActionFilter
{
public:
	ActionFilterErosion() = default;
	ActionFilterErosion(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, 
						double intensivness, double strength) :
		ActionFilter(parent, actionID, move(label), move(sceneryObjectName), intensivness, strength) {}
	ActionFilterErosion(const ActionFilterErosion& asset)				= default;
	ActionFilterErosion& operator=(const ActionFilterErosion& asset)	= default;
	
	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override	{ visitor->visitActionFilterErosion(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override		{ return SerializationID::ActionFilterErosion; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};