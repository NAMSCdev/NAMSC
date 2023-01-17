#include "Novel/Data/Visual/Scenery/Scenery.h"

void SceneryObject::ensureResourcesAreLoaded()
{
	if (!assetImage_)
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	if (!assetImage_)
	{
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		return;
	}
	if (!assetImage_->isLoaded())
		assetImage_->load();
}

void Scenery::ensureResourcesAreLoaded()
{
	for (Character& character : displayedCharacters_)
		character.ensureResourcesAreLoaded();

	for (SceneryObject& sceneryObject : displayedSceneryObjects_)
		sceneryObject.ensureResourcesAreLoaded();

	//todo: add QSoundEffect from Widget
	for (Sound& sound : sounds_)
		if (!sound.isLoaded())
			sound.load();

	if (!backgroundAssetImage_->isLoaded())
		backgroundAssetImage_->load();
}