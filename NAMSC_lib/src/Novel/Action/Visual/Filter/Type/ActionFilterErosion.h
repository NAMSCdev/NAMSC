#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Erosion Filter at a SceneryObject or the viewport
class ActionFilterErosion final : public ActionFilter
{
public:
	ActionFilterErosion() = default;
	ActionFilterErosion(QString &&label, QString &&sceneryObjectName, 
						double intensivness, double strength) :
		ActionFilter(move(label), move(sceneryObjectName), intensivness, strength) {}
	ActionFilterErosion(const ActionFilterErosion& obj) { *this = obj; }
	ActionFilterErosion& operator=(const ActionFilterErosion& obj) 
	{
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);

		return *this;
	}
	
	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterErosion(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, uint strength);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterErosion; }

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};