#include "Config.h"
#include "GLEE.h"
#include "GLUT.h"
#include "Windows.h"
#include <cstdio>
#include <string>


/*
==============================================================
Optionen
==============================================================*/
static int width;
static int height;
static int AF;
static float gamma;
static bool windowed;
static bool audio;
static bool skybox;
static bool textures;
static bool HD;
static bool animated;
static bool water;
static bool renderwater;
static float rotation;
static float translation;
static float up;
static float position[3];
static float angles[3];
static std::string data;
static std::string level;

/*
==============================================================
Gibt den Programmpfad zur�ck
==============================================================*/
static std::string GetProgrammPath(void) {
  const char *name = GetCommandLine();
  int length = strlen(GetCommandLine());

  while (name[length - 1] != '\\')
    --length;
  return std::string(name + 1, name + length);
}

static float GetPrivateProfileFloat(const char *lpAppName,
                                    const char *lpKeyName, float inDefault,
                                    const char *lpFileName) {
  char buffer[100];
  char _default[100];

  sprintf(_default, "%f", inDefault);
  GetPrivateProfileString(lpAppName, lpKeyName, _default, buffer, 100,
                          lpFileName);
  return atof(buffer);
}

/*
==============================================================
Funktionen zur Optionsabfrage
==============================================================*/
int GetConfigurationInt(enum Configuration configuration) {
  switch (configuration) {
  case Width:
    return (width == -1) ? glutGet(GLUT_SCREEN_WIDTH) : width;
  case Height:
    return (height == -1) ? glutGet(GLUT_SCREEN_HEIGHT) : height;
  case Windowed:
    return windowed;
  case PlayAudio:
    return audio;
  case DrawSkybox:
    return skybox;
  case AnimateSkybox:
    return animated;
  case AnimateWater:
    return water;
  case DrawTextures:
    return textures;
  case DrawWater:
    return renderwater;
  case AnisotropicFilter:
    return AF;
  }
}

std::string GetConfigurationString(enum Configuration configuration) {
  switch (configuration) {
  case TextureFormat:
    return (HD) ? ".tga" : ".wal";
  case DataPath:
    return (data == "local") ? GetProgrammPath() + "data\\" : data;
  case Level:
    return level + ".bsp";
  }
}

float GetConfigurationFloat(enum Configuration configuration) {
  switch (configuration) {
  case RotationStep:
    return rotation;
  case MoveStep:
    return translation;
  case MoveUpStep:
    return up;
  case Gamma:
    return gamma;
  }
}

const float *GetConfigurationFloatv(enum Configuration configuration) {
  switch (configuration) {
  case Rotation:
    return angles;
  case Position:
    return position;
  }
}

/*
==============================================================
L�dt INI-Datei
==============================================================*/
void LoadConfiguration(void) {
  std::string file = GetProgrammPath() + "configuration.ini";

  // Basiseinstellungen (alle int)
  windowed = GetPrivateProfileInt("BGL", "Windowed", 0, file.c_str());
  width = GetPrivateProfileInt("BGL", "ResolutionX", -1, file.c_str());
  height = GetPrivateProfileInt("BGL", "ResolutionY", -1, file.c_str());
  skybox = GetPrivateProfileInt("BGL", "Skybox", 1, file.c_str());
  animated = GetPrivateProfileInt("BGL", "AnimateSkybox", 1, file.c_str());
  water = GetPrivateProfileInt("BGL", "AnimateWater", 1, file.c_str());
  textures = GetPrivateProfileInt("BGL", "Textures", 1, file.c_str());
  HD = GetPrivateProfileInt("BGL", "HDTextures", 1, file.c_str());
  AF = GetPrivateProfileInt("BGL", "AF", 0, file.c_str());
  audio = GetPrivateProfileInt("BGL", "Audio", 1, file.c_str());
  renderwater = GetPrivateProfileInt("BGL", "Water", 1, file.c_str());

  // ErweiterteEinstellungen
  // alle float
  position[0] = GetPrivateProfileFloat("BGL", "PositionX", 1, file.c_str());
  position[1] = GetPrivateProfileFloat("BGL", "PositionY", 1, file.c_str());
  position[2] = GetPrivateProfileFloat("BGL", "PositionZ", 1, file.c_str());
  angles[0] = GetPrivateProfileFloat("BGL", "RotationX", 1, file.c_str());
  angles[1] = GetPrivateProfileFloat("BGL", "RotationY", 1, file.c_str());
  angles[2] = GetPrivateProfileFloat("BGL", "RotationZ", 1, file.c_str());
  translation = GetPrivateProfileFloat("BGL", "Translation", 1, file.c_str());
  rotation = GetPrivateProfileFloat("BGL", "Rotation", 1, file.c_str());
  up = GetPrivateProfileFloat("BGL", "Up", 1, file.c_str());
  gamma = GetPrivateProfileFloat("BGL", "Gamma", 1, file.c_str());

  // String
  char buffer[2][100];
  GetPrivateProfileString("BGL", "Level", "base2", buffer[0], 100,
                          file.c_str());
  GetPrivateProfileString("BGL", "DataFolder", "local", buffer[1], 100,
                          file.c_str());
  level = std::string(buffer[0]);
  data = std::string(buffer[1]);
}
