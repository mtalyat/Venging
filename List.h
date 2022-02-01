#ifndef LIST_H
#define LIST_H

#include <vector>
#include "Object.h"

/// <summary>
/// A wrapper class for vector that provides more C#-like methods.
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class List
	: public Object
{
public:
	List();
	List(int capacity);

	int length();
	int capacity();
	void add(T t);
	bool remove(T t);
	void removeAt(const int index);
	T get(const int index);
	void set(const int index, T t);
	void clear();
	T* getPointerToFirst();

	T operator[](const int index);

private:
	std::vector<T> content;
	unsigned int count;

	bool isInRange(const int index);
};

/// <summary>
/// Creates a new TList.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
List<T>::List()
{
	content = std::vector<T>();
	count = 0;
}

/// <summary>
/// Creates a new TList with a max length.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="capacity"></param>
template<typename T>
List<T>::List(int capacity)
{
	content = std::vector<T*>(capacity);
	count = 0;
}

/// <summary>
/// Gets the length of the TList.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
int List<T>::length()
{
	return count;
}

/// <summary>
/// Gets the max length of the TList.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
int List<T>::capacity()
{
	return content.max_size();
}

/// <summary>
/// Adds an object to this TList.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="t"></param>
template<typename T>
void List<T>::add(T t)
{
	content.push_back(t);
	count++;
}

/// <summary>
/// Removes an object from this TList.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="t"></param>
/// <returns>True if found and removed, otherwise false.</returns>
template<typename T>
bool List<T>::remove(T t)
{
	//try to find the pointer in the contents
	int i = 0;
	for (; i < length(); i++)
	{
		if (get(i) == t)
		{
			//found it
			content.erase(content.begin() + i);
			count--;
			return true;
		}
	}

	//not found
	return false;
}

template<typename T>
inline void List<T>::removeAt(const int index)
{
	//make sure in range
	if (!isInRange(index))
	{
		return;
	}

	//erase it
	content.erase(content.begin() + index);
}

/// <summary>
/// Gets the object at the given index.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="index"></param>
/// <returns></returns>
template<typename T>
T List<T>::get(const int index)
{
	if (!isInRange(index)) return nullptr;

	return content[index];
}

/// <summary>
/// Sets the object at the given index.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="index"></param>
/// <param name="t"></param>
template<typename T>
void List<T>::set(const int index, T t)
{
	if (!isInRange(index)) return;

	content.assign(content.begin() + index, t);
}

template<typename T>
inline void List<T>::clear()
{
	content.clear();
	count = 0;
}

template<typename T>
inline T* List<T>::getPointerToFirst()
{
	if (length() == 0)
	{
		return nullptr;
	}

	return &content[0];
}

/// <summary>
/// Gets the object at the given index.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="index"></param>
/// <returns></returns>
template<typename T>
T List<T>::operator[](const int index)
{
	return get(index);
}

/// <summary>
/// Determines if the index is within the bounds of the List.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="index"></param>
/// <returns></returns>
template<typename T>
bool List<T>::isInRange(const int index)
{
	return index >= 0 && index < length();
}

#endif
