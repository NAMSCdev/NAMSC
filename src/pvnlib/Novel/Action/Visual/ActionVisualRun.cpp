#include "pvnLib/Novel/Action/Visual/ActionVisualAll.h"

void ActionSceneryObject::run()
{
	Action::run();

	sceneryObject_ = NovelState::getCurrentlyLoadedState()->scenery.getDisplayedSceneryObject(sceneryObjectName_);
}

void ActionCharacter::run()
{
	Action::run();

	character_ = NovelState::getCurrentlyLoadedState()->scenery.getDisplayedCharacter(characterName_);
}

void ActionCharacterSetVoice::run()
{
	ActionCharacter::run();

	character_->setDefaultVoice(voiceName_);

	if (onRun_)
		onRun_(parentEvent, character_, voice_);
}

void ActionSceneryObjectSetImage::run()
{
	ActionSceneryObject::run();

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, assetImage_->getImage());
}

void ActionSetBackground::run()
{
	Action::run();

	if (onRun_)
		onRun_(parentEvent, assetImage_->getImage(), transitionType, transitionTime);
}