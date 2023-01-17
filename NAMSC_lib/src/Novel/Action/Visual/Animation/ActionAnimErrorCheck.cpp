#include "Novel/Action/Visual/Animation/ActionAnimAll.h"

#include "Novel/Data/Scene.h"

//template <class AnimNode>
//bool ActionSceneryObjectAnim<AnimNode>::errorCheck(bool bComprehensive) const

bool ActionSceneryObjectAnimColor::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimColor::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionSceneryObjectAnimFade::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimFade::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}


bool ActionSceneryObjectAnimMove::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimMove::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionSceneryObjectAnimRotate::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimRotate::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}


bool ActionSceneryObjectAnimScale::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimScale::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}