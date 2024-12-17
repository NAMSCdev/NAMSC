#include "pvnLib/Novel/Action/Visual/ActionVisualAll.h"

void ActionSceneryObjectSetImage::ensureResourcesAreLoaded()
{
	ActionSceneryObject::ensureResourcesAreLoaded();

	if (assetImage_->isLoaded())
		assetImage_->load();
}