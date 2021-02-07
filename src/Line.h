#ifndef LINE_H__
#define LINE_H__

#include "Vector.h"

class Line {
	protected:
		Vector p,u;
	public:
        /*
		=======================================================================
		Berechnet Gerade aus zwei Punkten
		========================================================================*/
		Line(const Vector P1,const Vector P2) : p(P1)
		{
			u = (P2 - P1).normalize();
		}

        /*
		=======================================================================
		Setzt bzw. gibt den St�tzvektor (Ursprung) der Geraden zur�ck
		========================================================================*/
		Line& setOrigin(const Vector &P)
		{
		    p = P;
            return *this;
		}

		const Vector& getOrigin(void) const
		{
			return p;
		}

        /*
		=======================================================================
		Setzt bzw. gibt den Richtungsvektor der Geraden zur�ck
		========================================================================*/
		Line& setDirection(const Vector &v)
		{
		    u = Vector(v).normalize();
            return *this;
		}

		const Vector& getDirection(void) const
		{
			return u;
		}

        /*
		=======================================================================
		Berechnet f�r den angegebenen Parameter den Punkt auf der Geraden
		========================================================================*/
		Vector getPoint(float t) const
		{
			return p + (u * t);
		}

		Vector operator*(float t) const
		{
			return getPoint(t);
		}

        /*
		=======================================================================
		�berpr�ft,ob Punkt auf der Geraden liegt
		========================================================================*/
		bool contains(const Vector &P) const
		{
			return p + (u * getParameter(P)) == P;
		}

        /*
		=======================================================================
		Berechnet Parameter der Geradengleichung f�r angegeben Punkt
		========================================================================*/
		float getParameter(const Vector &P) const
		{
            // s = u.(P-p) / |u|^2
			return DotProduct(u,P-p);
		}

        /*
		=======================================================================
		Verschiebt Gerade
		========================================================================*/
		Line& translate(const Vector &v)
		{
			p+= v;
			return *this;
		}
};

class Ray : public Line
{
	private:
		float reach;
	protected:
		using Line::getParameter;
	public:
        /*
		=======================================================================
		Berechnet Strahl aus zwei Punkten
		========================================================================*/
		Ray(const Vector &P1,const Vector &P2,float reach = 0.0f) : Line(P1,P2),reach(reach)
		{}

        /*
		=======================================================================
		�berpr�ft,ob Punkt auf dem Strahl liegt  mit Ber�cksichtigung der Reichweite)
		========================================================================*/
		bool contains(const Vector &P) const
		{
			if(Line::contains(P) && getParameter(P) >= 0)
				if(reach == 0.0f)
					return true;
				else
					return length(P) <= reach;
		}

        /*
		=======================================================================
		Berechnet die Strecke zwischen Ursprung der Geraden und dem angegbenen
		Punkt,welcher auf dem Strahl liegt
		========================================================================*/
		float length(const Vector &v) const
		{
			return (v - p).length();
		}

        /*
		=======================================================================
		Setzt bzw. gibt die Reichweite (L�nge) des Strahls zur�ck
		========================================================================*/
		void setReach(float reach)
		{
			Ray::reach = reach;
		}

		float getReach(void) const
		{
			return reach;
		}
};
#endif
