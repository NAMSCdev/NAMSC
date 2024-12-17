#include "pvnLib/Novel/Data/Visual/Scenery/Scenery.h"
#include "pvnLib/Novel/Widget/SceneWidget.h"

#include "pvnLib/Novel/Data/Novel.h"
#include "pvnLib/Novel/Widget/SceneWidget.h"

void Scenery::render(SceneWidget* sceneWidget) const
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