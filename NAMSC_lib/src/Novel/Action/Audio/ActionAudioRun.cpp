#include "Novel/Action/Audio/ActionAudioAll.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

void ActionAudioSetMusic::run()
{
	//qDebug() << "ActionAudioSetMusic::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionAudio::run();

	//TODO: pointer to the changed object
	onRun_(parentEvent, &musicPlaylist_);
}

void ActionAudioSetSounds::run()
{
	//qDebug() << "ActionAudioSetSounds::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionAudio::run();

	//TODO: pointer to the changed object
	onRun_(parentEvent, &sounds);
}
