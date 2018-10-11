#pragma once

#include "MathTemplate.h"

template<typename T>
struct Vector<4,T>
{
	T x, y, z, w;

	template<typename X,typename Y,typename Z,typename W>
	constexpr Vector(X x, Y y, W w, Z z);
	template<typename V3,typename W>
	constexpr Vector(Vector<3, V3> v3, W w);
	template<typename V3>
	explicit constexpr Vector(Vector<3,V3> v3);

	static constexpr int length();

	T& operator[](int index);
};

template<typename T>
struct Vector<3,T>
{
	T x, y, z;

	template<typename X,typename Y,typename Z>
	constexpr Vector(X x, Y y, Z z);
	template<typename X, typename Y, typename Z>
	constexpr Vector(Vector<1, X>const& x, Y y, Z z);
	template<typename X, typename Y, typename Z>
	constexpr Vector(X x, Vector<1, Y>const& y, Z z);
	template<typename X, typename Y, typename Z>
	constexpr Vector(X x, Y y, Vector<1, Z>const& z);
	template<typename X, typename Z>
	constexpr Vector(Vector<2,X>const& x,Z z);
	template<typename X>
	constexpr explicit Vector(Vector<3, X>const& x);
    template<typename X>
	constexpr explicit Vector(Vector<2, X>const& x);
	template<typename X>
	constexpr explicit Vector(X x);

	static constexpr int length();

	T& operator[](int index);
};



template<typename T>
struct Vector<2,T>
{
	T x, y;

	template<typename X,typename Y>
	Vector(X x, Y y);

	static constexpr int length();

	T& operator[](int index);
};

template<typename T>
struct Vector<1, T>
{
	T x;
	template<typename X>
	explicit Vector(X x);

	static constexpr int length();

	T& operator[](int index);
};

