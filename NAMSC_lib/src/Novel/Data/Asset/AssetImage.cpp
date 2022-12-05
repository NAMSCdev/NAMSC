#include "Novel/Data/Asset/AssetImage.h"

AssetImage::AssetImage(const QString& name, uint size, uint pos, const QString& path)
	: Asset(name, size, pos, path)
{
	checkForErrors(true);
}

bool AssetImage::checkForErrors(bool bComprehensive) const
{
	bool bError = Asset::checkForErrors(bComprehensive);
	
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (bComprehensive)
		{
			//todo: check lastError?
			if (!isLoaded())
			{
				AssetImage fake(name, size, pos, path);
				fake.load();
				fake.unload();
			}
			//todo: compare lastError?
		}

		return false;
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in AssetImage::checkForErrors \"" << name << '\"';

	return bError;
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
	//img_ = new QImage(path_);
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

bool AssetImage::isLoaded() const 
{ 
	return img_.get() != nullptr; 
}

void AssetImage::unload() noexcept
{ 
	img_.reset();
}

void AssetImage::save()
{
}

const QImage* AssetImage::getAssetImage() const noexcept
{
	return img_.get();
}
