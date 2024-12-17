//#pragma once
//#include "Global.h"
//
//#include "pvnLib/Novel/Action/Visual/ActionSceneryObject.h"
//
///// [optional] Base class for the rest of the ActionFilters
//class ActionFilter : public ActionSceneryObject
//{
//public:
//	ActionFilter() noexcept = default;
//	ActionFilter(QString&& sceneryObjectName, double intensivness, double strength);
//	ActionFilter(const ActionFilter& obj) noexcept { *this = obj; }
//	ActionFilter& operator=(const ActionFilter& obj) noexcept;
//
//protected:
//	//[optional] List of the ids that the filter will be applied on, empty list means all the parts
//	//QVector<uint> objectPartsAffected;
//
//	/// Sets the intensivness of the Filter, defined in percentage
//	/// Accepted values: 0.0 - 100.0
//	double intensivness	= 100.0;
//
//	/// Strength of the Effect, not all Filters use it. 
//	/// Intensivness is a multiplier for it
//	double strength = 1.0;
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//  /// \param dataStream Stream (presumably connected to a QFile) to read from
//	virtual void serializableLoad(QDataStream& dataStream) override;
//	/// Saving an object to a binary file
//  /// \param dataStream Stream (presumably connected to a QFile) to save to
//	virtual void serializableSave(QDataStream& dataStream) const override;
//};
//
//
//
//
//inline ActionFilter::ActionFilter(QString&& sceneryObjectName, double intensivness, double strength) :
//	ActionSceneryObject(move(sceneryObjectName)), intensivness(intensivness), strength(strength) 
//{
//}
//
//inline ActionFilter& ActionFilter::operator=(const ActionFilter& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionSceneryObject::operator=(obj);
//	intensivness = obj.intensivness;
//	strength     = obj.strength;
//
//	return *this;
//}