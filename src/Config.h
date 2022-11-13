#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>

enum Configuration {
  Width,
  Height,
  Windowed, // Fenstereinstellungen
  PlayAudio,
  DrawSkybox,
  AnimateSkybox,
  AnimateWater,
  DrawTextures,
  DrawWater, // optionale Render-Einstellungen
  TextureFormat,
  AnisotropicFilter,
  Gamma, // Texturoptionen
  DataPath,
  Level, // Datenoptionen
  Position,
  Rotation, // Kameraeinstellung
  RotationStep,
  MoveStep,
  MoveUpStep, // Steuerungseinstellungen
  // Aliase
  ResolutionX = Width,
  ResolutionY = Height
};

int GetConfigurationInt(enum Configuration configuration);
std::string GetConfigurationString(enum Configuration configuration);
float GetConfigurationFloat(enum Configuration configuration);
const float *GetConfigurationFloatv(enum Configuration configuration);
void LoadConfiguration(void);
#endif
