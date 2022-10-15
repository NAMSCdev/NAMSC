#pragma once
#include "Global.h"

#include "Story/Action/Visual/Filter/ActionFilter.h"

///[optional] Creates a Blur Filter at a SceneryObject or the Viewport
class ActionFilterBlur final : public ActionFilter
{
public:
	///Algorithm used for blurring
	enum class BlurType
	{
		Gaussian
	};

	ActionFilterBlur() = default;
	ActionFilterBlur(unsigned actionID, QString &&label, QString &&sceneryObjectName, double intensivness, 
					 double strength, BlurType blurType) :
		ActionFilter(actionID, move(label), move(sceneryObjectName), intensivness, strength), blurType(blurType) {}
	ActionFilterBlur(const ActionFilterBlur& obj) {	*this = obj; }
	ActionFilterBlur& operator=(const ActionFilterBlur& obj) 
	{
		if (this == &obj) return *this;

		ActionFilter::operator=(obj);
		blurType = obj.blurType;

		return *this;
	}

	///Executes Action's logic
	void run() override;

	///Accepts ActionVisitor
	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterBlur(this); }

signals:
	///A Qt signal executing after the Action's `run()` allowing for data read (and write if it is a pointer)
	void onRun(SceneryObject *sceneryObject, QPoint pos, QSize size, double intensivness, unsigned strength, BlurType blurType);

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override { return SerializationID::ActionFilterBlur; }

	///Algorithm used for blurring
	BlurType blurType = BlurType::Gaussian;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override;
};