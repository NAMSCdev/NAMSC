#pragma once

#include <QDebug>
#include <QException>
#include <QString>

namespace NovelLib
{
	class NovelException : QException
	{
	public:
		NovelException(QString msg);
		void raise() const override;
		NovelException* clone() const override;
		const char* what() const override;
	private:
		QString msg;
	};

	enum class ErrorType
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
		ChapterInvalid,
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
		StatValue,
		ErrorTypeCount
	};

	constexpr char const* const ErrorTypeStr[]
	{
		"[General]",
		"[Critical]",
		"[SaveCritical]",
		"[NameDuplicate]",
		"[AudioFileMissing]",
		"[AudioMissing]",
		"[AudioInvalid]",
		"[AssetAnimFileMissing]",
		"[AssetAnimInvalid]",
		"[AssetAnimLoad]",
		"[AssetAnimMissing]",
		"[AssetImageFileMissing]",
		"[AssetImageInvalid]",
		"[AssetImageLoad]",
		"[AssetImageMissing]",
		"[ChapterInvalid]",
		"[ChapterMissing]",
		"[CharacterMissing]",
		"[CharacterInvalid]",
		"[JumpInvalid]",
		"[VoiceInvalid]",
		"[VoiceMissing]",
		"[SceneryObjectInvalid]",
		"[SceneryObjectMissing]",
		"[StatInvalid]",
		"[StatMissing]",
		"[StatMinMax]",
		"[StatValue]"
	};

	bool catchExceptions(const std::function<void(bool bComprehensive)>& errorChecker, bool bComprehensive);
}

QDebug operator<<(QDebug logger, const NovelLib::ErrorType& errorType);