#pragma once
#include "Global.h"

#include "Novel/Data/Stat/Stat.h"
#include "Novel/Data/Visual/Scenery/Scenery.h"

///Contains data about Novel progression and Stats
class NovelState
{
    //Friends for serialization
    friend QDataStream& operator>>(QDataStream&, NovelState&);
    friend QDataStream& operator<<(QDataStream&, const NovelState&);
public:
    NovelState() = default;

    void createNew(uint slot)
    {
        //todo: read from a file and throw exceptions on fialure
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

    ///Find by `name` a Stat
    ///\param name searched Stat
    ///\exception CriticalException failure finding the AssetFont
    ///\return pointer to the found AssetFont
    Stat* getStat(const QString &name)
    { 
        return findInuPtrArray<Stat>(name, stats);
    }

    ///Time of the save being made
    QDate date;

    ///A Screenshot of the game just before it was saved
    QImage image;

    ///todo:descriptions
    Scenery scenery;

private:
    //---SERIALIZATION---
    ///Loading an object from a binary file
    void serializableLoad(QDataStream &dataStream);
    ///Saving an object to a binary file
    void serializableSave(QDataStream &dataStream) const;

    ///All the Stats retrievable by the `getStat(const QString &name)`
    QVector<uPtr<Stat>> stats;

    ///At which saveslot this state will be saved/loaded
    uint saveSlot = 0;

    ///The Chapter->Scene->Event that the NovelState is in
    uint chapterID = 0,
         sceneID = 0,
         eventID = 0;


};
