#include "Vector.h"

#include <iostream>
#include <cassert>

#define THROW_OUT_OF_RANGE_EXCEPTION    \
	throw std::exception("Out Of Range")\


template <typename T>
template <typename V3, typename W>
constexpr Vector<4, T>::Vector(Vector<3, V3> v3, W w) :x(static_cast<T>(v3.x)),
y(static_cast<T>(v3.y)),
z(static_cast<T>(v3.z)),
w(static_cast<T>(w))
{
}

template <typename T>
template <typename V3>
constexpr Vector<4, T>::Vector(Vector<3, V3> v3) :x(static_cast<T>(v3.x)),
y(static_cast<T>(v3.y)),
z(static_cast<T>(v3.z)),
w(static_cast<T>(0))
{
}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr Vector<4, T>::Vector(X x, Y y, W w, Z z) :x(static_cast<T>(x)),
y(static_cast<T>(y)),
z(static_cast<T>(z)),
w(static_cast<T>(w))
{	
}

template <typename T>
constexpr int Vector<4, T>::length()
{
	return 4;
}

template <typename T>
T& Vector<4, T>::operator[](const int index)
{
	assert(index >= 0 && index < length());
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		THROW_OUT_OF_RANGE_EXCEPTION;
	}
}


template <typename T>
template <typename X, typename Y, typename Z>
constexpr Vector<3, T>::Vector(X x, Y y, Z z):x(static_cast<T>(x)),
									y(static_cast<T>(y)),
									z(static_cast<T>(z))
{
}
template <typename T>
template <typename X, typename Y, typename Z>
constexpr Vector<3, T>::Vector(Vector<1, X>const& x, Y y, Z z) :x(static_cast<T>(x.x)),
												y(static_cast<T>(y)),
												z(static_cast<T>(z))
{
}
template <typename T>
template <typename X, typename Y, typename Z>
constexpr Vector<3, T>::Vector(X x, Vector<1, Y>const& y, Z z) :x(static_cast<T>(x)),
												y(static_cast<T>(y.y)),
												z(static_cast<T>(z))
{
}
template <typename T>
template <typename X, typename Y, typename Z>
constexpr Vector<3, T>::Vector(X x, Y y, Vector<1, Z>const& z) :x(static_cast<T>(x)),
												y(static_cast<T>(y)),
												z(static_cast<T>(z.z))
{
}

template <typename T>
template <typename X, typename Z>
constexpr Vector<3, T>::Vector(Vector<2, X>const& x, Z z) :x(static_cast<T>(x.x)),
										 y(static_cast<T>(x.y)),
										 z(static_cast<T>(z))
{
}
template <typename T>
template <typename X>
constexpr Vector<3, T>::Vector(Vector<3, X>const& x) :x(static_cast<T>(x.x)),
									  y(static_cast<T>(x.y)),
									  z(static_cast<T>(z.z))
{
}
template <typename T>
template <typename X>
constexpr Vector<3, T>::Vector(Vector<2, X>const& x) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(static_cast<T>(0))
{
}
template <typename T>
template <typename X>
constexpr Vector<3, T>::Vector(X x) :x(static_cast<T>(x)), y(static_cast<T>(x)), z(static_cast<T>(x))
{
}


template<typename T>
constexpr int Vector<3, T>::length()
{
	return 3;
}

template <typename T>
T& Vector<3, T>::operator[](const int index)
{
	assert(index >= 0 && index < length());
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		THROW_OUT_OF_RANGE_EXCEPTION;
	}
}



template <typename T>
template <typename X, typename Y>
 Vector<2, T>::Vector(X x, Y y):x(static_cast<T>(x)),
							   y(static_cast<T>(y))
{	
}

template <typename T>
constexpr  int Vector<2, T>::length()
{
	return 2;
}

template <typename T>
T& Vector<2, T>::operator[](const int index)
{
	assert(index == 0 || index == 1);
	if (index == 0)
		return x;
	return y;
}


template <typename T>
template <typename X>
Vector<1, T>::Vector(X x):x(static_cast<T>(x))
{
}

template <typename T>
constexpr int Vector<1, T>::length()
{
	return 1;
}

template <typename T>
T& Vector<1, T>::operator[](const int index)
{
	assert(index == 0);
	return x;
}

