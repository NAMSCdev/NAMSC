#include "pvnLib/Novel/Data/Asset/AssetAnim.h"

AssetAnimBase::AssetAnimBase(const QString& name, uint size, uint pos, const QString& path)
	: Asset(name, size, pos, path)
{
}

//template<typename AnimNode>
//AssetAnim<AnimNode>::AssetAnim(const QString& name, uint size, uint pos, const QString& path, bool bErrorCheck)

////template<typename AnimNode>
////void AssetAnim<AnimNode>::insertAnimNode(const AnimNode& newNode)

//template<typename AnimNode>
//bool AssetAnim<AnimNode>::isLoaded() const

//template<typename AnimNode>
//void AssetAnim<AnimNode>::unload() noexcept

//template<typename AnimNode>
//const std::vector<AnimNode>* AssetAnim<AnimNode>::getAnimNodes() const noexcept