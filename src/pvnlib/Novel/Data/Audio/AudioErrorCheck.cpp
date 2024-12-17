#include "pvnLib/Novel/Data/Audio/MusicPlaylist.h"
#include "pvnLib/Novel/Data/Audio/Sound.h"

#include <QFileInfo>
#include <QMediaPlayer>

bool AudioSettings::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	//if (bError)
	//	qDebug() << "An Error occurred in Action::errorCheck of Scene \"" + parentScene->name + "\" Event" << parentEvent->getIndex();

	return false;
}

bool Sound::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		//Check if the name is undefined
		if (soundFilePath == "")
			qCritical() << NovelLib::ErrorType::AudioInvalid << "No Sound file assigned. Was it deleted and not replaced?";
		//Check if the File is still there in the User's filesystem
		else if (!QFileInfo::exists(soundFilePath))
			qCritical() << NovelLib::ErrorType::AudioFileMissing << "Could not find a Sound file \"" + soundFilePath + '\"';
		else if (bComprehensive)
		{
			//todo: do checking in our new class
			//QSoundEffect effect;
			//TODO: check if this will ensure the format is right
			//effect.setSource(soundFilePath);
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Sound::errorCheck";

	return bError;
}

bool MusicPlaylist::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		for (const std::pair<QString, QString>& song : songs)
		{
			//Check if the path is undefined
			if (song.second == "")
				qCritical() << NovelLib::ErrorType::AudioInvalid << "No Song file assigned. Was it deleted and not replaced?";
			//Check if the File is still there in the User's filesystem
			else if (!QFile::exists(song.second))
				qCritical() << NovelLib::ErrorType::AudioFileMissing << "Could not find a Song file \"" + song.second + '\"';
			else if (bComprehensive)
			{
				QMediaPlayer player;
				//TODO: check if this will ensure the format is right
				player.setSource(song.second);
			}
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in MusicPlaylist::errorCheck";

	return bError;
}