#include "Novel/Data/Visual/Scenery/Scenery.h"
#include "Novel/Widget/SceneWidget.h"

#include "Novel/Data/Novel.h"
#include "Novel/Widget/SceneWidget.h"

void Scenery::render(SceneWidget* sceneWidget) const
{
	if (sceneWidget)
	{
		//if (backgroundAssetImage_ && backgroundAssetImage_->isLoaded())
			//sceneWidget->changeBackground(backgroundAssetImage_->getImage());

		emit novel.pendSceneryObjectsDisplay(displayedSceneryObjects_);

		emit novel.pendCharactersDisplay(displayedCharacters_);
	}
}