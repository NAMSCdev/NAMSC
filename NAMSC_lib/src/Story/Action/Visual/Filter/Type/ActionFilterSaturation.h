#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Saturation Filter at a SceneryObject or the viewport
class ActionFilterSaturation final: public ActionFilter
{
public:
	ActionFilterSaturation() = default;
	ActionFilterSaturation( Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, double intensivness, 
							double strength, int addedSaturation, double percentSaturation) :
		ActionFilter(parent, actionID, move(label), move(sceneryObjectName), intensivness, strength),
		addedSaturation(addedSaturation), percentSaturation(percentSaturation) {}
	ActionFilterSaturation(const ActionFilterSaturation& obj) {
		*this = obj;
	}
	ActionFilterSaturation& operator=(const ActionFilterSaturation& obj) {
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);
		addedSaturation = obj.addedSaturation;
		percentSaturation = obj.percentSaturation;

		return *this;
	}
	
	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterSaturation(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength, int addedSaturation, double percentSaturation);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterSaturation; }

	///Adds Saturation to every pixel of the affected object/vieport
	///Accepted values: -100 - 100
	int	addedSaturation	= 0;

	///Modifies percent value of Saturation in every pixel of the affected object/vieport
	///Accepted values: 0.0 - 100.0
	double percentSaturation = 100.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};