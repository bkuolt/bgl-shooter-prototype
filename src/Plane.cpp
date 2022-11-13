#include "Plane.h"

#include "CoordinateSystem.h"
#include "GLUT.h"
#include "Windows.h"
#include <stdio.h>


/*
n   ^u
^   /--------------->
|  /               /
| /               /
|/               /
O--------------->v
*/

/*
========================================================================
Konstruktoren
========================================================================*/
Plane::Plane(const Vector &P1, const Vector &P2, const Vector &P3) {
  p = P1;
  u = (P2 - P1).normalize();
  v = (P3 - P1).normalize();
}

Vector Plane::getNormal(void) const { return CrossProduct(u, v); }

/*
========================================================================
Zeichnet Ebene
========================================================================*/
void Plane::draw(float s, float t) const {
  Vector a, b;

  a = u * s;
  b = v * t;
  // zeichnet Ebene

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.0f, 0.0f, 1.0f, 0.65f);

  glBegin(GL_QUADS);
  glVertex3f(0, 0, 0);
  glVertex3f(a[X], a[Y], a[Z]);
  glVertex3f(a[X] + b[X], a[Y] + b[Y], a[Z] + b[Z]);
  glVertex3f(b[X], b[Y], b[Z]);
  glEnd();

  glColor3f(1.0f, 0.0f, 1.0f);
  Vector normal = getNormal() * 3;
  glLineWidth(3);

  /*
       glBegin(GL_LINES);
          glVertex3f(0,0,0);
          glVertex3f(normal[X],normal[Y],normal[Z]);
      glEnd();
  */
}
