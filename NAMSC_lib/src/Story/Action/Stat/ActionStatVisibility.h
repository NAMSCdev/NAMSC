#pragma once
#include "Global.h"

#include "Story/Action/Action.h"
#include "Story/Data/Stat/Stat.h"

//Sets the visibility of a Stat
class ActionStatVisibility final : public Action
{
public:
	ActionStatVisibility() = default;
	ActionStatVisibility(unsigned sceneID, unsigned eventExecutionOrder, QString &&statName, bool bNewVisibility, QString &&label = "") :
		Action(sceneID, eventExecutionOrder, move(label)), statName(move(statName)), bNewVisibility(bNewVisibility) {}

	//Executes Action's logic
	void				run					() override;

	//Accepts ActionVisitor
	void				accept				(ActionVisitor* visitor) override	{ visitor->visitActionStatVisibility(this); }
	
protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID		getType				() const override					{ return SerializationID::ActionStatVisibility; }

	//Name of the Stat that has its visibility changed
	QString				statName;
	//TODO: load Stat
	Stat				*stat;

	//Sets a Stat's visibility to this value
	bool				bNewVisibility;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> statName >> bNewVisibility;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << statName << bNewVisibility;
	}
};
