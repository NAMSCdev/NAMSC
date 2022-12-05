//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Hue Filter at a SceneryObject or the entire Viewport
//class ActionFilterHue final : public ActionFilter
//{
//public:
//	ActionFilterHue() noexcept = default;
//	ActionFilterHue(QString&& sceneryObjectName, double intensivness, double strength, int hueShift);
//	ActionFilterHue(const ActionFilterHue& obj) noexcept { *this = obj; }
//	ActionFilterHue& operator=(const ActionFilterHue& obj) noexcept;
//
//	/// Executes the ActionFilterHue's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterHue(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterHue's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength, int hueShift) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionFilterHue; }
//
//	/// Adds Hue to every pixel of the affected object/vieport
//	/// Accepted values: -359 - 359
//	int	hueShift = 0;
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
//inline ActionFilterHue::ActionFilterHue(QString&& sceneryObjectName, double intensivness, double strength, int hueShift) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength), hueShift(hueShift) 
//{
//
//}
//
//inline ActionFilterHue& ActionFilterHue::operator=(const ActionFilterHue& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//	hueShift = obj.hueShift;
//
//	return *this;
//}