#pragma once
#include "Global.h"

#include "Novel/Action/ActionVisitor.h"

#include "Novel/Action/ActionsAll.h"

///Updates `name` of a changed Asset
class ActionVisitorCorrectAsset : public ActionVisitor
{
public:
	ActionVisitorCorrectAsset(QString&& oldName, QString&& newName) : oldName(move(oldName)), newName(move(newName)) {}

protected:
	///Every Action containing an Asset with name equal to 'oldName' will have its name updated to `newName`
	///Empty QString stands for invalid (happens after deletion)
	QString oldName,
			newName;
};

///Updates `live2DAnimAssetName` of a changed Asset
class ActionVisitorCorrectLive2DAnimAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectLive2DAnimAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	///[optional]
	void visitActionLive2DAnim(ActionLive2DAnim* action) override 
	{ 
		if (action->assetLive2DAnimName == oldName)
			action->assetLive2DAnimName = newName;
	}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectLive2DModelAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectLive2DModelAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAnimMoveAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimMoveAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override
	{
		if (action->animAssetName == oldName)
			action->animAssetName = newName;
	}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAnimScaleAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimScaleAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override
	{
		if (action->animAssetName == oldName)
			action->animAssetName = newName;
	}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAnimRotateAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimRotateAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override
	{
		if (action->animAssetName == oldName)
			action->animAssetName = newName;
	}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAnimColorAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimColorAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override
	{
		if (action->animAssetName == oldName)
			action->animAssetName = newName;
	}
};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAssetFont final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAssetFont(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAssetImage final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionChangeMusic(ActionChangeMusic* action) override { changeID(action); }
	void visitActionPlaySound(ActionPlaySound* action) override { changeID(action); }

	void visitActionStatChange(ActionStatChange* action) override { changeID(action); }

	void visitActionSetBackground(ActionSetBackground* action) override { changeID(action); }
	void visitActionSceneryObjectImageChange(ActionSceneryObjectImageChange* action) override { changeID(action); }
	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override { changeID(action); }
	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override { changeID(action); }
	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override { changeID(action); }
	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override { changeID(action); }
	void visitActionSceneryObjectVisibilityChange(ActionSceneryObjectVisibilityChange* action) override { changeID(action); }

	///[optional]
	void visitActionStatVisibility(ActionStatVisibility* action) override { changeID(action); }

	void visitActionEffectBlur(ActionEffectBlur* action) override { changeID(action); }
	void visitActionEffectDistort(ActionEffectDistort* action) override { changeID(action); }
	void visitActionEffectGlow(ActionEffectGlow* action) override { changeID(action); }

	void visitActionFilterBlur(ActionFilterBlur* action) override { changeID(action); }
	void visitActionFilterBrightness(ActionFilterBrightness* action) override { changeID(action); }
	void visitActionFilterDilation(ActionFilterDilation* action) override { changeID(action); }
	void visitActionFilterErosion(ActionFilterErosion* action) override { changeID(action); }
	void visitActionFilterHue(ActionFilterHue* action) override { changeID(action); }
	void visitActionFilterNegative(ActionFilterNegative* action) override { changeID(action); }
	void visitActionFilterSaturation(ActionFilterSaturation* action) override { changeID(action); }

	void visitActionCharLive2DAnim(ActionCharLive2DAnim* action) override { changeID(action); }

};

///Updates `name` of a changed Asset
class ActionVisitorCorrectAnimAsset final : public ActionVisitorCorrectAsset
{
public:
	ActionVisitorCorrectAnimAsset(QString&& oldName, QString&& newName) : ActionVisitorCorrectAsset(move(oldName), move(newName)) {}

	void visitActionChangeMusic(ActionChangeMusic* action) override { changeID(action); }
	void visitActionPlaySound(ActionPlaySound* action) override { changeID(action); }

	void visitActionStatChange(ActionStatChange* action) override { changeID(action); }

	void visitActionSetBackground(ActionSetBackground* action) override { changeID(action); }
	void visitActionSceneryObjectImageChange(ActionSceneryObjectImageChange* action) override { changeID(action); }
	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override { changeID(action); }
	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override { changeID(action); }
	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override { changeID(action); }
	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override { changeID(action); }
	void visitActionSceneryObjectVisibilityChange(ActionSceneryObjectVisibilityChange* action) override { changeID(action); }

	///[optional]
	void visitActionStatVisibility(ActionStatVisibility* action) override { changeID(action); }

	void visitActionEffectBlur(ActionEffectBlur* action) override { changeID(action); }
	void visitActionEffectDistort(ActionEffectDistort* action) override { changeID(action); }
	void visitActionEffectGlow(ActionEffectGlow* action) override { changeID(action); }

	void visitActionFilterBlur(ActionFilterBlur* action) override { changeID(action); }
	void visitActionFilterBrightness(ActionFilterBrightness* action) override { changeID(action); }
	void visitActionFilterDilation(ActionFilterDilation* action) override { changeID(action); }
	void visitActionFilterErosion(ActionFilterErosion* action) override { changeID(action); }
	void visitActionFilterHue(ActionFilterHue* action) override { changeID(action); }
	void visitActionFilterNegative(ActionFilterNegative* action) override { changeID(action); }
	void visitActionFilterSaturation(ActionFilterSaturation* action) override { changeID(action); }

	void visitActionCharLive2DAnim(ActionCharLive2DAnim* action) override { changeID(action); }

};