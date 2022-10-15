#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/AnimNode.h"
#include "Story/Data/Visual/Scenery/SceneryObject.h"

#include "Story/Data/Asset/Type/AssetAnim.h"
#include "Story/Data/Asset/AssetManager.h"

///Controls an Animation output that will be assigned to change something that is being animated
template<typename AnimNode>
class Animator
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream& dataStream, Animator& t);
	friend QDataStream& operator<<(QDataStream& dataStream, const Animator& t);
public:
	Animator() = default;
	Animator(QString&& animAssetName, double speed, bool bLoop) :
		animAssetName(move(animAssetName)), speed(speed), bLoop(bLoop) {}
	Animator(const Animator& obj) { *this = obj; }
	Animator& operator=(const Animator& obj)
	{
		if (this == &obj) return *this;

		nodes         = obj.nodes;
		animAssetName = obj.animAssetName;
		animAsset     = obj.animAsset;
		currentNode   = nodes->cbegin() + (obj.currentNode - obj.nodes->cbegin());
		nextNode      = currentNode + 1;
		startTime     = obj.startTime;
		speed         = obj.speed;
		bLoop         = obj.bLoop;

		return *this;
	}
	
	virtual ~Animator() = 0;

	void start()
	{
		ensureAnimIsLoaded();
		startTime = QTime::currentTime();
		currentNode = nodes->cbegin();
		nextNode = currentNode + 1;
	}

	///Calculates interpolated state in given [time]
	AnimNode currentAnimState();
	void ensureAnimIsLoaded() { if (!animAsset->isLoaded()) animAsset->load(); nodes = animAsset->getAnimNodes(); }

protected:
	///Poits to the AnimNodes of some AssetAnim, that contain sequential changes
	QVector<AnimNode>	*nodes;

	///Name of the AssetAnim, so it can be loaded (if needed) and played
	QString				animAssetName;
	///AssetAnim containing all the AnimNodes
	AssetAnim<AnimNode>	*animAsset;

	///Nodes containing current state and next state that we interpolate into
	QVector<AnimNode>::const_iterator	currentNode, 
										nextNode;

	///Beginning of the animation, so we can calculate the elapsed time
	QTime startTime;

	///How fast the animation will be played
	double speed = 1.0;

	///Whether the animation is looped
	bool bLoop = false;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};

template<typename AnimNode>
Animator<AnimNode>::~Animator() = default;

template<typename AnimNode>
class AnimatorSceneryObject : public Animator<AnimNode>
{
public:
	AnimatorSceneryObject() = default;
	AnimatorSceneryObject(QString&& animAssetName, double speed, bool bLoop, QString&& sceneryObjectName);
	AnimatorSceneryObject(const AnimatorSceneryObject &obj) { *this = obj; }
	AnimatorSceneryObject& operator=(const AnimatorSceneryObject& obj)
	{
		if (this == &obj) return *this;

		Animator<AnimNode>::operator=(obj);
		sceneryObjectName = obj.sceneryObjectName;
		sceneryObject     = obj.sceneryObject;

		return *this;
	}

	///Affects the SceneryObject
	virtual void update() = 0;

protected:
	///Name to the Scenery Object, so it can be loaded (if needed)
	QString		  sceneryObjectName;
	///Scenery Object that will be affected by this Animator
	SceneryObject *sceneryObject;

	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const override;
};