
#include "bounding_box.hpp"
#include "coordinate_system.hpp"
#include "frustum.hpp"
#include "vector.hpp"

namespace bgl {

	class Camera {
	private: public:

		enum class Axis { X, Y, Z };

		BoundingSphere sphere;
		Vector getFocus(void) const;
		void calculateBoundingSphere(void);
	private: public:
		float angle;
		CoordinateSystem axes;
		ViewingFrustum frustum;
		Vector position, focus;
	public:
		Camera(void);
		Camera(const ViewingFrustum& frustum);
		Camera(const Vector& position, const Vector& focus, const ViewingFrustum& frustum);
		void set(void) const;

		void translate(const Vector& v);
		void rotate(Axis axis, float step);

		const Vector& getPosition(void) const;
		Vector getVisiblePosition(void) const;

		void moveLeft(float step);
		void moveRight(float step);
		void moveUp(float step);
		void moveDown(float step);
		void moveForward(float step);
		void moveBackward(float step);
		void rotateUp(float step);
		void rotateDown(float step);
		void rotateLeft(float step);
		void rotateRight(float step);
	};

}  // namespace bgl