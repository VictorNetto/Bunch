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
	private:
		real pad;  // padding to ensure 4 word alignment

	public:
		Vector3();
		Vector3(real x, real y, real z);

		Vector3 operator+(const Vector3& other);
		Vector3 operator-(const Vector3& other);
		Vector3 operator*(real n);
		Vector3 operator/(real n);

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
	};


#ifdef DEBUG
	std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
		return os;
	}
#endif // DEBUG

}