#pragma once
#include "Global.h"

#include "Story/Action/Action.h"
#include "Story/Data/Visual/Animation/Animator.h"
#include "Story/Data/Visual/Scenery/SceneryObject.h"

//[optional] Animates a Character with Live2D
//Could be synced with the Speech, have custom duration, or infinite one
class ActionSceneryObjectAnim final : public Action
{
public:
	ActionSceneryObjectAnim() = default;
	ActionSceneryObjectAnim(unsigned sceneID, unsigned eventExecutionOrder, QString &&animURI, QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), animURI(move(animURI)) {}

	//Executes Action's logic
	void					run						() override;
	
	//Accepts ActionVisitor
	void					accept					(ActionVisitor* visitor) override	{ visitor->visitActionSceneryObjectAnim(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType					() const override					{ return SerializationID::ActionSceneryObjectAnim; }

	//Ensures Assets are loaded and if not - loads it
	void					ensureAssetsAreLoaded	() override							{ /*animator->load();*/ }

	//URI to the Scenery Object, so it can be loaded (if needed) and replaced
	QString					sceneryObjectURI;
	//TODO: load Scenery Object
	SceneryObject			*sceneryObject;

	//URI to the Animation, so it can be loaded (if needed) and replaced
	QString					animURI;
	//TODO: think how to fix this... template the action? untemplate the animator (like Stats are now)?
	//uPtr<Animator>			animator;

	//Duration of the animation in seconds
	//0 stands for infinite
	double					duration													= 0.0;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> sceneryObjectURI /* >> animURI */ >> duration;
		animator->serializableLoad(ar);
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << sceneryObjectURI /* << animURI */ << duration;
		animator->serializableSave(ar);
	}
};
