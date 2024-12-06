#ifndef __COORDINATESYSTEM_H__
#define __COORDINATESYSTEM_H__

#include "Vector.hpp"
#define __DEBUG__

namespace bgl {
	class CoordinateSystem
	{
	private:
		Vector axes[3];
		Vector origin;
	protected:
		void normalize(void);
	public:
		enum class Axis { X, Y, Z };

		CoordinateSystem(void);
		CoordinateSystem(const Vector& origin);
		CoordinateSystem(const Vector& x, const Vector& y, const Vector& z);

		void translate(const Vector& v) const;
		void rotate(int axis, float angle);
		void rotate(const Vector& v, int axis, float angle);
		void setOrigin(const Vector& v);
		const Vector& getAxis(int axis) const;
		const Vector& getOrigin(void) const;
#ifdef __DEBUG__
		void draw(float, int, int g = 0) const;
#endif
	};
#endif

}  // namespace bgl