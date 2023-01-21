#include "Novel/Data/Novel.h"

bool Novel::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	for (const std::pair<const QString, Voice>& voice : voices_)
		bError |= voice.second.errorCheck(bComprehensive);

	for (const std::pair<const QString, SceneryObject>& defaultSceneryObject : sceneryObjectDefaults_)
		bError |= defaultSceneryObject.second.errorCheck(bComprehensive);

	for (const std::pair<const QString, Character>& defaultCharacter : characterDefaults_)
		bError |= defaultCharacter.second.errorCheck(bComprehensive);

	for (const std::pair<const QString, Scene>& scene : scenes_)
		bError |= scene.second.errorCheck(bComprehensive);

	bError |= stateAtSceneBeginning_.errorCheck();
	bError |= state_.errorCheck();
	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);

	return bError;
}

bool Scene::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	for (const std::shared_ptr<Event>& event : events_)
		bError |= event->errorCheck(bComprehensive);

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	//if (bError)
	//    qDebug() << "An Error occurred in Scene::errorCheck (object's name: \"" + name + "\")";

	return bError;
}