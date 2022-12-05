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

	bool catchExceptions(std::function<void(bool bComprehensive)> errorChecker, bool bComprehensive)
	{
		try
		{
			errorChecker(bComprehensive);
		}
		catch (QException& ex)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED `QException` HAS OCCURED OUTSIDE \"qCritical()\" MESSAGE HANDLER:\n" << ex.what(); //todo: check if '\n' is legal here
			return true;
		}
		catch (std::exception& ex)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED `std::exception` HAS OCCURED:\n" << ex.what();
			return true;
		}
		catch (...)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED EXCEPTION HAS OCCURED\n";
			return true;
		}
		return false;
	}
}