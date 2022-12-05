#pragma once

#include <QString>

namespace NovelLib
{
	template<typename T>
	const T* getFromNamedMap(const std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept;

	template<typename T>
	T* getFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept;

	template<typename T>
	bool removeFromNamedMap(std::unordered_map<QString, T>& map, const QString& name, const QString& type) noexcept;
}