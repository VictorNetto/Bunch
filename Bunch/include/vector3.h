#pragma once

#include <precision.h>

#ifdef  DEBUG
#include <iostream>
#endif //  DEBUG


namespace bunch {

	/*
	  A 3-dimensional vector represented internally as 3 real values (the cartesian coordinates).
	  An other real value (pad) is also present to ensure 4 word alignment and then improve performance.

	  Utilities functions such sum and dot product are avaible.
	*/
	class Vector3 {
	public:
		real x, y, z;  // the cartesian coordinates of the Vector3

	public:
		Vector3();
		Vector3(real x, real y, real z);

		void operator+=(const Vector3& other);
		void operator-=(const Vector3& other);
		void operator*=(real n);
		void operator/=(real n);

		real dot(const Vector3& other);
		Vector3 cross(const Vector3& other);

		real length_square();
		real length();

		void to_unit();  // make *this a unit vector
		Vector3 get_unit();  // get the unit vector of *this

	private:
		real pad;  // padding to ensure 4 word alignment
	};

	Vector3 operator+(const Vector3& vec, const Vector3& vec2);
	Vector3 operator-(const Vector3& vec, const Vector3& vec2);
	Vector3 operator*(const Vector3& vec, real n);
	Vector3 operator/(const Vector3& vec, real n);

	const Vector3 X_DIR = { 1, 0, 0 };
	const Vector3 Y_DIR = { 0, 1, 0 };
	const Vector3 Z_DIR = { 0, 0, 1 };

	const Vector3 RIGHT_VECTOR = X_DIR;
	const Vector3 LEFT_VECTOR = X_DIR * (-1);
	const Vector3 UP_VECTOR = Y_DIR;
	const Vector3 DOWN_VECTOR = Y_DIR * (-1);
	const Vector3 OUTSIDE_VECTOR = Z_DIR;
	const Vector3 INSIDE_VECTOR = Z_DIR * (-1);

#ifdef DEBUG
	std::ostream& operator<<(std::ostream& os, const Vector3& vector);
#endif // DEBUG

}