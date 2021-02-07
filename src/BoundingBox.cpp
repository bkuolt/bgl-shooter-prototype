#include "BoundingBox.h"

#ifdef __DEBUG__
/*
*********************************************************************************
* HINWEIS: Für Testzwecke werden alle AABBs in dieser Liste gespeichert!        *
*********************************************************************************/
std::set<AABB*> list;
#endif

/*
=================================================================================
=                                                                               =
=                        Axis Aligned Bounding Box                              =
=                                                                               =
=================================================================================*/
/*
  F-------G
/ |      /|
B-------C |
| |     | |
| E-----|-H
|/      |/
A-------D
*/

/*
=================================================================================
Berechnet aus den Punkten A und G die AABB
=================================================================================*/
AABB::AABB(const Vector &min,const Vector &max)
{
	calculateVertices(min,max);
	calculatePlanes();
	translate(min - vertices[A]); // Positioniert AABB
}

/*
=================================================================================
Berechnet aus den Maßen und dem Mittelpunkt die AABB
=================================================================================*/
AABB::AABB(float width,float height,float depth,const Vector &center)
{
	calculateVertices(center + Vector(-width / 2,-height / 2,-depth / 2),
					  center + Vector( width / 2, height / 2, depth / 2));
	calculatePlanes();
}

#ifdef __DEBUG__
/*
=================================================================================
Berechnet aus den angegebenen Eckpunkten die umschließende AABB
=================================================================================*/
AABB::AABB(const float *vertices,size_t count)
{
	Vector min,max;

	for(size_t i = 0;i < count;++i)
		for(size_t c = 0;c < 3;++c)
			if(vertices[(i * 3) + c] > max[c])
				max[c] = vertices[(i * 3) + c];
			else if(vertices[(i * 3) + c] < min[c])
				min[c] = vertices[(i * 3) + c];

	calculateVertices(min,max);
	calculatePlanes();
}
#endif

#ifdef __DEBUG__
/*
=================================================================================
Verwaltet AABB in einer Liste
=================================================================================*/
void AABB::manage(void)
{
    list.insert(this);
}

AABB::~AABB(void)
{
    list.erase(this);
}
#endif

/*
=================================================================================
Berechnet Eckpunkte
=================================================================================*/
void AABB::calculateVertices(const Vector &min,const Vector &max)
{
    Vector center = getCenter();
	float width  = fabs(max[X] - min[X]);
	float height = fabs(max[Y] - min[Y]);
	float depth  = fabs(max[Z] - min[Z]);

	vertices[A] = center + Vector(-width / 2,-height / 2, depth / 2);
	vertices[B] = center + Vector(-width / 2, height / 2, depth / 2);
	vertices[C] = center + Vector( width / 2, height / 2, depth / 2);
	vertices[D] = center + Vector( width / 2,-height / 2, depth / 2);
	vertices[E] = center + Vector(-width / 2,-height / 2,-depth / 2);
	vertices[F] = center + Vector(-width / 2, height / 2,-depth / 2);
	vertices[G] = center + Vector( width / 2, height / 2,-depth / 2);
	vertices[H] = center + Vector( width / 2,-height / 2,-depth / 2);
}

/*
=================================================================================
Berechnet Ebenenen
=================================================================================*/
void AABB::calculatePlanes(void)
{
	planes[0] = Plane(vertices[A],vertices[D],vertices[B]); // Vorderseite
	planes[1] = Plane(vertices[E],vertices[F],vertices[H]); // Rückseite
	planes[2] = Plane(vertices[A],vertices[B],vertices[E]); // linke Seite
	planes[3] = Plane(vertices[D],vertices[H],vertices[C]); // rechte Seite
	planes[4] = Plane(vertices[B],vertices[C],vertices[F]); // Oberseite
	planes[5] = Plane(vertices[A],vertices[E],vertices[D]); // Unterseite
}

/*
=================================================================================
Überprüft,ob die AABB vom angegebenem Strahl getroffen wird
=================================================================================*/
bool AABB::intersects(const Ray &ray) const
{
	Vector intersection;
	Vector min = vertices[A];
	Vector max = vertices[G];
	std::pair<float,float> parameters;

	for(size_t i = 0;i < 6;++i)
		if(planes[i].intersects(ray)){
			// (1) berechnet Schnittpunkt mit der Ebene und die Parametes für den Schnittpunkt
			intersection = planes[i].getIntersection(ray);
            parameters = planes[i].getParameters(intersection);

            // (2) überprüft,ob die Reichweite des Strahls ausreicht
        	if(ray.contains(intersection))
                // (3) überprüft,ob Schnittpunkt auf einer der Seitenflächen liegt
				if((parameters.first  > 0.0f && parameters.first  < 1.0f) &&
                   (parameters.second > 0.0f && parameters.second < 1.0f))
				   return true;
		}
	return false;
}

/*
=================================================================================
Überprüft,ob die AABB mit der angegebenen AABB kollidiert
=================================================================================*/
bool AABB::intersects(const AABB &rhs) const
{
    Vector distance = getCenter() - rhs.getCenter(); // Abstand der Mittelpunkte

    if(fabs(distance[X]) > fabs(getWidth()  + rhs.getWidth()))  return false;
    if(fabs(distance[Y]) > fabs(getHeight() + rhs.getHeight())) return false;
    if(fabs(distance[Z]) > fabs(getDepth()  + rhs.getDepth()))  return false;
    return true;
}

/*
=================================================================================
Überprüft,ob Punkt in der AABB liegt
=================================================================================*/
bool AABB::isWithin(const Vector &v) const
{
    return (vertices[A][X] < v[X] && vertices[D][X] > v[X]) &&
           (vertices[A][Y] < v[Y] && vertices[B][Y] > v[Y]) &&
           (vertices[A][Z] > v[Z] && vertices[E][Z] < v[Z]);
}

/*
=================================================================================
Verschiebt die AABB
=================================================================================*/
AABB& AABB::translate(const Vector &v)
{
	for(size_t i = 0;i < 8;++i)
		vertices[i] += v;
    for(size_t i = 0;i < 6;++i)
		planes[i].translate(v);
	return *this;
}

/*
=================================================================================
Berechnet Mittelpunkt der AABB
=================================================================================*/
Vector AABB::getCenter(void) const
{
	return vertices[A] + (vertices[G] - vertices[A]) * 0.5f;
}

/*
=================================================================================
Positioniert AABB mit dem Mittelpunkt an angegebener Position
=================================================================================*/
void AABB::position(const Vector &v)
{
    translate(v - getCenter());
}

/*
=================================================================================
Berechnet die Maße der AABB
=================================================================================*/
float AABB::getWidth(void) const
{
	return fabs(vertices[D][X] - vertices[A][X]);
}

float AABB::getHeight(void) const
{
	return fabs(vertices[B][Y] - vertices[A][Y]);
}

float AABB::getDepth(void) const
{
    return fabs(vertices[E][Z] - vertices[A][Z]);
}

/*
=================================================================================
Gibt Ebenen der Seitenflächen zurück
=================================================================================*/
const Plane & AABB::getPlane(size_t i) const
{
    return planes[i];
}

#ifdef __DEBUG__
void AABB::draw(void) const
{
    static const GLubyte indices[] = {
        0,1,2,3,
        0,3,4,5,
        0,5,6,1,
        1,6,7,2,
        7,4,3,2,
        4,7,6,5};

    GLfloat points[24] = {
        vertices[C][X],vertices[C][Y],vertices[C][Z],
        vertices[B][X],vertices[B][Y],vertices[B][Z],
        vertices[A][X],vertices[A][Y],vertices[A][Z],
        vertices[D][X],vertices[D][Y],vertices[D][Z],
        vertices[H][X],vertices[H][Y],vertices[H][Z],
        vertices[G][X],vertices[G][Y],vertices[G][Z],
        vertices[F][X],vertices[F][Y],vertices[F][Z],
        vertices[E][X],vertices[E][Y],vertices[E][Z]};

    glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glColor3f(1.0f,0.0f,0.0f);

        glVertexPointer(3,GL_FLOAT,0,points);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indices);
        glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
}
#endif

/*
=================================================================================
=                                                                               =
=                          Oriented Bounding Box                                =
=                                                                               =
=================================================================================*/

/*
=================================================================================
Konstruiert OBB aus AABB (ist explizit nötig,da AABB kein Standardkonstruktor hat)
=================================================================================*/
OBB::OBB(const AABB &aabb) : AABB(aabb)
{}

/*
=================================================================================
Überprüft,ob sich der angegebene Punkt in der OBB befindet
=================================================================================*/
bool OBB::isWithin(const Vector &P) const
{
	for(size_t i = 0;i < 6;++i)
		if(planes[i].distance(P) > 0.0f)
			return false;
	return true;
}

/*
=================================================================================
Überprüft,ob diese OBB und die angegeben AABB/OBB kollidieren
=================================================================================*/
bool OBB::intersects(const AABB &rhs) const
{
	for(size_t i = 0;i < 8;++i)
		if(isWithin(rhs.vertices[i]) || rhs.isWithin(vertices[i]))
			return true;
	return false;
}

/*
=================================================================================
Rotiert die OBB
=================================================================================*/
OBB& OBB::rotate(Axis axis,float angle)
{
    Vector center = getCenter();

    // Eckpunkte rotieren
	for(size_t i = 0;i < 8;++i){
		vertices[i]-= center;
		vertices[i].rotate(axis,angle);
		vertices[i]+= center;
	}
    // Ebenen neu berechnen
	calculatePlanes();
	return *this;
}

/*
=================================================================================
=                                                                               =
=                                Bounding Sphere                                =
=                                                                               =
=================================================================================*/

/*
=================================================================================
Überprüft,ob Kugel sich AABB und Kugel schneiden
=================================================================================*/
bool AABB::intersects(const BoundingSphere &sphere) const
{
	for(size_t i = 0;i < 6;++i)
		if(planes[i].distance(sphere.getCenter()) < sphere.getRadius())
			return true;
	return false;
}

/*
=================================================================================
Konstruiert aus Mittelpunkt und Radius ein Bounding Sphere
=================================================================================*/
BoundingSphere::BoundingSphere(const Vector &center,float radius)
			  : center(center),radius(radius)
{}

/*
=================================================================================
Überprüft,ob Kugel sich zwei Kugeln schneiden
=================================================================================*/
bool BoundingSphere::intersects(const BoundingSphere &rhs) const
{
	return (center - rhs.center).length() < radius + rhs.radius;
}

/*
=================================================================================
Verschiebt Kugel
=================================================================================*/
BoundingSphere& BoundingSphere::translate(const Vector &v)
{
	center += v;
	return *this;
}

/*
=================================================================================
Gibt Mittelpunkt bzw. Radius der Kugel zurück
=================================================================================*/
float BoundingSphere::getRadius(void) const
{
	return radius;
}

const Vector& BoundingSphere::getCenter(void) const
{
	return center;
}

#ifdef __DEBUG__
void BoundingSphere::draw(void) const
{
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(center[X],center[Y],center[Z]);
        glScalef(radius,radius,radius);
        glColor3f(0.0f,0.0f,1.0f);
        glutWireSphere(1,50,50);
    glPopMatrix();
    glPopAttrib();
}
#endif

/*
=================================================================================
Erstellt das am engsten umgebende Bounding Volume
=================================================================================*/
OrientedBoundingVolume* CreateBoundingVolume(float width,float height,float depth,float radius);
OrientedBoundingVolume* CreateBoundingVolume(const float* vertices,size_t count);
