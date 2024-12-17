#pragma once

#include <QString>
#include "pvnLib/Serialization.h"

//#include "pvnLib/Novel/Data/Visual/MainMenuTheme.h"

/// Global settings for the Novel
struct NovelSettings final
{    
public:
    static NovelSettings& getInstance();

    static void load();

    enum class AvailableResolutions;
    
    NovelSettings(const QString& language = "En", const QString& defaultLanguage = "En", uint lastSaveSlot = 0, uint cps = 40, double volumeMusicMultiplier = 1.0, double volumeSoundMultiplier = 1.0, double volumeVoiceMultiplier = 1.0, const Qt::Key nextButton = Qt::Key::Key_Right, bool mouseClick = true, bool bStatsVisible = true, bool bStatsNotification = false, bool bLazyFileLoad = true, const AvailableResolutions resoultion = AvailableResolutions::sf_800x600);
    NovelSettings(const NovelSettings&)  noexcept = delete;
    NovelSettings(NovelSettings&&)       noexcept = delete;
    void operator=(const NovelSettings&) noexcept = delete;

	/// Language that the Translations will return text in
	QString	language             = "En";

	/// Default language that the Translations will try to revert to, if the selected one in `language` is not found
	QString	defaultLanguage      = "En";

	/// Last used SaveSlot
	uint lastSaveSlot            = 0;

    /// Characters Per Second
    uint cps                     = 30;

    double volumeMusicMultiplier = 1.0;

    double volumeSoundMultiplier = 1.0;

    double volumeVoiceMultiplier = 1.0;

	/// Button that can be pressed to navigate to the next Event
	Qt::Key	nextButton           = Qt::Key::Key_Right;
	
	/// Whether **left mouse button** can be used to navigate to the next Event
	bool mouseClick              = true;

    /// Whether Stats button opening Stats View is available
    bool bStatsVisible           = true;

    /// Whether every Stat change shows some kind of a notification
    bool bStatsNotification      = false;

    /// Whether the Files will not be compressed but managed in temporary files
    /// It's an useful option in Editor to make Data edit a lot faster
    bool bLazyFileLoad            = true;

	//[optional] Menu custom graphics
	//MainMenuTheme theme;

    /// List of available resolutions for the story
    /// \todo [optional] Make it custom defined
    enum class AvailableResolutions
    {
        sf_800x600,
        sf_1024x768,
        sw_1280x720, 
        s_1280x800, 
        sw_1360x768,
        sw_1366x768,
        s_1440x900, 
        sw_1600x900, 
        s_1680x1050, 
        sw_1920x1080,
        sw_2560x1440,
        s_2560x1600, 
        sw_3840x2160
    } resolution = AvailableResolutions::sf_800x600;

    /// Changes the default language and forces every AssetText to copy the text from previous one, if there is no Translation in the new default language available
    /// \todo implement this
    void defaultLanguageChange(const QString& newLanguage);

    //---SERIALIZATION---
    /// Loading an object from a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};
