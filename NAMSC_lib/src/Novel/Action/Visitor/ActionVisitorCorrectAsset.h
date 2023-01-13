#pragma once
#include "Novel/Action/Visitor/ActionVisitor.h"

#include "Novel/Action/ActionAll.h"

/// Updates `assetName_` of a changed/deleted Asset
class ActionVisitorCorrectAssetBase : public ActionVisitor
{
public:
	ActionVisitorCorrectAssetBase(const QString& oldAssetName, const QString& newAssetName);

protected:
	/// Every Action containing an Asset with its `assetAssetName_` equal to 'oldAssetName_' will have its `assetAssetName_` changed to `newAssetName_`
	/// Empty QString stands for invalid (it stands for invalid one - deleted)
	QString oldAssetName_ = "",
			newAssetName_ = "";
};

/// [optional] Updates `assetLive2DassetAnimName_` of a changed/deleted AssetLive2DAnim
//class ActionVisitorCorrectAssetLive2DAnim final : public ActionVisitorCorrectAsset
//{
//public:
//	ActionVisitorCorrectAssetLive2DAnim(const QString& oldAssetName, const QString& newAssetName);
//
//	void visitActionLive2DAnim(ActionLive2DAnim* action) override;
//};

/// [optional] Updates `assetLive2DModelAssetName_` of a changed/deleted AssetLive2DModel
//class ActionVisitorCorrectAssetLive2DModel final : public ActionVisitorCorrectAsset
//{
//public:
//	ActionVisitorCorrectAssetLive2DModel(const QString& oldAssetName, const QString& newAssetName);
//};

/// Updates `assetAnimName_` of a changed/deleted **color** AssetAnim
class ActionVisitorCorrectAssetAnimColor final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectAssetAnimColor(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSceneryObjectAnimColor(ActionSceneryObjectAnimColor* action) override;
};

/// Updates `assetAnimName_` of a changed/deleted **move** AssetAnim
class ActionVisitorCorrectAssetAnimMove final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectAssetAnimMove(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSceneryObjectAnimMove(ActionSceneryObjectAnimMove* action) override;
};

/// Updates `assetAnimName_` of a changed/deleted **rotate** AssetAnim
class ActionVisitorCorrectAssetAnimRotate final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectAssetAnimRotate(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSceneryObjectAnimRotate(ActionSceneryObjectAnimRotate* action) override;
};

/// Updates `assetAnimName_` of a changed/deleted **scale** AssetAnim
class ActionVisitorCorrectAssetAnimScale final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectAssetAnimScale(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSceneryObjectAnimScale(ActionSceneryObjectAnimScale* action) override;
};

/// Updates `assetAudioAssetName` of a changed/deleted Music AssetAudio
class ActionVisitorCorrectMusicPlaylist final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectMusicPlaylist(const QString& oldAssetName, const QString& newAssetName);

	void visitActionAudioSetMusic(ActionAudioSetMusic* action) override;
};

/// Updates `assetAudioAssetName` of a changed/deleted Sound AssetAudio
class ActionVisitorCorrectSounds final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectSounds(const QString& oldAssetName, const QString& newAssetName);

	void visitActionAudioSetSounds(ActionAudioSetSounds* action) override;
};

/// Updates `assetImageAssetName` of a changed/deleted background AssetImage
class ActionVisitorCorrectBackgroundAssetImage final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectBackgroundAssetImage(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSetBackground(ActionSetBackground* action) override;
};

/// Updates `assetImageAssetName` of a changed/deleted AssetImage
class ActionVisitorCorrectSceneryObjectAssetImage final : public ActionVisitorCorrectAssetBase
{
public:
	ActionVisitorCorrectSceneryObjectAssetImage(const QString& oldAssetName, const QString& newAssetName);

	void visitActionSceneryObjectSetImage(ActionSceneryObjectSetImage* action) override;
};