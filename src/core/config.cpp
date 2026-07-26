#include "config.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>

/*
==============================================================
Options
==============================================================*/
static int width;
static int height;
static int af_val;
static float gamma_val;
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

static std::map<std::string, std::map<std::string, std::string>> ini_data;

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

static void parse_ini(const std::string& filename) {
    ini_data.clear();
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string current_section;
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        if (line.front() == '[' && line.back() == ']') {
            current_section = trim(line.substr(1, line.size() - 2));
        } else {
            size_t delim_pos = line.find('=');
            if (delim_pos != std::string::npos) {
                std::string key = trim(line.substr(0, delim_pos));
                std::string val = trim(line.substr(delim_pos + 1));
                ini_data[current_section][key] = val;
            }
        }
    }
}

static int GetIniInt(const char* section, const char* key, int default_val) {
    auto sec_it = ini_data.find(section);
    if (sec_it != ini_data.end()) {
        auto key_it = sec_it->second.find(key);
        if (key_it != sec_it->second.end()) {
            return std::atoi(key_it->second.c_str());
        }
    }
    return default_val;
}

static float GetIniFloat(const char* section, const char* key, float default_val) {
    auto sec_it = ini_data.find(section);
    if (sec_it != ini_data.end()) {
        auto key_it = sec_it->second.find(key);
        if (key_it != sec_it->second.end()) {
            return std::atof(key_it->second.c_str());
        }
    }
    return default_val;
}

static std::string GetIniString(const char* section, const char* key, const char* default_val) {
    auto sec_it = ini_data.find(section);
    if (sec_it != ini_data.end()) {
        auto key_it = sec_it->second.find(key);
        if (key_it != sec_it->second.end()) {
            return key_it->second;
        }
    }
    return default_val;
}

static std::string GetProgrammPath(void) {
    return "./";
}

int GetConfigurationInt(enum Configuration configuration) {
    switch (configuration) {
    case ResolutionX:
        return (width == -1) ? glutGet(GLUT_SCREEN_WIDTH) : width;
    case ResolutionY:
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
        return af_val;
    default:
        return 0;
    }
}

std::string GetConfigurationString(enum Configuration configuration) {
    switch (configuration) {
    case TextureFormat:
        return (HD) ? ".tga" : ".wal";
    case DataPath:
        return (data == "local") ? GetProgrammPath() + "data/" : data;
    case Level:
        return level + ".bsp";
    default:
        return "";
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
        return gamma_val;
    default:
        return 0.0f;
    }
}

const float* GetConfigurationFloatv(enum Configuration configuration) {
    switch (configuration) {
    case Rotation:
        return angles;
    case Position:
        return position;
    default:
        return position;
    }
}

void LoadConfiguration(void) {
    std::string file = GetProgrammPath() + "configuration.ini";
    parse_ini(file);

    windowed = GetIniInt("BGL", "Windowed", 0);
    width = GetIniInt("BGL", "ResolutionX", -1);
    height = GetIniInt("BGL", "ResolutionY", -1);
    skybox = GetIniInt("BGL", "Skybox", 1);
    animated = GetIniInt("BGL", "AnimateSkybox", 1);
    water = GetIniInt("BGL", "AnimateWater", 1);
    textures = GetIniInt("BGL", "Textures", 1);
    HD = GetIniInt("BGL", "HDTextures", 1);
    af_val = GetIniInt("BGL", "AF", 0);
    audio = GetIniInt("BGL", "Audio", 1);
    renderwater = GetIniInt("BGL", "Water", 1);

    position[0] = GetIniFloat("BGL", "PositionX", 1.0f);
    position[1] = GetIniFloat("BGL", "PositionY", 1.0f);
    position[2] = GetIniFloat("BGL", "PositionZ", 1.0f);
    angles[0] = GetIniFloat("BGL", "RotationX", 1.0f);
    angles[1] = GetIniFloat("BGL", "RotationY", 1.0f);
    angles[2] = GetIniFloat("BGL", "RotationZ", 1.0f);
    translation = GetIniFloat("BGL", "Translation", 1.0f);
    rotation = GetIniFloat("BGL", "Rotation", 1.0f);
    up = GetIniFloat("BGL", "Up", 1.0f);
    gamma_val = GetIniFloat("BGL", "Gamma", 1.0f);

    level = GetIniString("BGL", "Level", "base2");
    data = GetIniString("BGL", "DataFolder", "local");
}
