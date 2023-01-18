#include "Novel/Data/Visual/Scenery/Scenery.h"

#include "Novel/Data/Novel.h"
#include "Novel/Widget/SceneWidget.h"

void Scenery::render(SceneWidget* sceneWidget)
{
	if (sceneWidget)
	{
		Novel& novel = Novel::getInstance();
		if (backgroundAssetImage_)
			emit novel.pendBackgroundDisplay(backgroundAssetImage_->getImage());

		emit novel.pendSceneryObjectsDisplay(displayedSceneryObjects_);

		emit novel.pendCharactersDisplay(displayedCharacters_);
	}
}