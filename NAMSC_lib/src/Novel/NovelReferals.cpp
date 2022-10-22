#include "Global.h"
#include "Novel/Data/Novel.h"

#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

#include "Novel/Action/Visual/ActionSceneryObject.h"
#include "Novel/Action/Visual/ActionSceneryObjectVoiceChange.h"

//Code that contains references to Novel from structures that are within it
//Potentially dangerous

ActionSceneryObject::ActionSceneryObject(QString&& sceneryObjectName) :
	Action(), sceneryObjectName(move(sceneryObjectName))
{
	sceneryObject = Novel::getInstance().findSceneryObject(this->sceneryObjectName);
}

AnimatorSceneryObjectInterface::AnimatorSceneryObjectInterface(QTime startTime, double speed, int timesPlayed, QString&& animAssetName, QString&& sceneryObjectName) :
	AnimatorInterface(startTime, speed, timesPlayed, move(animAssetName)), sceneryObjectName(move(sceneryObjectName))
{
	sceneryObject = Novel::getInstance().findSceneryObject(this->sceneryObjectName);
}

ActionSceneryObjectVoiceChange::ActionSceneryObjectVoiceChange(QString&& sceneryObjectName, QString&& voiceName) :
	ActionSceneryObject(move(sceneryObjectName)), voiceName(move(voiceName))
{
	voice = Novel::getInstance().findVoice(this->voiceName);
}