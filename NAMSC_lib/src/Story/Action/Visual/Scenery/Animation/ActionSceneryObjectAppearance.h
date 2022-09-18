#pragma once
#include "Global.h"

#include "Story/Action/Action.h"

//Makes an Scene Object appear or dissapear
class ActionSceneryObjectAppearance final : public Action
{
public:
	//Available effects for the appearing animatio
	enum class AppearEffectType
	{
		FadeIn
	};

	ActionSceneryObjectAppearance() = default;
	ActionSceneryObjectAppearance(unsigned sceneID, unsigned eventExecutionOrder, int characterID, QString &&sceneryObjectName,
		AppearEffectType appearEffectType = AppearEffectType::FadeIn, double duration = 0.1, bool bAppear = true, bool bPerserveAnimation = false, QString &&label = "") :
			Action(sceneID, eventExecutionOrder, move(label)), sceneryObjectURI(move(sceneryObjectURI)), appearEffectType(appearEffectType), duration(duration),
				bAppear(bAppear), bPerserveAnimation(bPerserveAnimation) {}

	//Executes Action's logic
	void				run						() override;

	//Accepts ActionVisitor
	void				accept					(ActionVisitor* visitor) override	{ visitor->ActionSceneryObjectAppearance(this); }

protected:
	//Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID		getType					() const override					{ return SerializationID::ActionSceneryObjectAppearance; }

	//Ensures Assets are loaded and if not - loads it
	void				ensureAssetsAreLoaded	() override							{ dasd }

	//Available effects for the appearing animatio
	AppearEffectType	appearEffectType;

	//URI to the Scenery Object, so it can be loaded (if needed) and replaced
	QString				sceneryObjectURI;

	//Duration of the [appearEffect] in seconds
	double				duration													= 0.1;

	//Whether is it Appear animation or Dissapear animation
	bool				bAppear														= true;

	//If it is a GIF, play its animation during the appear animation
	//[optional] If it is a Live2D animated, it will keep on playing its animation during the appear animation
	bool				bPerserveAnimation											= false;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		Action::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> appearEffectType >> sceneryObjectURI >> duration >> bAppear >> bPerserveAnimation;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		Action::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << appearEffectType << sceneryObjectURI << duration << bAppear << bPerserveAnimation;
	}
};
