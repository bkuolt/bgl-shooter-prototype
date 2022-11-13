#ifndef PLANE_H_
#define PLANE_H_

#include "GLUT.h"
#include "Line.h"
#include "Windows.h"
#include <cstdio>
#include <utility>


class Plane {
public:
  enum { A, B, C, D };

private:
public:
  Vector p, u, v;
  float equation[4];

public:
  /**
   * @brief Berechnet aus drei Punkten die Ebene
   */
  Plane(const Vector &P1, const Vector &P2, const Vector &P3) : p(P1) {
    Vector normal;

    // berechnet Normale
    normal = CrossProduct((u = P2 - P1), (v = P3 - P1)).normalize();
    // bestimmt Hessesche Normalenform der Ebene: D = -(Ax + By + Cz)
    equation[A] = normal[X];
    equation[B] = normal[Y];
    equation[C] = normal[Z];
    equation[D] = -DotProduct(normal, p);
  }

  Plane(void) { equation[A] = equation[B] = equation[C] = equation[D] = 0.0f; }

  Plane(float a, float b, float c, float d) {
    equation[A] = a;
    equation[B] = b;
    equation[C] = c;
    equation[D] = d;
  }

  /**
   * @brief Gibt die Normale der Ebene zur�ck
   */
  Vector getNormal(void) const {
    return Vector(equation[A], equation[B], equation[C]);
  }

  /**
   * @brief Invertiert die Normale
   */
  Vector invertNormal(void) {
    equation[A] *= -1.0f;
    equation[B] *= -1.0f;
    equation[B] *= -1.0f;
  }

  /**
   * @brief Gibt S�tzvektor der Ebene zur�ck
   */
  Vector getOrigin(void) { return p; }

  /**
   * @brief Verschiebt Ebene
   */
  Plane &translate(const Vector &v) {
    equation[D] = -DotProduct(getNormal(), p += v);
    return *this;
  }

  /**
   * @brief Berechnet Punkt auf der Ebene für Parameter r und s.
   */
  Vector getPoint(float s, float t) const { return p + (u * s) + (v * t); }

  /**
   * @brief �berpr�ft,ob die Ebene den angegebenen Punkt enth�lt
   */
  bool contains(const Vector &P) const {
    return (equation[A] * P[X]) + (equation[B] * P[Y]) + (equation[C] * P[Z]) +
               equation[D] ==
           0;
  }

  /**
   * @brief Berechnet den Abstand eines Punkts zur Ebene
   */
  float distance(const Vector &P) const {
    // d = Ax + By + Bz + D
    return (equation[A] * P[X]) + (equation[B] * P[Y]) + (equation[C] * P[Z]) +
           equation[D];
  }

  /**
   * @brief Überprüft, ob ein Punkt vor oder hinter der Ebene Liegt
   */
  bool isFrontFacing(const Vector &P) const { return distance(P) >= 0; }

  bool isBackFacing(const Vector &P) const { return distance(P) < 0; }

  /**
   * @brief �berpr�ft,ob Ebene von Strahl geschnitten wird. Die Reichweite des
   Strahls wird nicht ber�cksichtigt!
   */
  bool intersects(const Line &line) const {
    return DotProduct(line.getDirection(), getNormal()) != 0;
  }

  /**
   * @brief Berechnet den Schnittpunkt der Ebene und eines Strahl
   */
  Vector getIntersection(const Line &line) const {
    /*
    Strahl:  P = P0 + t*V
    Ebene:   0 = P.N + d | P = P0
    t = -(P0.N + d) / V.N
    P = P0 + t*V
    */
    return line.getPoint(
        -(DotProduct(line.getOrigin(), getNormal()) + equation[D]) /
        DotProduct(line.getDirection(), getNormal()));
  }

  /*
  =================================================================================

  =================================================================================*/

  /**
   * @brief Berechnet die Parameter der Ebenengleichung f�r angegebenen Punkt
   * (perp dot product)
   */
  std::pair<float, float> getParameters(const Vector &P) const {
    float f = DotProduct(u, P - p) / pow(u.length(), 2);
    // s = u.(P-p) / |u|^2
    Vector w = P - p;
    float s = DotProduct(w, CrossProduct(getNormal(), v)) /
              DotProduct(u, CrossProduct(getNormal(), v));

    float t = DotProduct(w, CrossProduct(getNormal(), u)) /
              DotProduct(v, CrossProduct(getNormal(), u));

    return std::make_pair(s, t);
  }

  void rotate(Axis axis, float angle) {
    u.rotate(axis, angle);
    v.rotate(axis, angle);

    Vector normal = getNormal();
    normal.rotate(axis, angle);

    normal.normalize();

    equation[A] = normal[X];
    equation[B] = normal[Y];
    equation[C] = normal[Z];
    equation[D] = -DotProduct(normal, p);
  }

  void draw(float s, float t) const {
    Vector a, b;
    a = u * s;
    b = v * t;

    // zeichnet Ebene
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();

    glTranslatef(p[X], p[Y], p[Z]);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(a[X], a[Y], a[Z]);
    glVertex3f(a[X] + b[X], a[Y] + b[Y], a[Z] + b[Z]);
    glVertex3f(b[X], b[Y], b[Z]);
    glEnd();

    // Normalen
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3fv((getNormal() * 10).begin());
    glEnd();
    glPopMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    glLineWidth(3);
  }
};

#endif // PLANE_H_
