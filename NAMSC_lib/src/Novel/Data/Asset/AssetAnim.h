#pragma once
#include "Novel/Data/Asset/Asset.h"

#include <vector>
#include <QString>

#include "Novel/Data/Visual/Animation/AnimNode.h"

/// Accepts AssetVisitor for AssetAnim class
class AssetAnimBase : public Asset
{
public:
	AssetAnimBase() = default;
	AssetAnimBase(const QString& name, uint size, uint pos = 0, const QString& path = "");
	AssetAnimBase(const AssetAnimBase& obj) = delete;
	AssetAnimBase(AssetAnimBase&& obj)      = default;
};

/// Allows Animation loading and its memory management
template<typename AnimNode>
class AssetAnim final : public AssetAnimBase
{
public:
	AssetAnim()                            = default;
	/// \exception Error Could not find/open/read the Resource file or one of the AnimNode in `animNodes_` has a duplicate `timeStamp'
	AssetAnim(const QString& name, uint size, uint pos = 0, const QString& path = "");
	AssetAnim(const AssetAnim& obj)        = delete;
	AssetAnim(AssetAnim&& obj)             = default;
	AssetAnim& operator=(const AssetAnim&) = default;

	/// \exception Error 'path' is invalid / some AnimNodes in `animNodes_` have invalid `timeStamp`
	/// \return Whether an Error has occurred
	bool checkForErrors(bool bComprehensive = false) const;

	/// \exception Error Could not find/open/read the Resource file
	/// \todo implement this
	void load() override;
	bool isLoaded() const override;
	void unload() noexcept override;

	/// Saves content changes (the Resource, not the definition)
	/// \exception Error Could not find/open/write to the file
	/// \todo implement this
	void save() override;

	const std::vector<AnimNode>* getAnimNodes() const noexcept;

	/// \exception Error A node with the same `timeStamp` already exists in the `animNodes_` container
	/// \todo More intelligent inserting, so the sort is not needed
	void insertAnimNode(const AnimNode& newNode);

private:
	std::vector<AnimNode> animNodes_;
};

using AssetAnimColor  = AssetAnim<AnimNodeDouble4D>;
using AssetAnimMove   = AssetAnim<AnimNodeDouble2D>;
using AssetAnimRotate = AssetAnim<AnimNodeDouble1D>;
using AssetAnimScale  = AssetAnim<AnimNodeDouble2D>;