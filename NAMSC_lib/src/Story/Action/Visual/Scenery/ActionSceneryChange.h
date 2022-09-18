#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

//Changes Scene's background Image and/or UI theme
class ActionSceneryChange final : public Action
{
public:
	//Blends the scene change with an animation
	enum class TransitionType
	{
		CrossFade,
		SweepRight
	};

	ActionSceneryChange() = default;
	ActionSceneryChange(unsigned sceneID, unsigned eventExecutionOrder, QString &&backgroundURI, TransitionType transitionType = TransitionType::CrossFade,
		double transitionTime = 0.33, QString &&themeURI = "", QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), backgroundURI(move(backgroundURI)), transitionType(transitionType),
				transitionTime(transitionTime), themeURI(move(themeURI)) {}

	//Executes Action's logic
	void					run					() override;

	//Accepts ActionVisitor
	void					accept				(ActionVisitor* visitor) override	{ visitor->visitActionSceneryChange(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID			getType				() const override					{ return SerializationID::ActionSceneryChange; }

	//URI to the background Image, so it can be loaded (if needed) and replaced
	QString					backgroundURI;

	//Blends the scene change with an animation
	TransitionType			transitionType											= TransitionType::CrossFade;

	//Time the transtition takes to move from one Image into another in seconds
	double					transitionTime											= 1.0;

	//URI to the UI theme, so it can be loaded (if needed) and replaced
	QString					themeURI												= "";

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> backgroundURI >> transitionType >> transitionTime >> themeURI;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << backgroundURI << transitionType << transitionTime << themeURI;
	}
};