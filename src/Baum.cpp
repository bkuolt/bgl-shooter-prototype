#include "BSP.h"
#include "Brush.h"
#include <set>
#include <vector>
#include <bitset>

extern ::Camera camera;
extern std::vector<std::vector<int32_t> > cluster_leafs;
extern GLuint lists;
extern AABB *aabbs;

namespace CD {

// Vorwärtsdeklaration
std::vector<bool> DecompressPVS(const char* data,size_t num_clusters);
struct Cluster;

std::vector<Cluster> clusters;  // alle Cluster


/**
 * @brief Clusterstruktur
 */
struct Cluster {
    uint32_t id;
    std::vector<bool>     visible_clusters;
    std::vector<uint32_t> containing_faces;
    GLuint list;

    Cluster() {
        list = 0;
    }

    /**
     * @brief Zählt die von diesem Cluster sichtbaren Cluster
     */
    size_t getVisibleClustersCount(void) const {
        size_t count = 0;

        for (size_t i = 0; i < visible_clusters.size(); ++i) {
            if (visible_clusters[i]) {
                ++count;
            }
        }
        return count;
    }

    /**
     * @brief Zeichnet diesen Cluster
     */
    void draw(void) {
        if (list == 0) {
            list = glGenLists(1);
            glNewList(list, GL_COMPILE);
                for (size_t i = 0; i < containing_faces.size(); ++i) {
                    RenderFace(containing_faces[i]);
                }
            glEndList();
        }
        else
            glCallList(list);
    }

    /**
     * @brief Zeichnet alle von diesem aus sichtbaren Cluster
     */
    void drawVisibleClusters(void) const {
        for (size_t i = 0; i < vis->numclusters; ++i) {
            if (visible_clusters[i]) {
                clusters[i].draw();
            }
        }
    }

    /**
     * @brief Sucht alle Polygone,die sich in diesem Cluster befinden
     */
    void findContainingFaces(void) {
        size_t k;  // Polygonindex

        for (size_t i = 0; i < leafs.size(); ++i) {
            if (leafs[i].cluster == id) {
                for (size_t j = 0; j < leafs[i].numleaffaces; ++j) {
                    k = leafs[i].firstleafface + j;
                    containing_faces.push_back(leaf_face[k]);
                }
            }
    }
};

/**
 * @brief Erstellt Alle Cluster
 */
void CreateClusters(dvis_t *vis) {
    printf("\tErstellt Cluster...\n");

    // (1) Reserviert Speicher
    clusters.resize(vis->numclusters);

    // (2) erstellt Cluster
    for (size_t i = 0; i < vis->numclusters; ++i) {
        clusters[i].id = i;
        clusters[i].visible_clusters.resize(vis->numclusters);
        clusters[i].findContainingFaces();
    }

    // (3) VIS dekomprimieren und zuweisen
    printf("\tDekomprimiert PVSs...\n");
    char *data = reinterpret_cast<char*>(vis);

    for (size_t i = 0; i < vis->numclusters; ++i) {
		clusters[i].visible_clusters = DecompressPVS(data + vis->bitofs[i][0], vis->numclusters);
    }
}

/**
 * @brief Dekomprimiert ein PVS
 */
std::vector<bool> DecompressPVS(const char* data, size_t num_clusters) {
	std::vector<bool> pvs;

	// (1) reserviert Speicher
	pvs.resize(num_clusters, false);

	// (2) Dekomprimiert Daten
	for (size_t c = 0, b = 0; c < num_clusters; b++) {
		if(data[b] == 0) {
		    b++;
			c += data[b] * 8;
		} else {
			// Liest Byte in Bitset
			std::bitset<8> byte(data[b]);

			// Liest alle Bits
			for (size_t i = 0; i < 8; ++i) {
				pvs[c + i] = byte[i];
            }
			c+= 8;
		}
	}

	// (3) gibt Daten zurück
	return pvs;
}

/*
===============================================================================================================
=                                       Schnittstelle                                                         =
===============================================================================================================*/
static int current_node;
static int current_leaf;
static int current_cluster;

/**
 * @brief Überprüft, ob Punkt vor Ebene Liegt
 */
bool IsFrontFacing(size_t plane, vec3_t v) {
    size_t i = plane;
    return (planes[i].normal[X] * v[X] +
            planes[i].normal[Y] * v[Y] +
            planes[i].normal[Z] * v[Z] - planes[i].dist) >= 0;
}

/**
 * @brief Sucht Knoten und Blatt
 */
std::pair<int32_t, int32_t> FindNodeLeaf(vec3_t v) {
    int child =  0;
    int node  =  0;

    while (child >= 0) {
        node = child;

        // Geht in Kindsknoten
        if (IsFrontFacing(nodes[node].planenum, v)) {
            child = nodes[node].children[0];
        } else {
            child = nodes[node].children[1];
        }
    }

    // Gibt Knoten und Blatt zurück
    return std::make_pair(node, -child - 1);
}

static std::pair<int32_t, int32_t> FindNodeLeaf(void) {
    vec3_t v = {camera.getPosition()[X],
                camera.getPosition()[Y],
                camera.getPosition()[Z]};
    return FindNodeLeaf(v);
}

static void UpdateTreeInformation(void) {
    std::pair<int32_t, int32_t> pair = FindNodeLeaf();

    current_node = pair.first;
    current_leaf = pair.second;
    current_cluster = leafs[current_leaf].cluster;
}

/*
===============================================================================================================*/

const char* GetVisibiltyString(void) {
    int32_t node      = current_node;
    int32_t leaf      = current_leaf;
    int32_t cluster   = current_cluster;
    int32_t count     = (cluster == -1) ? vis->numclusters : clusters[cluster].getVisibleClustersCount();
    float position[3] = {camera.getPosition()[X], camera.getPosition()[Y], camera.getPosition()[Z]};
    static char buffer[100];

    // Formatiert String
    sprintf(buffer, "Position(%4i|%4i|%4i), Node: %4i, Leaf: %4i, Cluster %4i, Visible Clusters: %4i",
            (int) position[X], (int) position[Y], (int) position[Z],
            node, leaf, cluster, count);
    return buffer;
}

/**
 * @brief Zeichnet alle sichtbaren Cluster (Kernstück) 
 */
void RenderVisibleClusters(void){
    int c;

    UpdateTreeInformation();
    c = current_cluster;

    // zeichnet alle Sichtbaren Cluster
    if (c == -1) {
        ::RenderAllClusters();
    } else {
        // clusters[c].drawVisibleClusters();
        if (clusters[c].getVisibleClustersCount() > 0) {
            for (size_t i = 0; i < clusters[c].visible_clusters.size(); ++i)
                if (clusters[c].visible_clusters[i]) {
                    RenderCluster(i);
                }
        } else {
            ::RenderAllClusters(); // Work-Around: bei sehr,sehr wenigen Clustern betr�gt die Sichtbarkeit 0!?
        }
    }

    RenderVisibleModels();
    // Zeichnet Kamera Sphere
    // camera.sphere.draw();
}

/*
==================================================================================================================
=                                                                                                                =
=                                               Kollisionserkennung                                              =
=                                                                                                                =
==================================================================================================================*/

/**
 * @brief Gibt Index auf richtigen Brush zur�ck
 */
inline unsigned short GetLeafBrush(unsigned int leaf, unsigned short i) {
    return leaf_brushes[leafs[leaf].firstleafbrush + i];
}

static bool collision = false;
static int checked_brushes = 0;
static int checked_planes  = 0;
static int check_time = 0;

const char* GetCollisionDetetctionString(void) {
    static char buffer[100];
    char auxbuffer[100];

    if (detect_collisions) {
        // Basisinformation
        sprintf(auxbuffer, "Checked Solid Brushes: %4i, Checked Planes: %4i, Solid Brush Collision: %s",
                checked_brushes, checked_planes, (collision) ? "Yes" : "No");
        // Konkrete Kollsionsinformation
        if (collision) {
            sprintf(buffer, "%s", auxbuffer);
        } else {
            strcpy(buffer, auxbuffer);
        }
    } else {
        sprintf(buffer,"Collision Detection disabled");
    }
    return buffer;
}

/**
 * @brief Überprüft,ob es eine Kollision der Kaerma-AABB mit einer der Brushes im Level gibt
 */
bool HasBrushCollsion(void) {
    int start = GetElapsedTime();
    int leaf = FindNodeLeaf().second;
    dplane_t *planes         = &::planes.front();
    dbrushside_t *brushsides = &::brush_sides.front();
    bool result;

    // Statistik
    checked_brushes = 0;
    checked_planes  = 0;

    for (size_t i = 1; i < brushes.size(); ++i) {
        checked_planes+= brushes[i].numsides;
        if (Brush(brushes[i], brushsides, planes).intersects(camera.sphere)) {
            checked_brushes = i;
            return collision = true;
        }
    }

    checked_brushes = brushes.size();
    return collision = false;
}

/**
 * @brief Überprüft,ob Kamera-AABB die W�nde des Levels schneiden schneiden
 */
static bool HasWallCollision(void) {
    // (2) Grobe Überprüfung
    return HasBrushCollsion();  // c == -1;
}

/**
 * @brief Kernstück der Wandkollisonserkennung:
          Überprüft, ob Kamera-AABB die W�nde des Levels schneiden schneiden W�RDEN,wenn die
          Kamera um den angegeben Vektor verschoben werden w�rde.
 */
bool WouldHaveWallCollision(const Vector &v) {
    bool result;
    if (!detect_collisions) return false;

    // Grobe Überprüfung
    camera.position += v;
    camera.sphere.translate(v);
    result = HasWallCollision();
    camera.position -= v;
    camera.sphere.translate(v * -1);
    return result;
}

// TODO: Steigung und Gravitation!

}
