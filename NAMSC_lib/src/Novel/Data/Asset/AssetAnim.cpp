#include "Novel/Data/Asset/AssetAnim.h"

template class AssetAnim<AnimNodeDouble1D>;
template class AssetAnim<AnimNodeDouble2D>;
template class AssetAnim<AnimNodeDouble3D>;
template class AssetAnim<AnimNodeDouble4D>;

template class AssetAnim<AnimNodeLongLong1D>;
template class AssetAnim<AnimNodeLongLong2D>;
template class AssetAnim<AnimNodeLongLong3D>;
template class AssetAnim<AnimNodeLongLong4D>;

AssetAnimBase::AssetAnimBase(const QString& name, uint size, uint pos, const QString& path)
	: Asset(name, size, pos, path)
{
	//checkForErrors(true);
}

template<typename AnimNode>
AssetAnim<AnimNode>::AssetAnim(const QString& name, uint size, uint pos, const QString& path, bool bCheckForErrors)
	: AssetAnimBase(name, size, pos, path)
{
	if (bCheckForErrors)
		checkForErrors(true);
}

template<typename AnimNode>
bool AssetAnim<AnimNode>::checkForErrors(bool bComprehensive) const
{
	bool bError = Asset::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		//todo: check timeStamps
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in AssetAnim::checkForErrors \"" << name << '\"';

	return bError;
}

template<typename AnimNode>
void AssetAnim<AnimNode>::insertAnimNode(const AnimNode& newNode)
{
	if (std::find(animNodes_.cbegin(), animNodes_.cend(), newNode.timeStamp) != animNodes_.cend())
	{
		qCritical() << this << "There already exists an AnimNode in the AssetAnim (object's name: \"" << name << "\") with `timeStamp` " << QString::number(newNode.timeStamp);
		return;
	}
	animNodes_.push_back(newNode);
	std::sort(animNodes_.begin(), animNodes_.end());
	bChanged_ = true;
}

template<typename AnimNode>
void AssetAnim<AnimNode>::load()
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

template<typename AnimNode>
bool AssetAnim<AnimNode>::isLoaded() const { return !animNodes_.empty(); }

template<typename AnimNode>
void AssetAnim<AnimNode>::unload() noexcept { animNodes_.clear(); }

template<typename AnimNode>
void AssetAnim<AnimNode>::save()
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

template<typename AnimNode>
const std::vector<AnimNode>* AssetAnim<AnimNode>::getAnimNodes() const noexcept 
{
	return &animNodes_; 
}