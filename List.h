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
	/// <summary>
	/// Creates a new List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	List();
	/// <summary>
	/// Creates a new List with a max length.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="capacity"></param>
	List(int capacity);

	/// <summary>
	/// Gets the length of the List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	int length();
	/// <summary>
	/// Gets the max length of the List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	int capacity();
	/// <summary>
	/// Adds an object to this List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="t"></param>
	void add(T t);
	/// <summary>
	/// Removes an object from this List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="t"></param>
	/// <returns>True if found and removed, otherwise false.</returns>
	bool remove(T t);
	/// <summary>
	/// Removes an object from this List at the given index.
	/// </summary>
	/// <param name="index"></param>
	void removeAt(const int index);
	/// <summary>
	/// Gets the object at the given index.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index"></param>
	/// <returns></returns>
	T get(const int index);
	/// <summary>
	/// Sets the object at the given index.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index"></param>
	/// <param name="t"></param>
	void set(const int index, T t);
	/// <summary>
	/// Clears the list.
	/// </summary>
	void clear();
	T* getPointerToFirst();

	/// <summary>
	/// Gets the object at the given index.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index"></param>
	/// <returns></returns>
	T operator[](const int index);

private:
	std::vector<T> content;
	unsigned int count;

	/// <summary>
	/// Determines if the index is within the bounds of the List.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index"></param>
	/// <returns></returns>
	bool isInRange(const int index);
};

template<typename T>
List<T>::List()
{
	content = std::vector<T>();
	count = 0;
}

template<typename T>
List<T>::List(int capacity)
{
	content = std::vector<T*>(capacity);
	count = 0;
}

template<typename T>
int List<T>::length()
{
	return count;
}

template<typename T>
int List<T>::capacity()
{
	return content.max_size();
}

template<typename T>
void List<T>::add(T t)
{
	content.push_back(t);
	count++;
}

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

template<typename T>
T List<T>::get(const int index)
{
	if (!isInRange(index)) return NULL;

	return content[index];
}

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

template<typename T>
T List<T>::operator[](const int index)
{
	return get(index);
}

template<typename T>
bool List<T>::isInRange(const int index)
{
	return index >= 0 && index < length();
}

#endif
