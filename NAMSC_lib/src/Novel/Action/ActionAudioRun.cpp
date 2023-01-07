#include "Novel/Action/Audio/ActionAudioSetMusic.h"
#include "Novel/Action/Audio/ActionAudioSetSounds.h"

#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Scene.h"

void ActionAudioSetMusic::run()
{
	qDebug() << "ActionAudioSetMusic::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionAudio::run();

	MusicPlaylist* sceneryMusicPlaylist = &(NovelState::getCurrentlyLoadedState()->scenery.musicPlaylist);
	*sceneryMusicPlaylist = musicPlaylist_;

	if (onRun_) 
		onRun_(parentEvent, sceneryMusicPlaylist);
}

void ActionAudioSetSounds::run()
{
	qDebug() << "ActionAudioSetSounds::run in Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();
	ActionAudio::run();

	NovelState::getCurrentlyLoadedState()->scenery.setSounds(sounds);

	if (onRun_) 
		onRun_(parentEvent, &sounds);
}