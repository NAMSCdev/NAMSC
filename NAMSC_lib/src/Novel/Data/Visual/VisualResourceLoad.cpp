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
	for (std::pair<const QString, Character>& character : displayedCharacters_)
		character.second.ensureResourcesAreLoaded();

	for (std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		sceneryObject.second.ensureResourcesAreLoaded();

	//todo: add QSoundEffect from Widget
	for (std::pair<const QString, Sound>& sound : sounds_)
		if (!sound.second.isLoaded())
			sound.second.load();

	if (!backgroundAssetImage_->isLoaded())
		backgroundAssetImage_->load();
}