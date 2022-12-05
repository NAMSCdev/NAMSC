#pragma once

#include <QDebug>
#include <QException>
#include <QString>

namespace NovelLib
{
	#define LOG_FILENAME "log.txt"
	enum ErrorType : unsigned int
	{
		General,
		Critical,
		SaveCritical,
		NameDuplicate,

		AudioFileMissing,
		AudioMissing,
		AudioInvalid,
		AssetAnimFileMissing,
		AssetAnimInvalid,
		AssetAnimLoad,
		AssetAnimMissing,
		AssetImageFileMissing,
		AssetImageInvalid,
		AssetImageLoad,
		AssetImageMissing,
		ChapterMissing,
		CharacterMissing,
		CharacterInvalid,
		JumpInvalid,
		VoiceInvalid,
		VoiceMissing,
		SceneryObjectInvalid,
		SceneryObjectMissing,
		StatInvalid,
		StatMissing,
		StatMinMax,
		StatValue
	};

	bool catchExceptions(std::function<void(bool bComprehensive)> errorChecker, bool bComprehensive);
}