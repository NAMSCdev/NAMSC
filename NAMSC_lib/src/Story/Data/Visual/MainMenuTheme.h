#pragma once

///[optional?] Adjustable look options for Main Menu
class MainMenuTheme
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, MainMenuTheme&);
	friend QDataStream& operator<<(QDataStream&, const MainMenuTheme&);
public:
	MainMenuTheme() = default;

protected:
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream)
	{
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const
	{
	}
};