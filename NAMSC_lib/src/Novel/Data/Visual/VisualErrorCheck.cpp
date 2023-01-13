#include "Novel/Data/Visual/Scenery/Scenery.h"

bool SceneryObject::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (!assetImage_)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ != "")
				qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		}
		else assetImage_->errorCheck(bComprehensive);
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in SceneryObject::errorCheck (object's name: \"" + name << ")\"";

	return bError;
}

bool Character::errorCheck(bool bComprehensive) const
{
	bool bError = SceneryObject::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		//Check if the name is undefined
		//if (defaultVoiceName_ == "")
		//{
		//	bError = true;
		//	qCritical() << NovelLib::ErrorType::VoiceInvalid << "No Voice assigned. Was it deleted and not replaced?";
		//}
		//Check if there is a Voice with this name in the Novel's container 
		//else if (Novel::getInstance().getVoice(defaultVoiceName_) == nullptr)
		//{
		//	bError = true;
		//	qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + defaultVoiceName_ + "\" does not exist. Definition file might be corrupted";
		//}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Character::errorCheck (object's name: \"" + name + "\")";

	return bError;
}

bool Scenery::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	if (backgroundAssetImage_)
		bError |= backgroundAssetImage_->errorCheck(bComprehensive);

	bError |= musicPlaylist.errorCheck(bComprehensive);

	for (const std::pair<const QString, Character>& character : displayedCharacters_)
		bError |= character.second.errorCheck(bComprehensive);

	for (const std::pair<const QString, SceneryObject>& sceneryObject : displayedSceneryObjects_)
		bError |= sceneryObject.second.errorCheck(bComprehensive);

	for (const std::pair<const QString, Sound>& sound : sounds_)
		bError |= sound.second.errorCheck(bComprehensive);

	//static auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Scenery::errorCheck";

	return bError;
}