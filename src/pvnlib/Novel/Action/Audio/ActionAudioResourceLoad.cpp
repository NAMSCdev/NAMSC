#include "pvnLib/Novel/Action/Audio/ActionAudioAll.h"

void ActionAudioSetSounds::ensureResourcesAreLoaded()
{
	for (Sound& sound : sounds_)
		sound.load();
}