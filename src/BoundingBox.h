#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#include "Windows.h"
#include "GLee.h"
#include "GLUT.h"

#include "Line.h"
#include "Plane.h"


#include <cstdio>
#include <set>
#include "CoordinateSystem.h"
#define __DEBUG__


class BoundingBox {
 public:
    enum Vertex { A, B, C, D, E, F, G, H};
 public:
    Vector vertices[8];
 public:
    const Vector& operator[](size_t) const;
    Vector& operator[](size_t);
    #ifdef __DEBUG__
    void draw(void) const;
    #endif
};


class BoundingSphere {
 private:
    Vector center;
    float radius;
 public:
    BoundingSphere(void) {}
    BoundingSphere(const Vector &center, float radius);

    bool intersects(const BoundingSphere &rhs) const;

    BoundingSphere& translate(const Vector &v);
    float getRadius(void) const;
    const Vector& getCenter(void) const;
    void draw(void) const;
};

class AxisAlignedBoundingBox : public BoundingBox {
    public:public:
        Plane planes[6];
	public:
        AxisAlignedBoundingBox() {}
        AxisAlignedBoundingBox(float width, float height, float depth, const Vector &center = Vector());
        AxisAlignedBoundingBox(const float *vertices, size_t count);
        AxisAlignedBoundingBox(const Vector &min, const Vector &max);
        ~AxisAlignedBoundingBox(void);
        void calculateVertices(const Vector &min, const Vector &max);
        Vector getCenter(void) const;
        float getWidth(void) const;
        float getHeight(void) const;
        float getDepth(void) const;
        Vector getRadius(void) const;
        AxisAlignedBoundingBox& translate(const Vector &v);
        AxisAlignedBoundingBox& scale(const Vector &v);
        AxisAlignedBoundingBox& scale(float k);
        bool intersects(const AxisAlignedBoundingBox &rhs) const;
        bool intersects(const Ray &rhs) const;
        void calculatePlanes();
        bool intersects(const BoundingSphere &sphere) const;

        bool isWithin(const Vector&) const;
		void manage(void);

        const Plane & getPlane(size_t i) const;
        void position(const Vector &v);

        const Vector& operator[](size_t i) const {
            return vertices[i];
        }

        Vector& operator[](size_t i) {
            return vertices[i];
        }

        void draw(void) const ;
#if 0
        {
            glPushMatrix();
            Vector center = getCenter();

            glPushAttrib(GL_CURRENT_BIT);
            glPushMatrix();
                glTranslatef(center[X],center[Y],center[Z]);
                glScalef(getWidth(),getHeight(),getDepth());
                glColor3f(1.0f,0.0f,0.0f);
                glutWireCube(1);
            glPopMatrix();
            glPopAttrib();
            for(size_t i = 0;i < 6;++i)
                planes[i].draw(1,1);
            glPopMatrix();
        }
#endif  // 0
};
typedef AxisAlignedBoundingBox OrientedBoundingVolume;

class OBB : public AxisAlignedBoundingBox{
 public:
    OBB(const AxisAlignedBoundingBox &aabb);

    bool isWithin(const Vector &P) const;
    bool intersects(const AxisAlignedBoundingBox &rhs) const;
    OBB& rotate(Axis axis, float angle);

    bool intersects(const Ray &ray) const {
        return AxisAlignedBoundingBox::intersects(ray);
    }
};


using = AABB AxisAlignedBoundingBox
#undef near
#undef far

class ViewingFrustum : public OBB {
 private: public:
	float angles[2];
	float width;
	float height;
	float near;
	float far;
	Vector unrotated_vertices[8];
	Vector apex;
 public:
	ViewingFrustum(float width, float height, float near, float far);
	ViewingFrustum();
	void set(void) const;
	bool isWithin(const Vector &P) const;
	const Vector& getApex(void) const;
	Vector getViewDirection(void);
	void translate(const Vector &v);
	void rotate(const Vector &v, Axis axis, float angle);
	void calculatePlanes(void);

	void calculateVertices(void);
//using OBB::intersects
	bool isWithin(const AABB &rhs) const;
	bool isWithin(void) const;
};

//========================================================================================================

class Camera {
 private: public:
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
    Camera(const ViewingFrustum &frustum);
    Camera(const Vector &position, const Vector &focus, const ViewingFrustum &frustum);
    void set(void) const;

    void translate(const Vector &v);
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

void GLUTCameraCallback(int key, bool ascii);

namespace CD {
bool WouldHaveWallCollision(const Vector&);
}  // namespace CD

#endif
