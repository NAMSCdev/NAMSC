#include "Novel/Action/Audio/ActionAudioAll.h"

void ActionAudioSetSounds::ensureResourcesAreLoaded()
{
	for (std::pair<const QString, Sound>& sound : sounds)
		sound.second.load();
}