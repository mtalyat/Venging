#ifndef MAP_H
#define MAP_H

#include <cstdbool>
#include "Object.h"

template <class T>
class Map
	: public Object
{
public:
	/// <summary>
	/// Create an empty Map with the given width and height.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	Map(int size);
	/// <summary>
	/// Create a populated Map using the given data, with the given width and height.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="data"></param>
	Map(int size, T data[]);

	~Map();

	/// <summary>
	/// Sets the data at the given Index.
	/// </summary>
	/// <param name="index"></param>
	/// <param name="t"></param>
	void set(const int index, T t);
	/// <summary>
	/// Sets the data at the given 3D coordinate.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="t"></param>
	void set(const int x, const int y, const int z, T t);
	/// <summary>
	/// Gets the data at the given index.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	T get(const int index);
	/// <summary>
	/// Gets the data at the given 3D coordinate.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <returns></returns>
	T get(const int x, const int y, const int z);

	/// <summary>
	/// Gets the length of the data in this Map.
	/// </summary>
	/// <returns></returns>
	int length() const;

	/// <summary>
	/// Determines if the given index is within the bounds of this Map.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	bool isInMap(const int index);
	/// <summary>
	/// Determines if the 3D coordinate is within the bounds of this Map.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <returns></returns>
	bool isInMap(const int x, const int y, const int z);

	/// <summary>
	/// Clears the Map with the given T.
	/// </summary>
	/// <param name="t"></param>
	void clear(T t);

	T operator[](const int index);

private:
	int size;
	T* data;

	/// <summary>
	/// Takes a 3D coordinate represented with x, y, and z and flattens it into a 1D coordinate.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <returns></returns>
	int flatten(const int x, const int y, const int z);
};

#endif

template<class T>
inline Map<T>::Map(int size)
{
	this->size = size;
	this->data = new T[length()];
}

template<class T>
inline Map<T>::Map(int size, T data[])
{
	this->size = size;
	this->data = data;
}

template<class T>
inline Map<T>::~Map()
{
	delete(data);
}

template<class T>
inline void Map<T>::set(const int index, T t)
{
	data[index] = t;
}

template<class T>
inline void Map<T>::set(const int x, const int y, const int z, T t)
{
	set(flatten(x, y, z), t);
}

template<class T>
inline T Map<T>::get(const int index)
{
	return data[index];
}

template<class T>
inline T Map<T>::get(const int x, const int y, const int z)
{
	return get(flatten(x, y, z));
}

template<class T>
inline int Map<T>::length() const
{
	return size * size * size;
}

template<class T>
inline bool Map<T>::isInMap(const int index)
{
	return index >= 0 && index < length();
}

template<class T>
inline bool Map<T>::isInMap(const int x, const int y, const int z)
{
	return (y >= 0 && y < size) && (x >= 0 && x < size) && (z >= 0 && z < size);
}

template<class T>
inline void Map<T>::clear(T t)
{
	int i = 0;
	for (; i < size; i++)
	{
		data[i] = t;
	}
}

template<class T>
inline T Map<T>::operator[](const int index)
{
	return data[index];
}

template<class T>
inline int Map<T>::flatten(const int x, const int y, const int z)
{
	return x + size * (z + size * y);
}
