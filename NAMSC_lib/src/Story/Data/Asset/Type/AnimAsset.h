#pragma once
#include "Global.h"

#include "Story/Data/Asset/Asset.h"
#include "Story/Data/Visual/Animation/AnimNode.h"

//Allows Animation loading and its memory management
template<typename AnimNode>
class AnimAsset : public Asset
{
public:
	AnimAsset() = default;
	AnimAsset(QString name, QString &&location, unsigned pos = 0) :
		Asset(move(name), move(location), pos) {}
	AnimAsset(const AnimAsset& asset) = default;
	AnimAsset& operator=(const AnimAsset& asset) = default;
	///Tries to load an Assent
	///Throws a noncritical Exception on failure
	void load() override					{ }

	///Release resources allocated for this asset
	void unload() override					{ animNodes.reset(); }

 	///Returns whether the asset is currently loaded
	bool isLoaded() const override			{ return animNodes.get() != nullptr; }

	///Returns a pointer to the AnimNodes that this Asset holds
	QVector<AnimNode>* getAnimNodes()		{ return animNodes.get(); }

private:
	///Needed for serialization, to know the class of an object about to be serialization loaded
	SerializationID	getType() const override{ return SerializationID::AnimAsset; }

	///A smart pointer to the actual data
	uPtr<QVector<AnimNode>>	animNodes;
};
