//#pragma once
//#include "Global.h"
//
//#include "pvnLib/Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Brightnss Filter at a SceneryObject or the entire Viewport
//class ActionFilterBrightness final : public ActionFilter
//{
//public:
//	ActionFilterBrightness() noexcept = default;
//	ActionFilterBrightness(QString &&sceneryObjectName, double addedBrightness, 
//						   double percentBrightness, double intensivness, double strength);
//	ActionFilterBrightness(const ActionFilterBrightness& obj) noexcept { *this = obj; }
//	ActionFilterBrightness& operator=(const ActionFilterBrightness& obj) noexcept;
//
//	/// Executes the ActionFilterBrightness's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterBrightness(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterBrightness's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength, double addedBrightness, double percentBrightness) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionFilterBrightness; }
//
//	/// Adds Brightness to every pixel of the affected object/vieport
//	/// Accepted values: 0.0 - 1.0
//	double	addedBrightness	= 0.0;
//
//	/// Modifies percent value of Brightness in every pixel of the affected object/vieport
//	/// Accepted values: 0.0 - 100.0
//	double	percentBrightness = 100.0;
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
//inline ActionFilterBrightness::ActionFilterBrightness(QString&& sceneryObjectName, double addedBrightness, 
//													  double percentBrightness, double intensivness, double strength) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength), addedBrightness(addedBrightness), percentBrightness(percentBrightness) 
//{
//}
//
//inline ActionFilterBrightness& ActionFilterBrightness::operator=(const ActionFilterBrightness& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//	addedBrightness        = obj.addedBrightness;
//	percentBrightness      = obj.percentBrightness;
//
//	return *this;
//}