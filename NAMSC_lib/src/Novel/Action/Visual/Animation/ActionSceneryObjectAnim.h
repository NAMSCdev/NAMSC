#pragma once
#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

///Creates AnimatorSceneryObjectColor and adds it to the Scenery, which will perform some Animation on a SceneryObject
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	/// \param sceneryObject Copies the SceneryObject pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param assetAnim Copies the AssetAnim pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param priority Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	/// \param startDelay In milliseconds
	/// \param speed Animation speed multiplier
	/// \param Remember to copy the description to the constructor parameter description as well, if it changes
	/// \param timesPlayed `-1` means infinite times
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName`
	explicit ActionSceneryObjectAnim(Event* const parentEvent, const QString& sceneryObjectName = "", const QString& assetAnimName = "", uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false, SceneryObject* sceneryObject = nullptr, AssetAnim<AnimNode>* assetAnim = nullptr);
	ActionSceneryObjectAnim(const ActionSceneryObjectAnim& obj)            noexcept = delete;
	ActionSceneryObjectAnim(ActionSceneryObjectAnim&& obj)                 noexcept = delete;
	ActionSceneryObjectAnim& operator=(const ActionSceneryObjectAnim& obj) noexcept = delete;
	bool operator==(const ActionSceneryObjectAnim<AnimNode>& obj) const    noexcept = delete;
	bool operator!=(const ActionSceneryObjectAnim<AnimNode>& obj) const    noexcept = delete;
	//Makes it abstract
	virtual ~ActionSceneryObjectAnim() = 0;

	void swapPrivate(ActionSceneryObjectAnim& second) noexcept;

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override;

	void ensureResourcesAreLodaded();

	QString getAssetAnimName()                const noexcept;
	const AssetAnim<AnimNode>* getAssetAnim() const noexcept;
	AssetAnim<AnimNode>*       getAssetAnim()       noexcept;
	//SetAssetAnim is defined in concrete ActionSceneryObjectAnims
	virtual void setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNode>* assetAnim = nullptr) noexcept = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	uint priority   = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// In milliseconds
	uint startDelay = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Animation speed multiplier
	double speed    = 1.0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// `-1` means infinite times
	int timesPlayed = 1;

	bool bFinishAnimationAtEventEnd = false;

protected:
	QString	             assetAnimName_ = "";
	AssetAnim<AnimNode>* assetAnim_     = nullptr;

private:
	/// Tracking pointer for the created Animator, so we know what to remove in `void end()`
	AnimatorSceneryObjectInterface<AnimNode>* animator_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;
};