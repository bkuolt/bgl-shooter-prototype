#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Windows.h"

#include <cmath>
#include <cstdlib>
#define M_PI 3.14159265358979323846

inline float RadianToDegree(float angle)
{
	return angle * (180.0f / M_PI );
}


class Vector;

inline float DotProduct(const Vector &a,const Vector &b);
inline float Angle(const Vector &a,const Vector &b);

typedef int Axis;


enum {X,Y,Z};

class Vector
{
    private:
        float values[3];
    public:
        /*
        ==============================================
        Konstruktoren
        ==============================================*/
        Vector(float x,float y,float z = 0.0f)
        {
            values[X] = x;
            values[Y] = y;
            values[Z] = z;
        }

        Vector(void)
        {
            values[X] = values[Y] = values[Z] = 0.0f;
        }

        float& operator[](Axis axis)
        {
            return values[axis];
        }

        const float& operator[](Axis axis) const
        {
            return values[axis];
        }

        /*
        ==============================================
        Arithmetische Operationen
        ==============================================*/
        Vector& operator+=(const Vector &rhs)
        {
            values[X] += rhs.values[X];
            values[Y] += rhs.values[Y];
            values[Z] += rhs.values[Z];
            return *this;
        }

        Vector& operator-=(const Vector &rhs)
        {
            values[X] -= rhs.values[X];
            values[Y] -= rhs.values[Y];
            values[Z] -= rhs.values[Z];
            return *this;
        }

        Vector& operator*=(const Vector &rhs)
        {
            values[X] *= rhs.values[X];
            values[Y] *= rhs.values[Y];
            values[Z] *= rhs.values[Z];
            return *this;
        }

        Vector& operator*=(float k)
        {
            values[X] *= k;
            values[Y] *= k;
            values[Z] *= k;
            return *this;
        }

        Vector operator+(const Vector &rhs) const
        {
            return Vector(*this)+= rhs;
        }

        Vector operator-(const Vector &rhs) const
        {
            return Vector(*this)-= rhs;
        }

        Vector operator-(const Vector &rhs)
        {
            return Vector(*this)-= rhs;
        }

        Vector operator+(const Vector &rhs)
        {
            return Vector(*this)+= rhs;
        }

        Vector operator*(float k) const
        {
            return Vector(*this)*= k;
        }

        Vector operator*(float k)
        {
            return Vector(*this)*= k;
        }

        float length(void) const
        {
            return std::sqrt(values[X] * values[X] +
                             values[Y] * values[Y] +
                             values[Z] * values[Z]);
        }

        Vector& normalize(void)
        {
            return *this *= (1.0f / length());
        }

        /*
        ==============================================
        Rotationen
        ==============================================*/
        Vector& rotate(Axis axis,float angle)
        {
            Vector v(*this); // Kopie des Vektors
            angle = angle*= (M_PI / 180); // Grad in Bogenmaﬂ

            switch(axis)
            {
                case X:
                    values[Y] = v[Y] * cos(angle) - v[Z] * sin(angle);
                    values[Z] = v[Y] * sin(angle) + v[Z] * cos(angle);
                    break;
                case Y:
                    values[X] = v[Z] * sin(angle) + v[X] * cos(angle);
                    values[Z] = v[Z] * cos(angle) - v[X] * sin(angle);
                    break;
                case Z:
                    values[X] = v[X] * cos(angle) - v[Y] * sin(angle);
                    values[Y] = v[X] * sin(angle) + v[Y] * cos(angle);
                    break;
            }
            return *this;
        }


        Vector rotate(Axis axis,float angle) const
        {
            Vector v(*this);
            v.rotate(axis,angle);
            return v;
        }



        void rotate(const Vector &v,Axis axis,float angle)
        {
//            *this -= v;
            rotate(axis,angle);
  //          *this += v;
        }

        /*
        ==============================================
        Iteratoren Schnittstelle
        ==============================================*/
        const float* begin(void) const
        {
            return values;
        }

        float* begin(void)
        {
            return values;
        }

        const float* end(void) const
        {
             return values + 3;
        }

        float* end(void)
        {
            return values + 3;
        }

        /*
        =================================================================
        Projeziert diesen Vektor auf den angegebenen Vektor
        =================================================================*/
        Vector project(const Vector &v) const
        {
            return (v * DotProduct(*this,v)) * (1.0f/ v.length());
        }


        bool operator==(const Vector &rhs) const
        {
            return rhs[X] == values[X] &&
                   rhs[Y] == values[Y] &&
                   rhs[Z] == values[Z];
        }


};
//----------------------------------------------------------------
inline float ScalarMultiple(const Vector &u,const Vector &v)
{
	// u   = s*v
	// u/v = s
	if(v[X] != 0)
		return u[X] / v[X];
	if(v[Y] != 0)
		return u[Y] / v[Y];
	if(v[Z] != 0)
		return u[Z] / v[Z];
}

inline float DotProduct(const Vector &a,const Vector &b)
{
	return (a[X] * b[X]) + (a[Y] * b[Y]) + (a[Z] * b[Z]);
}

inline Vector CrossProduct(const Vector &a,const Vector &b)
{
	return Vector(a[1] * b[2] - b[1] * a[2],
				  a[2] * b[0] - b[2] * a[0],
				  a[0] * b[1] - b[0] * a[1]);
}

inline float Angle(const Vector &a,const Vector &b)
{
    return RadianToDegree(acos(DotProduct(a,b) / (a.length() * b.length())));
}

inline bool AreCollinear(const Vector &a,const Vector &b)
{
	return (a[X] / b[X] == a[Y] / b[Z]) == a[Z] / b[Z];
}

inline Vector Center(const Vector &a,const Vector &b)
{
	return a + (b -a) * 0.5f;
}
#endif
