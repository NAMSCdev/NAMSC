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
	AssetAnim(const QString& name, uint size, uint pos = 0, const QString& path = "", bool bErrorCheck = true)
		: AssetAnimBase(name, size, pos, path)
	{
		if (bErrorCheck)
			errorCheck(true);
	}
	AssetAnim(const AssetAnim& obj) = delete;
	AssetAnim(AssetAnim&& obj)             = default;
	AssetAnim& operator=(const AssetAnim&) = default;

	/// \exception Error 'path' is invalid / some AnimNodes in `animNodes_` have invalid `timeStamp`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const
	{
		bool bError = Asset::errorCheck(bComprehensive);

		auto errorChecker = [this](bool bComprehensive)
		{
			//todo: check timeStamps
		};

		bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
		if (bError)
			qDebug() << "Error occurred in AssetAnim::errorCheck \"" + name + '\"';

		return bError;
	}

	/// \exception Error Could not find/open/read the Resource file
	/// \todo implement this
	void load() override
	{
		//if (size_ == 0)
		//{
		//	/// TODO: throw some Exception
		//	return;
		//}
		//checkFileExistence();
		//animNodes_.reset(new std::vector<AnimNode>);

		//QFile file(path_);
		//if (!file.open(QIODevice::ReadOnly))
		//{
		//	/// TODO: throw some Exception
		//	return;
		//}
		//QDataStream dataStream(&file);
		//dataStream.skipRawData(pos_);

		//uint animNodesSize;
		//dataStream >> animNodesSize;

		//for (uint i = 0; i != animNodesSize; ++i)
		//{
		//	AnimNode node;
		//	dataStream >> node;

		//	animNodes_.get()->push_back(node));
		//}
	}

	bool isLoaded() const override
	{
		return !animNodes_.empty();
	}

	void unload() noexcept override
	{
		animNodes_.clear();
	}

	/// Saves content changes (the Resource, not the definition)
	/// \exception Error Could not find/open/write to the file
	/// \todo implement this
	void save() override
	{
		//if (!bChanged_)
		//	return;

		//checkFileExistence();
		//QFile file(path_);
		//if (!file.open(QIODevice::ReadWrite))
		//{
		//	/// TODO: throw some Exception
		//	return;
		//}
		//QDataStream dataStream(&file);
		//QByteArray allData = file.readAll();
		//allData.remove(pos_, size_);

		//QByteArray newData;
		//QDataStream newDataStream(newData);
		//newDataStream << animNodes_->size();

		//for (const AnimNode& node : animNodes_)
		//	newDataStream << node;

		//allData.insert(pos_, newData);

		//uint oldSize = size_;
		//size_ = newData.size();

		//file.seek(0);
		//file.resize(0);
		//dataStream.writeRawData(allData, allData.size());

		//bChanged_ = false;

		//if (onSave)
		//	onSave(name_, oldSize, size_, pos_, path_);
	}

	const std::vector<AnimNode>* getAnimNodes() const noexcept
	{
		return &animNodes_;
	}

	/// \exception Error A node with the same `timeStamp` already exists in the `animNodes_` container
	/// \todo More intelligent inserting, so the sort is not needed
	void insertAnimNode(const AnimNode& newNode)
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

private:
	std::vector<AnimNode> animNodes_;
};

using AssetAnimColor  = AssetAnim<AnimNodeDouble4D>;
using AssetAnimMove   = AssetAnim<AnimNodeDouble2D>;
using AssetAnimRotate = AssetAnim<AnimNodeDouble1D>;
using AssetAnimScale  = AssetAnim<AnimNodeDouble2D>;