#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

//Changes scene basic a SceneryObject or the viewport
class ActionSceneryObjectChange final : public Action
{
public:
	ActionSceneryObjectChange() = default;
	ActionSceneryObjectChange(unsigned sceneID, unsigned eventExecutionOrder, QString &&sceneryObjectURI, 
		std::vector<QPair<unsigned, QString>> &&sceneryObjectParts, QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), sceneryObjectName(move(sceneryObjectName)),
				sceneryObjectParts(move(sceneryObjectParts)) {}

	//Executes Action's logic
	void									run						() override;

	//Accepts ActionVisitor
	void									accept					(ActionVisitor* visitor) override	{ visitor->visitActionSceneryObjectChange(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID							getType					() const override					{ return SerializationID::ActionSceneryObjectChange; }

	//URI to the Scenery Object, so it can be loaded (if needed) and replaced
	QString									sceneryObjectName;

	//URI to the Images that will replace SceneryObjectPart's images identified by IDs
	std::vector<QPair<unsigned, QString>>	sceneryObjectParts;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		unsigned sceneryObjectURISize;
		dataStream >> sceneryObjectName >> sceneryObjectURISize;
		for (unsigned i = 0u; i != sceneryObjectURISize; ++i)
		{
			QPair<unsigned, QString> part;
			dataStream >> part;
			sceneryObjectParts.push_back(part);
		}
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << sceneryObjectName << sceneryObjectParts.size();
		for (const QPair<unsigned, QString> &part : sceneryObjectParts)
			dataStream << part;
	}
};