#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <string>

enum Configuration {
    ResolutionX,
    ResolutionY,
    Windowed,
    Textures,
    HDTextures,
    AF,
    Audio,
    SkyboxOpt,
    AnimateSkybox,
    AnimateWater,
    TextureFormat,
    DataPath,
    Level,
    RotationStep,
    MoveStep,
    MoveUpStep,
    Gamma,
    Rotation,
    Position,
    PlayAudio,
    DrawSkybox,
    DrawTextures,
    DrawWater,
    AnisotropicFilter
};

/**
 * @brief Reads configuration parameters
 */
int GetConfigurationInt(enum Configuration configuration);
std::string GetConfigurationString(enum Configuration configuration);
float GetConfigurationFloat(enum Configuration configuration);
const float* GetConfigurationFloatv(enum Configuration configuration);

/**
 * @brief Loads the INI configuration file
 */
void LoadConfiguration(void);

#endif // CONFIG_HPP_INCLUDED
