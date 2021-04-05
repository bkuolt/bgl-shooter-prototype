#ifndef __COORDINATESYSTEM_H__
#define __COORDINATESYSTEM_H__

#include "Vector.h"
#define __DEBUG__

class CoordinateSystem
{
    private:
        Vector axes[3];
        Vector origin;
    protected:
        void normalize(void);
    public:
        CoordinateSystem(void);
        CoordinateSystem(const Vector &origin);
        CoordinateSystem(const Vector &x,const Vector &y,const Vector &z);

        void translate(const Vector &v) const;
        void rotate(Axis axis,float angle);
        void rotate(const Vector &v,Axis axis,float angle);
        void setOrigin(const Vector &v);
        const Vector& getAxis(Axis axis) const;
        const Vector& getOrigin(void) const;
        #ifdef __DEBUG__
        void draw(float,int,int g= 0) const;
        #endif
};
#endif
