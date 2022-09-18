#pragma once
#include "Global.h"

//Adjustable look options for Main Menu
class MainMenuTheme
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, MainMenuTheme &t);
	friend QIODevice &operator<<(QIODevice &device, const MainMenuTheme &t);
public:
	MainMenuTheme() = default;

protected:
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
	}
};