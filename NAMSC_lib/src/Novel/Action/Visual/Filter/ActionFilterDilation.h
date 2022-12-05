//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Dilation Filter at a SceneryObject or the entire Viewport
//class ActionFilterDilation final : public ActionFilter
//{
//public:
//	ActionFilterDilation() noexcept = default;
//	ActionFilterDilation(QString&& sceneryObjectName, double intensivness, double strength);
//	ActionFilterDilation(const ActionFilterDilation& obj) noexcept { *this = obj; }
//	ActionFilterDilation& operator=(const ActionFilterDilation& obj) noexcept;
//	
//	/// Executes the ActionFilterDilation's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override	{ visitor->visitActionFilterDilation(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterDilation's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override		{ return SerializationID::ActionFilterDilation; }
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
//inline ActionFilterDilation::ActionFilterDilation(QString&& sceneryObjectName, double intensivness, double strength) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength) 
//{
//}
//
//inline ActionFilterDilation& ActionFilterDilation::operator=(const ActionFilterDilation& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//
//	return *this;
//}