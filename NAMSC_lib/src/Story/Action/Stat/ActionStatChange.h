#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

#include "Story/Data/Stat/Stat.h"
#include "Story/Data/Stat/StatManager.h"

//Assigns a new value to a Stat
class ActionStatChange final : public Action
{
public:
	ActionStatChange() = default;
	ActionStatChange(unsigned sceneID, unsigned eventExecutionOrder, QString &&statName, QString &&expression, QString &&label = "") :
		Action(sceneID, eventExecutionOrder, move(label)), statName(move(statName)), expression(move(expression)) {}

	//Executes Action's logic
	void				run					() override;

	//Accepts ActionVisitor
	void				accept				(ActionVisitor* visitor) override	{ visitor->visitActionStatChange(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID		getType				() const override					{ return SerializationID::ActionStatChange; }

	//Checks if there are no errors in [statName] or [expression]
	void				checkForErrors		();

	//Name of the Stat that has its value changed
	QString				statName;
	//TODO: load Stat
	Stat				*stat;

	//New value of the Stat is calculated from this expression
	QString				expression;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> statName >> expression;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << statName << expression;
	}
};
