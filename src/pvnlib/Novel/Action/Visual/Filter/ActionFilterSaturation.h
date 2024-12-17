//#pragma once
//#include "Global.h"
//
//#include "pvnLib/Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Saturation Filter at a SceneryObject or the entire Viewport
//class ActionFilterSaturation final: public ActionFilter
//{
//public:
//	ActionFilterSaturation() noexcept = default;
//	ActionFilterSaturation(QString&& sceneryObjectName, double intensivness, double strength, int addedSaturation, double percentSaturation);
//	ActionFilterSaturation(const ActionFilterSaturation& obj) noexcept { *this = obj; }
//	ActionFilterSaturation& operator=(const ActionFilterSaturation& obj) noexcept;
//
//	/// Executes the ActionFilterSaturation's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterSaturation(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterSaturation's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength, int addedSaturation, double percentSaturation) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionFilterSaturation; }
//
//	/// Adds Saturation to every pixel of the affected object/vieport
//	/// Accepted values: -100 - 100
//	int	addedSaturation	= 0;
//
//	/// Modifies percent value of Saturation in every pixel of the affected object/vieport
//	/// Accepted values: 0.0 - 100.0
//	double percentSaturation = 100.0;
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file 7
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
//inline ActionFilterSaturation::ActionFilterSaturation(QString&& sceneryObjectName, double intensivness, double strength, int addedSaturation, double percentSaturation) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength), addedSaturation(addedSaturation), percentSaturation(percentSaturation)
//{
//}
//
//inline ActionFilterSaturation& ActionFilterSaturation::operator=(const ActionFilterSaturation& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//	addedSaturation   = obj.addedSaturation;
//	percentSaturation = obj.percentSaturation;
//
//	return *this;
//}