#include "Global.h"
#include "Novel/Data/Novel.h"

#include "Novel/Action/Audio/ActionChangeMusic.h"
#include "Novel/Action/Audio/ActionPlaySound.h"

void ActionChangeMusic::run()
{
	Action::run();

	MusicPlaylist* sceneryMusicPlaylist = Novel::getInstance().getCurrentSave()->getScenery().overwriteMusicPlayList();

	emit onRun(sceneryMusicPlaylist);
}

void ActionPlaySound::run()
{
	Action::run();
}
