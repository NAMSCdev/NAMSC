#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Hue Filter at a SceneryObject or the viewport
class ActionFilterHue final : public ActionFilter
{
public:
	ActionFilterHue() = default;
	ActionFilterHue(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName,
					double intensivness, double strength, int hueShift) :
		ActionFilter(parent, actionID, move(label), move(sceneryObjectName), intensivness, strength), hueShift(hueShift) {}
	ActionFilterHue(const ActionFilterHue& obj) {
		*this = obj;
	}
	ActionFilterHue& operator=(const ActionFilterHue& obj) {
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);
		hueShift = obj.hueShift;

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterHue(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength, int hueShift);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterHue; }

	///Adds Hue to every pixel of the affected object/vieport
	///Accepted values: -359 - 359
	int	hueShift = 0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};