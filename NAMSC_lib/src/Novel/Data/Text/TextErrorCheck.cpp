#include "Novel/Data/Text/Choice.h"
#include "Novel/Data/Text/Sentence.h"

#include "Novel/Data/Scene.h"
#include "Exceptions.h"

bool Choice::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (jumpToSceneName == "")
			qCritical() << NovelLib::ErrorType::JumpInvalid << "Choice is missing a jumpToSceneName";

		//todo: check `condition`
	};

	bError |= choiceDisplayOptions.errorCheck(bComprehensive) || NovelLib::catchExceptions(errorChecker, bComprehensive);
	qDebug() << "Error occurred in Choice::errorCheck";

	return bError;
}

bool Choice::ChoiceDisplayOptions::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		//if (fontName_ == "")
			//qCritical() << NovelLib::ErrorType::General << "No Font set";
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ChoiceDisplayOptions::errorCheck";

	return bError;
}

bool Sentence::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		//Check AssetImage
		//if (!assetImage_)
		//{
		//	qCritical() << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
		//	if (!assetImageName_.isEmpty())
		//		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		//}
		//Check Character
		if (!characterName_.isEmpty() && parentEvent->parentScene->scenery.getDisplayedCharacter(characterName_) == nullptr)
		{
			qCritical() << NovelLib::ErrorType::CharacterInvalid << "No valid Character assigned. Was it deleted and not replaced?";
			if (!characterName_.isEmpty())
				qCritical() << NovelLib::ErrorType::CharacterMissing << "Character \"" + characterName_ + "\" does not exist. Definition file might be corrupted";
		}
		//Check Voice
		//if (voice_ == nullptr)
		//{
		//	qCritical() << NovelLib::ErrorType::VoiceInvalid << "No valid Voice assigned. Was it deleted and not replaced?";
		//	if (!voiceName_.isEmpty())
		//		qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + voiceName_ + "\" does not exist. Definition file might be corrupted";
		//}
	};

	if (NovelLib::catchExceptions(errorChecker, bComprehensive) || translation.errorCheck(bComprehensive))
		qDebug() << "An Error occurred in Sentence::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool Translation::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (!translations_.contains(NovelSettings::getInstance().defaultLanguage))
			qCritical() << NovelLib::ErrorType::General << "Translation doesn't have default language set";
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);

	if (bError)
		qDebug() << "Error occurred in Translation::errorCheck";

	return bError;
}

bool Voice::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (fontName_ == "")
			qCritical() << NovelLib::ErrorType::General << "No Font set";
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Voice::errorCheck \"" + name + '\"';

	return bError;
}