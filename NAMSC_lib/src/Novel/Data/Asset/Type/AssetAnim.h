#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Asset.h"
#include "Novel/Data/Visual/Animation/AnimNode.h"

//Allows Animation loading and its memory management
template<typename AnimNode>
class AssetAnim : public Asset
{
public:
	AssetAnim() = default;
	AssetAnim(QString&& name, uint pos = 0,  QString&& location = "");
	AssetAnim(const AssetAnim&) = delete;
	AssetAnim& operator=(const AssetAnim&) = delete;

	/// Tries to load an Assent
	/// Throws a noncritical Exception on failure
	void load() override { }

	/// Release resources allocated for this asset
	void unload() override { animNodes.reset(); }

 	/// Returns whether the asset is currently loaded
	bool isLoaded() const override { return animNodes.get() != nullptr; }

	/// Returns a pointer to the AnimNodes that this Asset holds
	QVector<AnimNode>* getAnimNodes() { return animNodes.get(); }

private:
	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
	SerializationID	getType() const override { return SerializationID::AssetAnim; }

	/// A smart pointer to the actual data
	uPtr<QVector<AnimNode>>	animNodes;
};




template<typename AnimNode>
inline AssetAnim<AnimNode>::AssetAnim(QString&& name, uint pos, QString&& location) :
	Asset(move(name), pos, move(location))
{
}