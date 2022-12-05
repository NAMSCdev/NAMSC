#include "Novel/Action/Audio/ActionAudioSetMusic.h"

#include "Novel/Data/Scene.h"

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionAudio(parentEvent, parentScene)
{
}

ActionAudioSetMusic::ActionAudioSetMusic(Event* const parentEvent, Scene* const parentScene, const AudioSettings& audioSettings, const MusicPlaylist& musicPlaylist)
	: ActionAudio(parentEvent, parentScene, audioSettings), musicPlaylist_(musicPlaylist)
{
	checkForErrors(true);
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
		qDebug() << "Error occurred in ActionAudioSetMusic::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionAudioSetMusic::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, MusicPlaylist* musicPlaylist)> onRun) noexcept
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