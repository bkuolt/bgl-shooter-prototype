#include "BoundingBox.h"
#include <GL/GL.h>
#include <algorithm>

/*
F-------------L-------------G
|\            |            /|
| \           |           / |
|--\----------K----------/--|
|   \         |         /   |
|    \        |        /    |
E-----\---------------/-----H
 \     \             /     /
  \     B-----J-----C     /
   \    |     |     |    /
    \   |     |     |   /
     \  |-----I-----|  /
      \ |     |     | /
       \|     |     |/
        A-----------D
*/

/*
=================================================================================
=                                                                               =
=                                Viewing Frustum                                =
=                                                                               =
=================================================================================*/
ViewingFrustum::ViewingFrustum(void)
			  : near(1),far(10),width(2),height(2),
                OBB(AABB(Vector(),Vector()))  /* sinnlos! */ {
    set();
    calculateVertices();
    calculatePlanes();
    angles[X] = 0.0f;
    angles[Y] = 0.0f;
}

ViewingFrustum::ViewingFrustum(float width,float height,float near,float far)
              : near(near),far(far),width(width),height(height),
                OBB(AABB(Vector(),Vector()))  /* sinnlos! */ {
    set();
    calculateVertices();
    calculatePlanes();
    angles[X] = 0.0f;
    angles[Y] = 0.0f;
}

/*
=================================================================================
Berechnet alle Ebenen des Kegelstumpfs
=================================================================================*/
void ViewingFrustum::calculatePlanes(void) {
	planes[0] = Plane(vertices[A], vertices[D], vertices[B]);  // Vorderseite
	planes[1] = Plane(vertices[E], vertices[F], vertices[H]);  // Rückseite
	planes[2] = Plane(vertices[A], vertices[B], vertices[E]);  // linke Seite
	planes[3] = Plane(vertices[D], vertices[H], vertices[C]);  // rechte Seite
	planes[4] = Plane(vertices[B], vertices[C], vertices[F]);  // Oberseite
	planes[5] = Plane(vertices[A], vertices[E], vertices[D]);  // Unterseite
}

/*
=================================================================================
Berechnet alle Eckpunkte des Kegelstumpfs
=================================================================================*/
void ViewingFrustum::calculateVertices(void) {
	Vector vertices[8];
	Vector I, J, K, L;
    float depth  = far - near;
	float width  = ViewingFrustum::width;
	float height = ViewingFrustum::height;
	float near = -ViewingFrustum::near;
	float far  = -ViewingFrustum::far;
    float ratio;

	// (1) Berechnet Eckpunkte der Vorderseite
	vertices[A] = Vector(-width / 2, -height / 2, near);
	vertices[B] = Vector(-width / 2, height / 2, near);
	vertices[C] = Vector(width / 2, height / 2, near);
	vertices[D] = Vector(width / 2, -height / 2, near);

	// (2) Berechnet Punkte auf der Vorderseite
	I = Vector(0.0f, 0.0f, near);
	J = Vector(0.0f, height, near);

	// (3) Definiert Geraden
	Line g = Line(Vector(), I);
	Line h = Line(Vector(), J);

	// (4) Berechnet Punkte auf der Rückseite
	K = g * (far / I[Z]);
	L = h * (far / I[Z]);

	// (5) Berechnet Maße der Rückseite
	ratio  = width / height;
	height = L[Y] - K[Y];
	width  = height / ratio;

    // DEBUG:
    height *= 2.25;
    width  *= 2.25;

	// (6) Berechnet Eckpunkte der Rückseite
	vertices[E] = K + Vector(-width / 2, -height / 2, 0.0f);
	vertices[F] = K + Vector(-width / 2, height / 2, 0.0f);
	vertices[G] = K + Vector(width / 2, height / 2, 0.0f);
	vertices[H] = K + Vector(width / 2, -height / 2, 0.0f);

    // (7) Kopiert Vertices in spezialisierte OBB
    std::copy(vertices, vertices + 8, OBB::vertices);
    std::copy(vertices, vertices + 8, unrotated_vertices);  // unrotierte Kopie
}

/*
=================================================================================
Verwendet diesen Kegelstumpf bzw. setz diesen als aktuellen
=================================================================================*/
void ViewingFrustum::set(void) const {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-width / 2, width / 2, -height / 2, height / 2, near, far);
}

/*
=================================================================================
Gibt Pyramidenpitze zur�ck
=================================================================================*/
const Vector& ViewingFrustum::getApex(void) const {
	return apex;
}

/*
=================================================================================
Gibt Vektor der Blickrichtung zur�ck (buggy)
=================================================================================*/
Vector ViewingFrustum::getViewDirection(void) {
	return planes[0].getNormal().normalize();
}

/*
=================================================================================
�berpr�ft,ob sich AABB (zumindest teilwiese) im Frustum befindet
HINWEIS: M�glicherweise etwas ungenau!
=================================================================================*/
bool ViewingFrustum::isWithin(const AABB &rhs) const {
    for (size_t i = 0; i < 6; ++i) {
        if (planes[i].distance(rhs[0]) < 0.0f) continue;
        if (planes[i].distance(rhs[1]) < 0.0f) continue;
        if (planes[i].distance(rhs[2]) < 0.0f) continue;
        if (planes[i].distance(rhs[3]) < 0.0f) continue;
        if (planes[i].distance(rhs[4]) < 0.0f) continue;
        if (planes[i].distance(rhs[5]) < 0.0f) continue;
        if (planes[i].distance(rhs[6]) < 0.0f) continue;
        if (planes[i].distance(rhs[7]) < 0.0f) continue;
        return false;
    }
    return true;
}

/*
=================================================================================
�berpr�ft,ob sich Punkt im Frustum befindet
=================================================================================*/
bool ViewingFrustum::isWithin(const Vector &P) const {
    for (size_t i = 0; i < 6; ++i)
        if (planes[i].distance(P) < 0.0f)
            return false;
    return true;
}

#ifdef __DEBUG__
/*
*********************************************************************************
* HINWEIS: �berpr�ft,ob eine AABB aus der Verwaltungsliste den Kegelstumpf      *
*          schneidet!                                                           *
*********************************************************************************/
extern std::set<AABB*> list;

bool ViewingFrustum::isWithin(void) const {
    for (std::set<AABB*>::const_iterator iterator = list.begin(); iterator != list.end(); ++iterator)
        if (isWithin(**iterator))
            return true;
    return false;
}
#endif

/*
=================================================================================
Verschiebt Kegelstumpf
=================================================================================*/
void ViewingFrustum::translate(const Vector &v) {
	OBB::translate(v);
	for (size_t i = 0; i < 8; ++i) unrotated_vertices[i] += v;
	apex += v;
}

/*
=================================================================================
Rotiert Kegelstumpf
=================================================================================*/
void ViewingFrustum::rotate(const Vector &v,Axis axis,float angle) {
    angles[axis] += angle;
    // Überschreibt alte unrotierte Eckpunkte
    std::copy(unrotated_vertices, unrotated_vertices + 8, vertices);

    // Eckpunkte rotieren
	for (size_t i = 0; i < 8; ++i){
		vertices[i]-= v;
		vertices[i].rotate(X, angles[X]);
		vertices[i]+= v;
	}

	for (size_t i = 0; i < 8; ++i){
		vertices[i]-= v;
		vertices[i].rotate(Y, angles[Y]);
		vertices[i]+= v;
	}

    // Ebenen neu berechnen
    calculatePlanes();
}
