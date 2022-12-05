#include "Novel/Action/Visitor/ActionVisitorCorrectAsset.h"

#include "Novel/Data/Scene.h"

ActionVisitorCorrectAssetBase::ActionVisitorCorrectAssetBase(const QString& oldAssetName, const QString& newAssetName)
	: oldAssetName_(oldAssetName), newAssetName_(newAssetName) 
{
}

ActionVisitorCorrectAssetAnimColor::ActionVisitorCorrectAssetAnimColor(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectAssetAnimMove::ActionVisitorCorrectAssetAnimMove(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectAssetAnimRotate::ActionVisitorCorrectAssetAnimRotate(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectMusicPlaylist::ActionVisitorCorrectMusicPlaylist(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectSounds::ActionVisitorCorrectSounds(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectBackgroundAssetImage::ActionVisitorCorrectBackgroundAssetImage(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}

ActionVisitorCorrectSceneryObjectAssetImage::ActionVisitorCorrectSceneryObjectAssetImage(const QString& oldAssetName, const QString& newAssetName)
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName) 
{
}


void ActionVisitorCorrectAssetAnimColor::visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action)
{
	if (action->assetAnim_->name == oldAssetName_)
	{
		action->assetAnim_->unload();
		action->assetAnim_ = nullptr;
		action->assetAnim_ = AssetManager::getInstance().getAssetAnimColor(newAssetName_);
		if (action->assetAnim_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Color AssetAnim \"" << newAssetName_ << "\" does not exist. Asset replacement failed";
	}
}

void ActionVisitorCorrectAssetAnimMove::visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action)
{
	if (action->assetAnim_->name == oldAssetName_)
	{
		action->assetAnim_->unload();
		action->assetAnim_ = nullptr;
		action->assetAnim_ = AssetManager::getInstance().getAssetAnimMove(newAssetName_);
		if (action->assetAnim_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Move AssetAnim \"" << newAssetName_ << "\" does not exist. Asset replacement failed";
	}
}

void ActionVisitorCorrectAssetAnimRotate::visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action)
{
	if (action->assetAnim_->name == oldAssetName_)
	{
		action->assetAnim_->unload();
		action->assetAnim_ = nullptr;
		action->assetAnim_ = AssetManager::getInstance().getAssetAnimRotate(newAssetName_);
		if (action->assetAnim_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Rotate AssetAnim \"" << newAssetName_ << "\" does not exist. Asset replacement failed";
	}
}

ActionVisitorCorrectAssetAnimScale::ActionVisitorCorrectAssetAnimScale(const QString& oldAssetName, const QString& newAssetName) 
	: ActionVisitorCorrectAssetBase(oldAssetName, newAssetName)
{
}

void ActionVisitorCorrectAssetAnimScale::visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action)
{
	if (action->assetAnim_->name == oldAssetName_)
	{
		action->assetAnim_->unload();
		action->assetAnim_ = nullptr;
		action->assetAnim_ = AssetManager::getInstance().getAssetAnimScale(newAssetName_);
		if (action->assetAnim_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "Scale AssetAnim \"" << newAssetName_ << "\" does not exist. Asset replacement failed";
	}
}

void ActionVisitorCorrectMusicPlaylist::visitActionAudioSetMusic(ActionAudioSetMusic* action)
{
	for (QPair<QString, QString>& pair : action->musicPlaylist_.songs)
		if (pair.second == oldAssetName_)
			pair.second = newAssetName_;
}

void ActionVisitorCorrectSounds::visitActionAudioSetSounds(ActionAudioSetSounds* action) 
{
	for (Sound& sound : action->sounds)
		if (sound.soundFilePath == oldAssetName_)
			sound.soundFilePath = newAssetName_;
}

void ActionVisitorCorrectBackgroundAssetImage::visitActionSetBackground(ActionSetBackground* action) 
{
	if (action->assetImage_->name == oldAssetName_)
	{
		action->assetImage_->unload();
		action->assetImage_ = nullptr;
		action->assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(newAssetName_);
		if (action->assetImage_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << newAssetName_ << "\" does not exist. Definition file might be corrupted";
	}
}

void ActionVisitorCorrectSceneryObjectAssetImage::visitActionSceneryObjectSetImage(ActionSceneryObjectSetImage* action)
{
	if (action->assetImage_->name == oldAssetName_)
	{
		action->assetImage_->unload();
		action->assetImage_ = nullptr;
		action->assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(newAssetName_);
		if (action->assetImage_ == nullptr)
			qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" << newAssetName_ << "\" does not exist. Definition file might be corrupted";
	}
}