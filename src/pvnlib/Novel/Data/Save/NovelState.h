#pragma once

#include <QDate>
#include <QImage>
#include <qhashfunctions.h>
#include <unordered_map>

#include "pvnLib/Novel/Data/Stat/Stat.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"
#include "pvnLib/Novel/Data/Visual/Scenery/Scenery.h"

/// Contains data about the Novel progression and Stats
class NovelState final
{
    /// Swap trick
    friend void swap(NovelState& first, NovelState& second) noexcept;
public:
    NovelState()                                 noexcept = default;
    /// \param scenery Current Media
    /// \param sceneName The Scene that the Save is in, which marks the Player's progression 
    /// \param eventID The Scene->Event that the Save is in, which marks the Player's progression 
    /// \param sentenceID Which Sentence is being read, which marks the Player's progression in EventDialogue
    /// \exception Error 'screenshot` could not be loaded and recognized as an Image or `scenery` contains an Error
    explicit NovelState(const QDate& saveDate, const QImage& screenshot = QImage(20, 20, QImage::Format_ARGB32), uint saveSlot = 0, const QString& sceneName = "", uint eventID = 0, uint sentenceID = 0);
    NovelState(const NovelState& obj)            noexcept = default;
    NovelState(NovelState&& obj)                 noexcept = default;
    NovelState& operator=(const NovelState& obj) noexcept = default;
    //NovelState& operator=(NovelState obj)        noexcept;
    bool operator==(const NovelState& obj) const noexcept = default;
    bool operator!=(const NovelState& obj) const noexcept = default;

    static NovelState* getCurrentlyLoadedState();
    static NovelState load(uint saveSlot);
    static NovelState reset(uint saveSlot);
    void save();

    /// \exception Error 'screenshot`/`scenery` is invalid
    /// \return Whether an Error has occurred
    bool errorCheck(bool bComprehensive = false) const;
    void update(uint elapsedTime);

    const std::unordered_map<QString, std::shared_ptr<Stat>>* getStats() const noexcept;
    /// \exception Error Could not find a Stat with this name
    const std::shared_ptr<Stat> getStat(const QString& name) const;
    /// \exception Error Could not find a Stat with this name
    std::shared_ptr<Stat> getStat(const QString& name);
    const std::unordered_map<QString, std::shared_ptr<Stat>>* setStats(const std::unordered_map<QString, std::shared_ptr<Stat>>& stats) noexcept;
    const std::unordered_map<QString, std::shared_ptr<Stat>>* setStats(std::unordered_map<QString, std::shared_ptr<Stat>>&& stats)      noexcept;
    std::shared_ptr<Stat> setStat(Stat* stat) noexcept;
    std::shared_ptr<Stat> setStat(const std::shared_ptr<Stat>& stat) noexcept;
    /// \exception Error Could not find a Stat with `oldName`
    std::shared_ptr<Stat> renameStat(const QString& oldName, const QString& newName);
    /// \exception Error Could not find a Stat with this name
    bool removeStat(const QString& name);
    void clearStats() noexcept;

    QDate saveDate    = QDate::currentDate();

    QImage screenshot;

    //[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
    /// Current Media
    Scenery scenery   = Scenery(nullptr);

    int saveSlot      = -1;

    //[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
    /// The Scene that the Save is in, which marks the Player's progression 
    QString sceneName = "";

    //[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
    /// The Scene->Event that the Save is in, which marks the Player's progression 
    uint eventID      = 0;

    //[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
    /// Which Sentence is being read, which marks the Player's progression in EventDialogue
    uint sentenceID   = 0;

private:
    /// Loads Stats definitions (meaning they will be reset to the default values) from a single file
    /// \todo implement this
    void loadStats();

    std::unordered_map<QString, std::shared_ptr<Stat>> stats_;
public:
    //---SERIALIZATION---
    /// Loading an object from a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file
    /// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};