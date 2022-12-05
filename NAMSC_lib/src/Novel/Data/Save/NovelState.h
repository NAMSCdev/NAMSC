#pragma once

#include <QDate>
#include <QImage>
#include <QJSEngine>
#include <qhashfunctions.h>
#include <unordered_map>

#include "Novel/Data/Stat/Stat.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

/// Contains data about the Novel progression and Stats
class NovelState final
{
    //Friends for serialization
    friend QDataStream& operator>>(QDataStream&, NovelState&);
    friend QDataStream& operator<<(QDataStream&, const NovelState&);
public:
    NovelState()                                 = default;
    /// \exception Error 'screenshot` could not be loaded and recognized as an Image or `scenery` contains an Error
    NovelState(const QDate& saveDate, const QImage& screenshot, const Scenery& scenery, uint saveSlot, const QString& sceneName, uint eventID);
    NovelState(const NovelState& obj) noexcept;
    /// \todo reset and copy `jsEngine_` properties
    NovelState& operator=(NovelState obj) noexcept;
    bool operator==(const NovelState& obj) const noexcept;
    bool operator!=(const NovelState& obj) const = default; //{ return !(*this == obj); }

    static NovelState* getCurrentlyLoadedState();
    static NovelState load(uint saveSlot);
    static NovelState reset(uint saveSlot);
    void save();

    /// \exception Error 'screenshot`/`scenery` is invalid
    /// \return Whether an Error has occurred
    bool checkForErrors(bool bComprehensive = false) const;
    void update(uint elapsedTime);

    const std::unordered_map<QString, std::unique_ptr<Stat>>* getStats() const noexcept;
    const Stat* getStat(const QString& statName) const noexcept;
    Stat* getStat(const QString& statName) noexcept;
    void  setStat(const QString& statName, Stat* stat) noexcept;
    bool  removeStat(const QString& statName) noexcept;

    QDate saveDate    = QDate::currentDate();

    QImage screenshot;

    /// Current Media
    Scenery scenery;

    int saveSlot      = -1;

    /// The Scene->Event that the is in, which marks the Player's progression 
    QString sceneName = "";
    /// The Scene->Event that the is in, which marks the Player's progression 
    uint eventID      = 0;

private:
    /// Loads Stats definitions (meaning they will be reset to the default values) from a single file
    /// \todo implement this
    void loadStats();

    std::unordered_map<QString, std::unique_ptr<Stat>> stats_;

    QJSEngine jsEngine_;

    //---SERIALIZATION---
    /// Loading an object from a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};