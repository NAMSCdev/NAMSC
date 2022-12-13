#pragma once

#include <QString>
#include "Serialization.h"

//#include "Novel/Data/Visual/MainMenuTheme.h"

/// Global settings for the Novel
struct NovelSettings final
{    
public:
    static NovelSettings& getInstance();

    static void load();

    enum class AvailableResolutions;
    
    NovelSettings() noexcept             = default;
    NovelSettings(const QString& novelTitle, const QString& language, const QString& defaultLanguage, uint lastSaveSlot, uint cps, double volumeMusicMultiplier, double volumeSoundMultiplier, double volumeVoiceMultiplier, const Qt::Key nextButton, bool mouseClick, uint animationUpdateInterval, bool bLazyFileLoad, uint version, const AvailableResolutions resoultion);
    NovelSettings(const NovelSettings&)  = delete;
    void operator=(const NovelSettings&) = delete;

    /// Title of the Novel
    QString novelTitle           = "Пан Тадеуш: реальная история";

	/// Language that the Translation will return text in
	QString	language             = "En";

	/// Default language that the Translations will try to revert to, if the selected one in `language` is not found
	QString	defaultLanguage      = "En";

	/// Last used SaveSlot
	uint lastSaveSlot            = 0;

    /// Characters Per Second
    uint cps                     = 0;

    double volumeMusicMultiplier = 1;

    double volumeSoundMultiplier = 1;

    double volumeVoiceMultiplier = 1;

	/// Button that can be pressed to navigate to the next Event
	Qt::Key	nextButton           = Qt::Key::Key_Right;
	
	/// Whether **left mouse button** can be used to navigate to the next Event
	bool mouseClick              = true;

    /// How often the Animator keeps updating its Animation in milliseconds
    /// The formula is `1000/framerate_`
    /// 0 stands for minimal update time (might turn PC into a toaster)
    uint animationUpdateInterval = 0;

    /// Whether Stats button opening Stats View is available
    bool bStatsVisible           = true;

    /// [optional] Whether every Stat change shows some kind of a notification
    bool bStatsNotification      = false;

    /// [optional] Whether the Files will not be compressed but managed in temporary files
    /// It's an useful option in Editor to make Data edit a lot faster
    bool bLazyFileLoad            = true;

    /// Version of the Novel engine that it was written in (matters when loading a newer/older save)
    uint version                 = 0;

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


private:

public:
    //---SERIALIZATION---
    /// Loading an object from a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};
