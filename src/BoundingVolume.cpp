#include "Header.h"
#include "Plane.h"
#include "BoundingBox.h"
#include <vector>
//http://www.gamedev.net/topic/550461-aabb-plane-collision/

class Brush
{
    private:
        std::vector<Plane> planes;
        int contents;
    public:
        /*
        =====================================================================
        Konstruktoren
        =====================================================================*/
        Brush(void) : contents(0)
        {}

        Brush(const dbrush_t &brush,const dbrushside_t *brushsides,const dplane_t *planes) : contents(brush.contents)
        {
            size_t j;

            // (1) Reserviert Speicher für Ebenen
            Brush::planes.resize(brush.numsides);

            // (2) Liest Ebenen ein
            for(size_t i = 0;i < brush.numsides;++i)
            {
                j = brushsides[brush.firstside + i].planenum;
                Brush::planes[i] = Plane(planes[j].normal[X],planes[j].normal[Y],planes[j].normal[Z],planes[j].dist);
            }
        }

CONTENTS_SOLID








        bool isWithin(const Vector &P) const
        {
            for(size_t i = 0;i < planes.size();++i)
                if(planes[i].isFrontFacing(P))
                    return false;
            return true;
        }


        bool intersects(const AABB &rhs) const
        {}

        Plane& operator[](size_t i)
        {
            return planes[i];
        }

        const Plane& operator[](size_t i) const
        {
            return planes[i];
        }
};
















