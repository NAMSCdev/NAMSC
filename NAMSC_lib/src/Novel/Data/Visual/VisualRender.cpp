#include "Novel/Data/Visual/Scenery/Scenery.h"
#include "Novel/Widget/SceneWidget.h"

#include "Novel/Data/Novel.h"
#include "Novel/Widget/SceneWidget.h"

void Scenery::render(SceneWidget* sceneWidget) const
{
	if (sceneWidget)
	{
		Novel& novel = Novel::getInstance();
		if (backgroundAssetImage_)
			emit novel.pendBackgroundDisplay(backgroundAssetImage_->getImage());

		sceneWidget->clearSceneryObjectWidgets();
		auto renderSceneryObject = [&sceneWidget](SceneryObject& sceneryObject)
		{
			AssetImage* sprite = sceneryObject.getAssetImage();
			if (sprite && sprite->isLoaded())
				sceneWidget->addSceneryObjectWidget(sceneryObject);
		};

		for (SceneryObject& displayedSceneryObject : displayedSceneryObjects_)
			renderSceneryObject(displayedSceneryObject);

		emit novel.pendSceneryObjectsDisplay(displayedSceneryObjects_);

		emit novel.pendCharactersDisplay(displayedCharacters_);
	}
}