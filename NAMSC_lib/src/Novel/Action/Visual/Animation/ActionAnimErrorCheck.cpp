#include "Novel/Action/Visual/Animation/ActionAnimAll.h"

#include "Novel/Data/Scene.h"

template <class AnimNode>
bool ActionSceneryObjectAnim<AnimNode>::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObject::errorCheck(bComprehensive);

	static auto errorChecker = [this](bool bComprehensive)
	{
		if (assetAnim_ == nullptr)
		{
			qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "No valid AnimAsset assigned. Was it deleted and not replaced?";
			if (!assetAnimName_.isEmpty())
				qCritical() << NovelLib::ErrorType::AssetAnimMissing << "AssetAnim \"" + assetAnimName_ + "\" does not exist or read. Definition file might be corrupted";
		}
		else assetAnim_->errorCheck(bComprehensive);
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	//if (bError)
	//	qDebug() << "Error occurred in ActionSceneryObjectAnim::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

bool ActionSceneryObjectAnimColor::errorCheck(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::errorCheck(bComprehensive);

	//static auto errorChecker = [this](bool bComprehensive)
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

	//static auto errorChecker = [this](bool bComprehensive)
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

	//static auto errorChecker = [this](bool bComprehensive)
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

	//static auto errorChecker = [this](bool bComprehensive)
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

	//static auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimScale::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimInstances.h"