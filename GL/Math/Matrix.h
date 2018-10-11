#pragma once
#include "MathTemplate.h"

template<typename T>
struct Matrix<4,4,T>
{
	Vector<4, T> col[4];


	Vector<4,T>& operator[](int index);

private:
	constexpr static int length();
};