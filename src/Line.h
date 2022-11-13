#ifndef LINE_H_
#define LINE_H_

#include "Vector.h"

class Line {
public:
  /**
   * @brief Berechnet Gerade aus zwei Punkten
   */
  Line(const Vector P1, const Vector P2) : p(P1) { u = (P2 - P1).normalize(); }

  /**
   * @brief Setzt bzw. gibt den Stützvektor (Ursprung) der Geraden zurück.
   */
  Line &setOrigin(const Vector &P) {
    p = P;
    return *this;
  }

  const Vector &getOrigin(void) const { return p; }

  /**
   * @brief Setzt bzw. gibt den Richtungsvektor der Geraden zurück.
   */
  Line &setDirection(const Vector &v) {
    u = Vector(v).normalize();
    return *this;
  }

  const Vector &getDirection(void) const { return u; }

  /**
   * @brief Berechnet f�r den angegebenen Parameter den Punkt auf der Geraden
   */
  Vector getPoint(float t) const { return p + (u * t); }

  Vector operator*(float t) const { return getPoint(t); }

  /**
   * @brief Überprüft,ob Punkt auf der Geraden liegt
   */
  bool contains(const Vector &P) const {
    return p + (u * getParameter(P)) == P;
  }

  /**
   * @brief Berechnet Parameter der Geradengleichung für angegeben Punkt
   */
  float getParameter(const Vector &P) const {
    // s = u.(P-p) / |u|^2
    return DotProduct(u, P - p);
  }

  /**
   * @brief Verschiebt Gerade
   */
  Line &translate(const Vector &v) {
    p += v;
    return *this;
  }

protected:
  Vector p, u;
};

class Ray : public Line {
private:
  float reach;

protected:
  using Line::getParameter;

public:
  /**
   * @brief Berechnet Strahl aus zwei Punkten
   */
  Ray(const Vector &P1, const Vector &P2, float reach = 0.0f)
      : Line(P1, P2), reach(reach) {}

  /**
   * @brief Überprüft,ob Punkt auf dem Strahl liegt  mit Berücksichtigung der
   * Reichweite)
   */
  bool contains(const Vector &P) const {
    if (Line::contains(P) && getParameter(P) >= 0)
      if (reach == 0.0f)
        return true;
      else
        return length(P) <= reach;
  }

  /**
   * @brief Berechnet die Strecke zwischen Ursprung der Geraden und dem
   angegbenen Punkt,welcher auf dem Strahl liegt
   */
  float length(const Vector &v) const { return (v - p).length(); }

  /**
   * @brief Setzt bzw. gibt die Reichweite (Länge) des Strahls zurück.
   */
  void setReach(float reach) { Ray::reach = reach; }

  float getReach(void) const { return reach; }
};

#endif // LINE_H_
