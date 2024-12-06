#ifndef MD2_H_INCLUDED
#define MD2_H_INCLUDED

#include <cmath>
#include <vector>
#include <algorithm>

#include "Sound.hpp"
#include "Config.hpp"
#include "BSP.hpp"
#include "ID_MD2.hpp"

#define MIN 0
#define MAX 1

int GetElapsedTime();

/**
 * @brief Angepasste Pfade
 */
std::string GetPath(void);
std::string GetPath(const std::string& name);

/*
================================================================================================
=                                                                                              =
=                                      MD2 Model                                               =
=                                                                                              =
================================================================================================*/
class MD2 {
public:
	struct Keyframe {
		float** vertices;
		char name[16];
	};
private:
	Keyframe* keyframes;
	unsigned int* indices;
	double** texture_coords;
	size_t keyframe_count;
	size_t vertex_count;
	size_t triangle_count;
	GLuint texture;
	anim_t* animations;
	size_t animation_count;
	//-----------------------
	double** current_vertices;
	size_t current_frame;
	size_t current_animation;
	size_t fps;
	bool started;
	bool repeat;
	bool draw_last;

public:
	MD2(void);
	MD2(const std::string filename);

	/**
	 * @brief Lädt Daten
	 */
	void load(const std::string filename);

private:

	/**
	 * @brief Zeichnet aktuellen Frame
	 */
	void render(double** const vertices) const;

	/**
	 * @brief Erstellt Animationsliste
	 *
	 */
	void createAnimationList(void);

	/**
	 * @brief  Interpoliert Frames
	 */
	void interpolate(double** vertices, size_t first, size_t second, float factor);

	/**
	 * @brief Rendert Frame der Animation
	 */
	void createFrame(size_t animation, size_t frame, float factor);

	/**
	 * @brief Legt den nächsten Frame fest
	 *
	 */
	void next(void);

public:
	void start(size_t animation, size_t fps, bool do_repeat);

	void animate(void);

	void normalize(void);
	bool isRunning(void) const;
	int GetCurrentAnimation(void) const;
	void stop(void);

};

typedef MD2 Animation;

/*
================================================================================================
=                                                                                              =
=                                    Waffensteuerung                                           =
=                                                                                              =
================================================================================================*/
Sound gun;
Sound music;

class Weapon {
private:
	enum { Putting, Shooting, Idle, PuttingAway };
	MD2 weapon;
	bool active;
	bool fight;

public:
	/**
	 * @brief Lädt MD2-Datei
	 *
	 */
	Weapon(void);
	Weapon(const std::string& file);
	void load(const std::string& file);

	/**
	 * @brief Spielt Animation ab
	 */
	void animate(void);

	/**
	 * @brief Setzt Animationen.
	 */
	void put(void);;
	void putaway(void);
	void startShooting(void);
	void stopShooting(void);
	void idle(void);
};

#endif
