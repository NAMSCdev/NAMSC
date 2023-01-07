#pragma once
#include "Novel/Action/Visual/ActionSceneryObject.h"

#include "Novel/Data/Asset/AssetAnim.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

///Creates AnimatorSceneryObjectColor and adds it to the Scenery, which will perform some Animation on a SceneryObject
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	ActionSceneryObjectAnim(Event* const parentEvent) noexcept;
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName`
	ActionSceneryObjectAnim(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	ActionSceneryObjectAnim<AnimNode>& operator=(const ActionSceneryObjectAnim<AnimNode>& obj) noexcept;
	bool operator==(const ActionSceneryObjectAnim<AnimNode>& obj) const noexcept;
	bool operator!=(const ActionSceneryObjectAnim<AnimNode>& obj) const = default;

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	virtual bool checkForErrors(bool bComprehensive = false) const override;

	virtual void run() override = 0;

	void ensureResourcesAreLodaded();

	const AssetAnim<AnimNode>* getAssetAnim() const noexcept;
	AssetAnim<AnimNode>* getAssetAnim() noexcept;
	QString getAssetAnimName() const noexcept;
	//SetAssetAnim is defined in concrete ActionSceneryObjectAnims

	/// Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	uint priority   = 0;

	/// In milliseconds
	uint startDelay = 0;

	double speed    = 1.0;

	/// `-1` means infinite times
	int timesPlayed = 1;

	bool bStopAnimationAtEventEnd = false;

protected:
	QString	             assetAnimName_ = "";
	AssetAnim<AnimNode>* assetAnim_     = nullptr;

public://---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override;

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override;

private:
	/// Tracking pointer for created Animator, so we know what to remove in `void end()`
	AnimatorSceneryObjectInterface<AnimNode>* animator = nullptr;
};