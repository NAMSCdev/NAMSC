#pragma once
#include "Global.h"

#include "Novel/Data/Stat/Stat.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

/// Contains data about the Novel progression and Stats
class NovelState
{
    //Friends for serialization
    friend QDataStream& operator>>(QDataStream&, NovelState&);
    friend QDataStream& operator<<(QDataStream&, const NovelState&);
public:
    NovelState() = default;
    NovelState(NovelState& obj) { *this = obj; }
    NovelState& operator=(const NovelState& obj);

    void createNew(uint slot)
    {
        //todo: read from a file and throw exceptions on failure
        QFile();
        QDataStream dataStream();
    };

    bool load(uint slot)
    {
        //todo: read from a file and throw exceptions on fialure
        QFile();
        QDataStream dataStream();
        return true;
    };

    /// Find by `name` a Stat
    /// \param name searched Stat
    /// \exception CriticalException failure finding the AssetFont
    /// \return pointer to the found AssetFont
    Stat* getStat(const QString &name)
    { 
        return findInuPtrArray<Stat>(name, stats);
    }

    /// Time of the save being made
    QDate date;

    /// A Screenshot of the game just before it was saved
    QImage image;

    /// Currently displayed Media
    Scenery scenery;

private:
    /// All the Stats retrievable by the `getStat(const QString &name)`
    QVector<uPtr<Stat>> stats;

    /// At which saveslot the NovelState will be saved/loaded
    uint saveSlot = 0;

    /// The Chapter->Scene->Event that the NovelState is in
    uint chapterID = 0,
         sceneID = 0,
         eventID = 0;

    //---SERIALIZATION---
    /// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
    void serializableLoad(QDataStream& dataStream);
    /// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
    void serializableSave(QDataStream& dataStream) const;
};




inline NovelState& NovelState::operator=(const NovelState& obj)
{
    if (this == &obj) return *this;

    date      = obj.date;
    image     = obj.image;
    scenery   = obj.scenery;
    stats     = obj.stats;
    saveSlot  = obj.saveSlot;
    chapterID = obj.chapterID;
    sceneID   = obj.sceneID;
    eventID   = obj.eventID;

    return *this;
}