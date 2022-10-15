#pragma once
#include "Global.h"

#include "Story/Data/Stat/Stat.h"

///Contains data about Story progression and Stats
class StoryState
{
    ///Friends for serialization
    friend QDataStream& operator>>(QDataStream&, StoryState&);
    friend QDataStream& operator<<(QDataStream&, const StoryState&);
public:
    void createNew(unsigned slot)
    {
        //todo: read from a file and throw exceptions on fialure
        QFile();
        QDataStream dataStream();
    };

    bool load(unsigned slot)
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

    ///At which saveslot this state will be saved/loaded
    unsigned saveSlot = 0;

   	///Event execution order position with sceneID identifies the Event
    ///precisely and all Actions are contained within Events
    unsigned sceneID  = 0,
             eventID  = 0;

    ///Time of the save being made
    QDate date;

    ///A Screenshot of the game just before it was saved
    QImage image;

private:
    //---SERIALIZATION---
    ///Loading an object from a binary file
    void serializableLoad(QDataStream &dataStream);
    ///Saving an object to a binary file
    void serializableSave(QDataStream &dataStream) const;

    ///All the Stats retrievable by the `getStat(const QString &name)`
    QVector<uPtr<Stat>> stats;
};
