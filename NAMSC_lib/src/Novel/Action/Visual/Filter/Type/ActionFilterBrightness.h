#pragma once
#include "Global.h"

#include "Novel/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Brightnss Filter at a SceneryObject or the viewport
class ActionFilterBrightness final : public ActionFilter
{
public:
	ActionFilterBrightness() = default;
	ActionFilterBrightness( Event *parent, uint actionID, QString &&label, QString &&sceneryObjectName, double addedBrightness, 
							double percentBrightness, double intensivness, double strength) :
		ActionFilter(move(label), move(sceneryObjectName), intensivness, strength), 
		addedBrightness(addedBrightness), percentBrightness(percentBrightness)  {}
	ActionFilterBrightness(const ActionFilterBrightness& obj) { *this = obj; }
	ActionFilterBrightness& operator=(const ActionFilterBrightness& obj)
	{
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);
		addedBrightness   = obj.addedBrightness;
		percentBrightness = obj.percentBrightness;

		return *this;
	}

	///Executes this Action's logic
	void run() override;

	///Accepts an ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterBrightness(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, uint strength, double addedBrightness, double	percentBrightness);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterBrightness; }

	///Adds Brightness to every pixel of the affected object/vieport
	///Accepted values: 0.0 - 1.0
	double	addedBrightness	= 0.0;

	///Modifies percent value of Brightness in every pixel of the affected object/vieport
	///Accepted values: 0.0 - 100.0
	double	percentBrightness = 100.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};