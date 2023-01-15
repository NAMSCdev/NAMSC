#include "Novel/Action/Visual/ActionVisualAll.h"

#include "Novel/Data/Scene.h"

bool ActionSceneryObject::errorCheck(bool bComprehensive) const
{
	bool bError = Action::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (parentEvent->parentScene->scenery.getDisplayedSceneryObject(sceneryObjectName_) == nullptr)
		{
			qCritical() << NovelLib::ErrorType::SceneryObjectInvalid << "No valid SceneryObject assigned. Was it deleted and not replaced?";
			if (!sceneryObjectName_.isEmpty())
				qCritical() << NovelLib::ErrorType::SceneryObjectMissing << "SceneryObject \"" + sceneryObjectName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObject::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionCharacter::errorCheck(bool bComprehensive) const
{
	bool bError = Action::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (parentEvent->parentScene->scenery.getDisplayedCharacter(characterName_) == nullptr)
		{
			qCritical() << NovelLib::ErrorType::CharacterInvalid << "No valid Character assigned. Was it deleted and not replaced?";
			if (!characterName_.isEmpty())
				qCritical() << NovelLib::ErrorType::CharacterMissing << "Character \"" + characterName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionCharacter::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionSceneryObjectSetImage::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObject::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
			if (!assetImageName_.isEmpty())
				qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectSetImage::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionCharacterSetVoice::errorCheck(bool bComprehensive) const
{
	bool bError = ActionCharacter::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (voice_ == nullptr)
		{
			qCritical() << NovelLib::ErrorType::VoiceInvalid << "No valid Voice assigned. Was it deleted and not replaced?";
			if (!voiceName_.isEmpty())
				qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + voiceName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionCharacterSetVoice::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionSetBackground::errorCheck(bool bComprehensive) const
{
	bool bError = Action::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "No valid Background AssetImage assigned. Was it deleted and not replaced?";
			if (!assetImageName_.isEmpty())
				qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSetBackground::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}