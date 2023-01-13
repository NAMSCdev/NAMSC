#include "Novel/Data/Asset/AssetAnim.h"

AssetAnimBase::AssetAnimBase(const QString& name, uint size, uint pos, const QString& path)
	: Asset(name, size, pos, path)
{
}

template<typename AnimNode>
AssetAnim<AnimNode>::AssetAnim(const QString& name, uint size, uint pos, const QString& path, bool bErrorCheck)
	: AssetAnimBase(name, size, pos, path)
{
	if (bErrorCheck)
		errorCheck(true);
}

template<typename AnimNode>
void AssetAnim<AnimNode>::insertAnimNode(const AnimNode& newNode)
{
	if (std::find(animNodes_.cbegin(), animNodes_.cend(), newNode.timeStamp) != animNodes_.cend())
	{
		qCritical() << "There already exists an AnimNode in the AssetAnim (object's name: \"" + name + "\") with `timeStamp`" << QString::number(newNode.timeStamp);
		return;
	}
	animNodes_.push_back(newNode);
	std::sort(animNodes_.begin(), animNodes_.end());
	bChanged_ = true;
}

template<typename AnimNode>
bool AssetAnim<AnimNode>::isLoaded() const 
{ 
	return !animNodes_.empty();
}

template<typename AnimNode>
void AssetAnim<AnimNode>::unload() noexcept 
{ 
	animNodes_.clear();
}

template<typename AnimNode>
const std::vector<AnimNode>* AssetAnim<AnimNode>::getAnimNodes() const noexcept 
{
	return &animNodes_; 
}

#include "Novel/Data/Asset/AssetAnimInstances.h"