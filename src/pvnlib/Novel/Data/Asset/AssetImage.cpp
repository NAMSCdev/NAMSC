#include "pvnLib/Novel/Data/Asset/AssetImage.h"

AssetImage::AssetImage(const QString& name, uint size, uint pos, const QString& path, bool bErrorCheck)
	: Asset(name, size, pos, path)
{
	if (bErrorCheck)
		errorCheck(true);
}

bool AssetImage::isLoaded() const 
{ 
	return img_.get() != nullptr; 
}

void AssetImage::unload() noexcept
{ 
	img_.reset();
}

const QImage* AssetImage::getImage() const noexcept
{
	return img_.get();
}
