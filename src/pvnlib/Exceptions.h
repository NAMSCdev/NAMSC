#pragma once

#include <QDebug>
#include <QException>
#include <QString>

namespace NovelLib
{
	/// More sophisitacted Exceptions with ErrorType for easier debugging
	class NovelException : public QException
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

		ActionMissing,
		ActionInvalid,
		AssetAnimMissing,
		AssetAnimFileMissing,
		AssetAnimLoad,
		AssetAnimInvalid,
		AssetImageMissing,
		AssetImageFileMissing,
		AssetImageLoad,
		AssetImageInvalid,
		AudioMissing,
		AudioFileMissing,
		AudioInvalid,
		ChapterMissing,
		ChapterInvalid,
		CharacterMissing,
		CharacterInvalid,
		ChoiceMissing,
		ChoiceInvalid,
		EventMissing,
		EventInvalid,
		JumpMissing,
		JumpInvalid,
		VoiceMissing,
		VoiceInvalid,
		SceneMissing,
		SceneInvalid,
		SceneryObjectMissing,
		SceneryObjectInvalid,
		SentenceMissing,
		SentenceInvalid,
		SoundMissing,
		SoundInvalid,
		StatMissing,
		StatInvalid,
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

		"[ActionMissing]",
		"[ActionInvalid]",
		"[AudioMissing]",
		"[AudioFileMissing]",
		"[AudioInvalid]",
		"[AssetAnimMissing]",
		"[AssetAnimFileMissing]",
		"[AssetAnimLoad]",
		"[AssetAnimInvalid]",
		"[AssetImageMissing]",
		"[AssetImageFileMissing]",
		"[AssetImageLoad]",
		"[AssetImageInvalid]",
		"[ChapterMissing]",
		"[ChapterInvalid]",
		"[CharacterMissing]",
		"[CharacterInvalid]",
		"[ChoiceMissing]",
		"[ChoiceInvalid]",
		"[EventMissing]",
		"[EventInvalid]",
		"[JumpMissing]",
		"[JumpInvalid]",
		"[VoiceMissing]",
		"[VoiceInvalid]",
		"[SceneMissing]",
		"[SceneInvalid]",
		"[SceneryObjectMissing]",
		"[SceneryObjectInvalid]",
		"[SentenceMissing]",
		"[SentenceInvalid]",
		"[SoundMissing]",
		"[SoundInvalid]",
		"[StatMissing]",
		"[StatInvalid]",
		"[StatMinMax]",
		"[StatValue]"
	};

	bool catchExceptions(const std::function<void(bool bComprehensive)>& errorChecker, bool bComprehensive);
}

QDebug operator<<(QDebug logger, const NovelLib::ErrorType& errorType);