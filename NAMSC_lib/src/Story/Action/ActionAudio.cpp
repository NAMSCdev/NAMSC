#include "Story/Action/Audio/ActionChangeMusic.h"
#include "Story/Action/Audio/ActionPlaySound.h"

void ActionChangeMusic::run()
{
	Action::run();

	emit onRun(settings);
}

void ActionPlaySound::run()
{
	Action::run();
}
