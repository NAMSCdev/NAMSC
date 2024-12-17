#pragma once
#include "pvnLib/Novel/Data/Asset/Asset.h"

#include <QImage>

/// Allows Image loading and its memory management
class AssetImage final : public Asset
{
public:
	AssetImage()                                   = default;
	/// \exception Error Could not find/open/read the Resource file or the `assetImage_` couldn't be read as Image file (bad format)
	AssetImage(const QString& name, uint size, uint pos = 0, const QString& path = "", bool bErrorCheck = true);
	AssetImage(const AssetImage& obj)            = delete;
	AssetImage(AssetImage&& obj)                   = default;
	AssetImage& operator=(const AssetImage& obj) = delete;

	/// \exception Error Could not find/open/read the Resource file / invalid `assetImage_`
	/// \todo implement this
	void load() override;	
	bool isLoaded() const override;
	void unload() noexcept override;

	/// \exception Error Could not find/open/read the Resource file / invalid `assetImage_`
	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive = false) const;

	/// Saves content changes (the Resource, not the definition)
	/// \exception Error Could not find/open/write to the file
	/// \todo implement this
	void save() override;

	const QImage* getImage() const noexcept;

protected:
	std::unique_ptr<QImage> img_ = nullptr;
};