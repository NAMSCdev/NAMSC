//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Erosion Filter at a SceneryObject or the entire Viewport
//class ActionFilterErosion final : public ActionFilter
//{
//public:
//	ActionFilterErosion() noexcept = default;
//	ActionFilterErosion(QString&& sceneryObjectName, double intensivness, double strength);
//	ActionFilterErosion(const ActionFilterErosion& obj) noexcept { *this = obj; }
//	ActionFilterErosion& operator=(const ActionFilterErosion& obj) noexcept;
//	
//	/// Executes the ActionFilterErosion's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterErosion(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterErosion's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionFilterErosion; }
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
//inline ActionFilterErosion::ActionFilterErosion(QString&& sceneryObjectName, double intensivness, double strength) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength) 
//{
//}
//
//inline ActionFilterErosion& ActionFilterErosion::operator=(const ActionFilterErosion& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//
//	return *this;
//}