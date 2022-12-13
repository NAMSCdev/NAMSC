//#include "Helpers.h"
//
//#include "Novel/Data/Text/Voice.h"
//
//template<typename T>
//	const T* NovelLib::getFromNamedMap(const std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
//	{
//		if (!map.contains(name))
//		{
//			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
//			return nullptr;
//		}
//
//		return &(map.at(name));
//	}
//
//	template<typename T>
//	T* NovelLib::getFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
//	{
//		if (!map.contains(name))
//		{
//			qDebug() << "Tried to get an non-existent " << type << " \"" << name << "\"";
//			return nullptr;
//		}
//
//		return &(map.at(name));
//	}
//
//	template<typename T>
//	bool NovelLib::removeFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept
//	{
//		if (!map.contains(name))
//		{
//			qDebug() << "Tried to remove a non-existent " << type << " \"" << name << "\"";
//			return false;
//		}
//
//		map.erase(name);
//
//		return true;
//	}
//
//	template const Voice* NovelLib::getFromNamedMap<Voice>(const std::unordered_map<QString, Voice>& map, const QString& name, const QString& type) noexcept;
//	template Voice* NovelLib::getFromNamedMap<Voice>(std::unordered_map<QString, Voice>& map, const QString& name, const QString& type) noexcept;