#include "Matrix.h"
#include <cassert>

template <typename T>
Vector<4,T>& Matrix<4, 4, T>::operator[](const int index)
{
	assert(index >= 0 && index < length());
	return col[index];
}

template<typename T>
constexpr int Matrix<4, 4, T>::length()
{
	return 4;
}
