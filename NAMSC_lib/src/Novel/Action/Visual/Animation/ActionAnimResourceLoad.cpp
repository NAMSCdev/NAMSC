#include "Novel/Action/Visual/Animation/ActionAnimAll.h"

template <class AnimNode>
void ActionSceneryObjectAnim<AnimNode>::ensureResourcesAreLodaded()
{
	if (assetAnim_->isLoaded())
		assetAnim_->load();
}
