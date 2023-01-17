#include "Novel/Data/Visual/Scenery/Scenery.h"

void Scenery::render(SceneWidget* sceneWidget)
{
	if (sceneWidget)
	{
		//if (backgroundAssetImage_ && backgroundAssetImage_->isLoaded())
			//sceneWidget->changeBackground(backgroundAssetImage_->getImage());

		auto renderSceneryObject = [&sceneWidget](SceneryObject& sceneryObject)
		{
			AssetImage* sprite = sceneryObject.getAssetImage();
			if (sprite && sprite->isLoaded())
				sceneWidget->addSceneryObjectWidget(sceneryObject);
		};

		for (SceneryObject& displayedSceneryObject : displayedSceneryObjects_)
			renderSceneryObject(displayedSceneryObject);

		for (Character& displayedCharacter : displayedCharacters_)
			renderSceneryObject(displayedCharacter);
	}
}