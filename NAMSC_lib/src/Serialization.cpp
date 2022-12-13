#include "Novel/Data/Save/NovelState.h"
#include "Novel/Data/Stat/Stat.h"

//[polish personal note; optional todo] Teoretycznie moglibysmy w Serializacji na samym poczatku zliczyc rozmiar calej struktury, tak ze jak wystapi blad przy wczytywaniu jednej klasy ze skompresowanego pliku, to dalo sie wczytac reszte (przeskoczyc znacznikiem do miejsca, gdzie jest nastepny obiekt)

template QDataStream& operator>><NovelState>(QDataStream& dataStream, NovelState& t);
template QDataStream& operator<<<NovelState>(QDataStream& dataStream, const NovelState& t);
template QDataStream& operator>><Stat>(QDataStream& dataStream, Stat& t);
template QDataStream& operator<<<Stat>(QDataStream& dataStream, const Stat& t);