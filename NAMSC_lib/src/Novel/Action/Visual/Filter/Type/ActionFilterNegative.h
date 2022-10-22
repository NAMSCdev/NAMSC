//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Negation Filter at a SceneryObject or the viewport
///// "Flips" colors
//class ActionFilterNegative final : public ActionFilter
//{
//public:
//	ActionFilterNegative() noexcept = default;
//	ActionFilterNegative(QString&& sceneryObjectName, double intensivness, double strength);
//	ActionFilterNegative(const ActionFilterNegative& obj) noexcept { *this = obj; };
//
//	/// Executes the ActionFilterNegative's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterNegative(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterNegative's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//	SerializationID	getType() const override { return SerializationID::ActionFilterNegative; }
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to read from
//	void serializableLoad(QDataStream& dataStream) override;
//	/// Saving an object to a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to save to
//	void serializableSave(QDataStream& dataStream) const override;
//};
//
//
//
//
//inline ActionFilterNegative::ActionFilterNegative(QString&& sceneryObjectName, double intensivness, double strength) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength)
//{
//}
//
//inline ActionFilterNegative& ActionFilterNegative::operator=(const ActionFilterNegative& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//
//	return *this;
//}