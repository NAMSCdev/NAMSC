#include "Novel/Action/Audio/ActionAudioSetMusic.h"

#include "Novel/Data/Scene.h"

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent) noexcept
	: ActionAudio(parentEvent)
{
}

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent, const AudioSettings& audioSettings, const MusicPlaylist& musicPlaylist)
	: ActionAudio(parentEvent, audioSettings), musicPlaylist_(musicPlaylist)
{
	checkForErrors(true);
}

ActionAudioSetMusic::ActionAudioSetMusic(const ActionAudioSetMusic& obj) noexcept
	: ActionAudio(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

ActionAudioSetMusic& ActionAudioSetMusic::operator=(const ActionAudioSetMusic& obj) noexcept
{
	if (this == &obj) return *this;

	ActionAudio::operator=(obj);
	//onRun_         = obj.onRun_;
	musicPlaylist_ = obj.musicPlaylist_;

	return *this;
}

bool ActionAudioSetMusic::operator==(const ActionAudioSetMusic& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionAudio::operator==(obj)        && 
			musicPlaylist_ == obj.musicPlaylist_;
}

bool ActionAudioSetMusic::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionAudio::checkForErrors(bComprehensive);

	bError |= musicPlaylist_.checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);

	if (bError)
		qDebug() << "Error occurred in ActionAudioSetMusic::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionAudioSetMusic::clone() const
{
	ActionAudioSetMusic* clone = new ActionAudioSetMusic(*this);
	return clone;
}

void ActionAudioSetMusic::setOnRunListener(std::function<void(Event* const parentEvent, MusicPlaylist* musicPlaylist)> onRun) noexcept
{
	onRun_ = onRun;
}

const MusicPlaylist* ActionAudioSetMusic::getMusicPlaylist() const noexcept
{
	return &musicPlaylist_;
}

MusicPlaylist* ActionAudioSetMusic::getMusicPlaylist() noexcept
{
	return &musicPlaylist_;
}

void ActionAudioSetMusic::setMusicPlaylist(const MusicPlaylist& musicPlaylist) noexcept
{
	musicPlaylist_ = musicPlaylist;
}

void ActionAudioSetMusic::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionAudioSetMusic(this);
}

NovelLib::SerializationID ActionAudioSetMusic::getType() const noexcept
{
	return NovelLib::SerializationID::ActionAudioSetMusic;
}

void ActionAudioSetMusic::serializableLoad(QDataStream& dataStream)
{
	ActionAudio::serializableLoad(dataStream);
	dataStream >> musicPlaylist_;
	checkForErrors();
}

void ActionAudioSetMusic::serializableSave(QDataStream& dataStream) const
{
	ActionAudio::serializableSave(dataStream);
	dataStream << musicPlaylist_;
}