#include "Serialization.h"

//[polish personal note; optional todo] Teoretycznie moglibysmy w Serializacji na samym poczatku zliczyc rozmiar calej struktury, tak ze jak wystapi blad przy wczytywaniu jednej klasy ze skompresowanego pliku, to dalo sie wczytac reszte (przeskoczyc znacznikiem do miejsca, gdzie jest nastepny obiekt)

namespace NovelLib
{
    /// Serialization loading
    template<SerializableLoad T>
    QDataStream& operator>>(QDataStream& dataStream, T& t)
    {
        t.serializableLoad(dataStream);
        return dataStream;
    }

    /// Serialization saving
    template<SerializableSave T>
    QDataStream& operator<<(QDataStream& dataStream, const T& t)
    {
        t.serializableSave(dataStream);
        return dataStream;
    }
}