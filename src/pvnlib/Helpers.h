#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "pvnLib/Exceptions.h"

/// Using C++ concepts to provide helper functions that will throw errors with more details, if they contain *duplicates* and the *error throwing is enabled* (it is a parameter)
/// Also *bound checking* and lack of *reflection* workaround (parent messages)
namespace NovelLib::Helpers
{
	// Unfortunately template code needs to be defined inside a header, so it's quite a mess...

	// Notice that there are usually 2 or 4 functions defined per operation. It is for *unnamed object handling*, *named object handling* and there might be variations for *const* and *non-const* types
	template<typename T>
	concept NotQObject = !std::derived_from<T, QObject>;

	template<typename T>
	concept NamedObject = NotQObject<T> && requires(T & t)
	{
		t.name = QString();
	};

	template<typename T>
	concept NamedPointer = NotQObject<T> && requires(T & t)
	{
		t->name = QString();
	};

	template<typename T>
	concept LabeledObject = NotQObject<T> && requires(T & t)
	{
		t.label = QString();
	};

	template<typename T>
	concept LabeledPointer = NotQObject<T> && requires(T & t)
	{
		t->label = QString();
	};

	template<typename T>
	concept NamedEntity = NamedObject<T> || NamedPointer<T>;

	template<typename T>
	concept LabeledEntity = LabeledObject<T> || LabeledPointer<T>;

	template<typename T>
	concept IdentifiedEntity = NamedEntity<T> || LabeledEntity<T>;

	template<NamedObject T>
	QString getIdentifier(const T& object)
	{
		return object.name;
	}

	template<NamedPointer T>
	QString getIdentifier(const T& pointer)
	{
		return pointer->name;
	}

	template<LabeledObject T>
	QString getIdentifier(const T& object)
	{
		return object.label;
	}

	template<LabeledPointer T>
	QString getIdentifier(const T& pointer)
	{
		return pointer->label;
	}

	template<NamedObject T>
	void setIdentifier(T& object, const QString& name)
	{
		object.name = name;
	}

	template<NamedPointer T>
	void setIdentifier(T& pointer, const QString& name)
	{
		pointer->name = name;
	}

	template<LabeledObject T>
	void setIdentifier(T& object, const QString& label)
	{
		object.label = label;
	}

	template<LabeledPointer T>
	void setIdentifier(T& pointer, const QString& label)
	{
		pointer->label = label;
	}

	template<typename T>
	const typename T::pointer itToPtr(const T& it)
	{
		return &*it;
	}

	template<typename T>
	typename T::pointer itToPtr(T& it)
	{
		return &*it;
	}

	QString parentMsg(const QString& parentType, const QString& parentName, const QString& parentParentType, const QString& parentParentName);

	//template<IdentifiedEntity T>
	//bool isNameEqual(const QString& name, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	//{
	//	if (getIdentifier(entity) != name)
	//	{
	//		if (bThrowErrors)
	//			qCritical() << errorTypeInvalid << type + "'s name missmatch (name=\"" + name + "\", instace name=\"" + getIdentifier(entity) + "\")" + parentMsg(parentType, parentName, parentParentType, parentParentName);
	//		return false;
	//	}
	//	return true;
	//}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator checkListExistence(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getIdentifier(listEntity) == name; });
		if (ret == list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator checkListDuplicate(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getIdentifier(listEntity) == name; });
		if (ret != list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " \"" + name + "\" already exists" + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	template<LabeledEntity T>
	typename std::vector<T>::iterator checkListDuplicate(std::vector<T>& list, const QString& label, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (label.isEmpty())
			return list.end();
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&label](T& listEntity) { return getIdentifier(listEntity) == label; });
		if (ret != list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " \"" + label + "\" already exists" + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	// Maps

	template<typename T>
	bool checkMapExistence(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!map.contains(key))
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + key + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	template<typename T>
	bool checkMapDuplicate(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (map.contains(key))
		{
			if (bThrowErrors)
				qCritical() << errorTypeInvalid << type + " \"" + key + "\" already exists" + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	template<typename T>
	const T* mapGet(const std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(map.at(key));	
	}

	template<typename T>
	T* mapGet(std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		return &(map.at(key));
	}

	template<IdentifiedEntity T>
	T* mapSet(std::unordered_map<QString, T>& map, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		return &(map[getIdentifier(entity)] = entity);
	}

	template<IdentifiedEntity T>
	T* mapSet(std::unordered_map<QString, T>& map, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		const QString name = getIdentifier(entity);
		if (map.contains(name))
			map.erase(name);

		map.emplace(name, std::move(entity));
		
		return &map.at(name);
	}

	template<IdentifiedEntity T>
	T* mapRename(std::unordered_map<QString, T>& map, const QString& oldName, const QString& newName, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, oldName, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		if (!checkMapDuplicate(map, newName, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return nullptr;

		T&& object = std::move(map.at(oldName));
		setIdentifier(object, newName);

		auto iteratorBoolPair = map.emplace(newName, std::move(object));
		map.erase(oldName);
		
		return &(iteratorBoolPair.first->second);
	}

	template<typename T>
	bool mapRemove(std::unordered_map<QString, T>& map, const QString& key, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true) noexcept
	{
		if (!checkMapExistence(map, key, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return false;

		map.erase(key);

		return true;
	}

	// Lists

	template<typename T>
	bool checkListIndex(const std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index >= list.size())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Index " + QString::number(index) + " exceeds container's size " + QString::number(list.size()) + parentMsg(parentType, parentName, parentParentType, parentParentName);
			return false;
		}
		return true;
	}

	template<typename T>
	typename std::vector<T>::const_iterator listGet(const std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.cend();

		return list.cbegin() + index;
	}

	template<typename T>
	typename std::vector<T>::iterator listGet(std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		return list.begin() + index;
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::const_iterator listGet(const std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::const_iterator ret = std::find_if(list.cbegin(), list.cend(), [&name](const T& listEntity) { return getIdentifier(listEntity) == name; });
		if (ret == list.cend())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator listGet(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = std::find_if(list.begin(), list.end(), [&name](T& listEntity) { return getIdentifier(listEntity) == name; });
		if (ret == list.end())
		{
			if (bThrowErrors)
				qCritical() << errorTypeMissing << "Tried to get a non-existent " + type + "\"" + name + '\"' + parentMsg(parentType, parentName, parentParentType, parentParentName);
		}
		return ret;
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator listInsert(std::vector<T>& list, uint index, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index != 0 && !checkListIndex(list, index - 1, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		typename std::vector<T>::iterator ret = checkListDuplicate(list, getIdentifier(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return list.end();

		return list.insert(list.begin() + index, entity);
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator listInsert(std::vector<T>& list, uint index, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index != 0 && !checkListIndex(list, index - 1, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		typename std::vector<T>::iterator ret = checkListDuplicate(list, getIdentifier(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return list.end();

		return list.insert(list.begin() + index, std::move(entity));
	}

	template<typename T>
	typename std::vector<T>::iterator listInsert(std::vector<T>& list, uint index, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index != 0 && !checkListIndex(list, index - 1, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		return list.insert(list.begin() + index, entity);
	}

	template<typename T>
	typename std::vector<T>::iterator listInsert(std::vector<T>& list, uint index, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index != 0 && !checkListIndex(list, index - 1, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		return list.insert(list.begin() + index, std::move(entity));
	}

	template<typename T>
	typename std::vector<T>::iterator listReinsert(std::vector<T>& list, uint index, uint newIndex, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (index == newIndex)
			return list.begin() + index;

		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		if (newIndex != 0 && !checkListIndex(list, newIndex - 1, type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return list.end();

		if (index < newIndex)
			--newIndex;

		T&& movedElement = std::move(list.at(index));
		list.erase(list.begin()  + index);

		return list.insert(list.begin() + newIndex, std::move(movedElement));
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator listAdd(std::vector<T>& list, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListDuplicate(list, getIdentifier(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return list.end();

		list.push_back(entity);

		return list.end() - 1;
	}

	template<typename T>
	typename std::vector<T>::iterator listAdd(std::vector<T>& list, const T& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		list.push_back(entity);

		return list.end() - 1;
	}

	template<IdentifiedEntity T>
	typename std::vector<T>::iterator listAdd(std::vector<T>& list, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListDuplicate(list, getIdentifier(entity), type, errorTypeInvalid, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret != list.end())
			return list.end();

		list.push_back(std::move(entity));

		return list.end() - 1;
	}

	template<typename T>
	typename std::vector<T>::iterator listAdd(std::vector<T>& list, T&& entity, const QString& type, NovelLib::ErrorType errorTypeInvalid = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		list.push_back(std::move(entity));

		return list.end() - 1;
	}

	template<typename T>
	bool listRemove(std::vector<T>& list, uint index, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		if (!checkListIndex(list, index, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors))
			return false;

		list.erase(list.begin() + index);

		return true;
	}

	template<IdentifiedEntity T>
	bool listRemove(std::vector<T>& list, const QString& name, const QString& type, NovelLib::ErrorType errorTypeMissing = NovelLib::ErrorType::General, const QString& parentType = "", const QString& parentName = "", const QString& parentParentType = "", const QString& parentParentName = "", bool bThrowErrors = true)
	{
		typename std::vector<T>::iterator ret = checkListExistence(list, name, type, errorTypeMissing, parentType, parentName, parentParentType, parentParentName, bThrowErrors);
		if (ret == list.end())
			return false;

		list.erase(ret);

		return true;
	}
}