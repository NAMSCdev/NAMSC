#include <QDir>

#include "Novel/Data/Asset/AssetManager.h"

#include <QFile>

template class AssetAnim<AnimNodeDouble1D>;
template class AssetAnim<AnimNodeDouble2D>;
template class AssetAnim<AnimNodeDouble3D>;
template class AssetAnim<AnimNodeDouble4D>;

template class AssetAnim<AnimNodeLongLong1D>;
template class AssetAnim<AnimNodeLongLong2D>;
template class AssetAnim<AnimNodeLongLong3D>;
template class AssetAnim<AnimNodeLongLong4D>;

template<typename AssetType>
void AssetManager::loadDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
	{
		qCritical() << NovelLib::ErrorType::General << "Could not open the File \"" + path + "\": ";
		return;
	}
	try
	{
		QDataStream dataStream(&file);
		while (!dataStream.atEnd())
		{
			AssetType asset;
			dataStream >> asset;
			map.insert(std::make_pair<QString, AssetType>(QString(asset.name), std::move(asset)));
		}
	}
	catch (QException exception)
	{
		qCritical() << NovelLib::ErrorType::General << "Could not read from File \"" + path + "\":" << exception.what();
	}
}

template<typename AssetType>
void AssetManager::saveDefinitions(const QString& path, std::unordered_map<QString, AssetType>& map)
{
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		qCritical() << NovelLib::ErrorType::General << "Couldn't open \"" + path + "\" File";
		return;
	}
	try
	{
		QDataStream dataStream(&file);
		for (const std::pair<const QString, AssetType>& asset : map)
			dataStream << asset.second;
	}
	catch (QException& exception)
	{
		qCritical() << NovelLib::ErrorType::General << "Could not write to File \"" + path + "\":" << exception.what();
	}
}

void AssetManager::loadAllAssetsDefinitions()
{
	loadDefinitions("Assets/colorAnims.bin",       colorAnims_);
	loadDefinitions("Assets/moveAnims.bin",        moveAnims_);
	loadDefinitions("Assets/rotateAnims.bin",      rotateAnims_);
	loadDefinitions("Assets/scaleAnims.bin",       scaleAnims_);
	loadDefinitions("Assets/backgroundImages.bin", backgroundImages_);
	loadDefinitions("Assets/objectImages.bin",     objectImages_);
}

void AssetManager::saveAllAssetsDefinitions()
{
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/colorAnims.bin", colorAnims_);
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/moveAnims.bin",        moveAnims_);
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/rotateAnims.bin",      rotateAnims_);
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/scaleAnims.bin",       scaleAnims_);
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/backgroundImages.bin", backgroundImages_);
	saveDefinitions(QDir::currentPath() + "/game/" + "Assets/objectImages.bin",     objectImages_);
}

void AssetManager::saveAllAssets()
{
	//for (std::pair<const QString, AssetAnimColor>& asset : colorAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimMove>& asset : moveAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimRotate>& asset : rotateAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetAnimScale>& asset : scaleAnims_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetImage>& asset : backgroundImages_)
	//	asset.second.save();
	//for (std::pair<const QString, AssetImage>& asset : objectImages_)
	//	asset.second.save();
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

void AssetImage::load()
{
	//checkFileExistence();
	//if (size == 0)
	//{
	//	/// TODO: throw some Exception
	//	return;
	//}	
	//TODO: add some way to edit Images (even using external editors) in the Editor, then allow for compression to happen
	img_ = std::unique_ptr<QImage>(new QImage(path));
	//img = std::unique_ptr<QImage>();
	//QFile file(path);
	//if (!file.open(QIODevice::ReadOnly))
	//{
	//	/// TODO: throw some Exception
	//	return;
	//}
	//QDataStream dataStream(&file);
	//dataStream.skipRawData(pos);

	//std::unique_ptr<char> data = std::unique_ptr<char>(new char[size]);
	//dataStream.readRawData(data.get(), size);

	//img = std::unique_ptr<QImage>(new QImage);
	//if (!img.get()->loadFromData(reinterpret_cast<uchar*>(data.get()), size))
	//{
	//	/// TODO: throw some Exception
	//	return;
	//}

}

void AssetImage::save()
{
}

#include "Novel/Data/Asset/AssetAnimInstances.h"