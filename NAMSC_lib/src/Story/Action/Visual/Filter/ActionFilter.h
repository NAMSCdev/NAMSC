#pragma once
#include "Global.h"

#include "Story/Action/Visual/ActionSceneryObject.h"

///[optional] Base class for the rest of the ActionFilters
class ActionFilter : public ActionSceneryObject
{
public:
	ActionFilter() = default;
	ActionFilter(Event *parent, unsigned actionID, QString &&label, QString &&sceneryObjectName, double intensivness, double strength) :
		ActionSceneryObject(parent, actionID, move(label), move(sceneryObjectName)), intensivness(intensivness), strength(strength) {}
	ActionFilter(const ActionFilter& asset)				= default;
	ActionFilter& operator=(const ActionFilter& asset)	= default;

protected:
	//[optional] List of the ids that the filter will be applied on, empty list means all the parts
	//QVector<unsigned> objectPartsAffected;

	///Sets the intensivness of the Filter, defined in percentage
	///Accepted values: 0.0 - 100.0
	double	intensivness	= 100.0;

	///Strength of the Effect, not all Filters use it. 
	///Intensivness is a multiplier for it
	double	strength		= 1.0;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const override;
};