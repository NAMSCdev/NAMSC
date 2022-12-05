#pragma once

/// [optional?] Adjustable look options for the Main Menu
//class MainMenuTheme
//{
//	//Friends for serialization
//	friend QDataStream& operator>>(QDataStream&, MainMenuTheme&);
//	friend QDataStream& operator<<(QDataStream&, const MainMenuTheme&);
//public:
//	MainMenuTheme() = default;
//
//protected:
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to read from
//	void serializableLoad(QDataStream& dataStream)
//	{
//	}
//	/// Saving an object to a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to save to
//	void serializableSave(QDataStream& dataStream) const
//	{
//	}
//};