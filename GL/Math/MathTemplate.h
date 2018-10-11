#pragma once


template<int col, typename T> struct Vector;
template<int col, int row, typename T> struct Matrix;

typedef Vector<4, float> Vector4;
typedef Vector<3, float> Vector3;
typedef Vector<2, float> Vector2;
typedef Vector<1, float> Vector1;

typedef Matrix<4, 4, float> Matrix4x4;