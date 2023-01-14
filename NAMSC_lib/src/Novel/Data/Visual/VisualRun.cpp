#include "Novel/Data/Visual/Scenery/Scenery.h"

void SceneryObject::run()
{
	for (AnimatorSceneryObjectColor&  animator : animatorsColor_)
		animator.run();

	for (AnimatorSceneryObjectFade&   animator : animatorsFade_)
		animator.run();

	for (AnimatorSceneryObjectRotate& animator : animatorsRotate_)
		animator.run();

	for (AnimatorSceneryObjectMove&   animator : animatorsMove_)
		animator.run();

	for (AnimatorSceneryObjectScale&  animator : animatorsScale_)
		animator.run();
}

void Scenery::run()
{
	for (std::pair<const QString, Character>&     character     : displayedCharacters_)
		character.second.run();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.run();
}