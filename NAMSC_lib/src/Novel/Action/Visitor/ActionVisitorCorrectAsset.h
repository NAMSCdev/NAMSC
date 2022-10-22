#pragma once
#include "Global.h"

#include "Novel/Action/ActionVisitor.h"
#include "Novel/Action/ActionsAll.h"

/// Updates `assetName` of a changed/deleted Asset
class ActionVisitorCorrectAsset : public ActionVisitor
{
public:
	ActionVisitorCorrectAsset(QString&& oldName, QString&& newName) : oldName(move(oldName)), newName(move(newName)) {}

protected:
	/// Every Action containing an Asset with its name equal to 'oldName' will have its name changed to `newName`
	/// Empty QString stands for invalid (it stands for invalid one - deleted)
	QString oldName,
			newName;
};

/// [optional] Updates `assetLive2DAnimName` of a changed/deleted AssetLive2DAnim
class ActionVisitorCorrectAssetLive2DAnim final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetLive2DAnim(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionLive2DAnim(ActionLive2DAnim* action) override 
	{ 
		if (action->assetLive2DAnimName == oldName)
			action->assetLive2DAnimName = newName;
	}
};

/// [optional] Updates `assetLive2DModelName` of a changed/deleted AssetLive2DModel
class ActionVisitorCorrectAssetLive2DModel final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetLive2DModel(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}
};

/// Updates `assetAnimName` of a changed/deleted **color** AssetAnim
class ActionVisitorCorrectAssetAnimColor final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetAnimColor(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override
	{
		if (action->assetAnimName == oldName)
			action->assetAnimName = newName;
	}
};

/// Updates `assetAnimName` of a changed/deleted **move** AssetAnim
class ActionVisitorCorrectAssetAnimMove final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetAnimMove(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override
	{
		if (action->assetAnimName == oldName)
			action->assetAnimName = newName;
	}
};

/// Updates `assetAnimName` of a changed/deleted **rotate** AssetAnim
class ActionVisitorCorrectAssetAnimRotate final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetAnimRotate(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override
	{
		if (action->assetAnimName == oldName)
			action->assetAnimName = newName;
	}
};

/// Updates `assetAnimName` of a changed/deleted **scale** AssetAnim
class ActionVisitorCorrectAssetAnimScale final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetAnimScale(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override
	{
		if (action->assetAnimName == oldName)
			action->assetAnimName = newName;
	}
};

/// Updates `assetAudioName` of a changed/deleted Music AssetAudio
class ActionVisitorCorrectMusicAssetAudio final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectMusicAssetAudio(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionChangeMusic(ActionChangeMusic* action) override
	{
		for (QString& name : action->assetAudioNames)
			if (name == oldName)
				name = newName;
	}
};

/// Updates `assetAudioName` of a changed/deleted Sound AssetAudio
class ActionVisitorCorrectSoundAssetAudio final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectSoundAssetAudio(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionPlaySound(ActionPlaySound* action) override
	{
		for (QString& name : action->assetAudioNames)
			if (name == oldName)
				name = newName;
	}
};

/// Updates `assetImageName` of a changed/deleted background AssetImage
class ActionVisitorCorrectBackgroundAssetImage final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectBackgroundAssetImage(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSetBackground(ActionSetBackground* action) override
	{
		if (action->assetImageName == oldName)
			action->assetImageName = newName;
	}
};

/// Updates `assetImageName` of a changed/deleted AssetImage
class ActionVisitorCorrectSceneryObjectAssetImage final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectSceneryObjectAssetImage(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectImageChange(ActionSceneryObjectImageChange* action) override
	{
		if (action->assetImageName == oldName)
			action->assetImageName = newName;
	}
};