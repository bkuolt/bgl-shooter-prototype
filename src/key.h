

namespace Key {

typedef int Key;

// Tastendefinitionen f�r das OpenGL Utility Toolkit und SDL
enum {
#ifdef GL_UTITLITY_TOOLKIT
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Plus  = '+',
	Minus = '-',
	Up    = 256 + GLUT_KEY_UP,
	Down  = GLUT_KEY_DOWN,
	Left  = GLUT_KEY_LEFT,
	Right = GLUT_KEY_RIGHT
#endif  // GL_UTITLITY_TOOLKIT
};

// Hilfsfunktions
#ifdef GL_UTITLITY_TOOLKIT
Key ConvertGLUTKey(int key) {
	if(key <= 255)
		return toupper(key);
	else
		return key + 256;
}
#endif

}  // namespace Key
