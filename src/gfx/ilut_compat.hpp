#ifndef ILUT_COMPAT_HPP_INCLUDED
#define ILUT_COMPAT_HPP_INCLUDED

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <algorithm>
#include <cctype>
#include <string>

extern "C" {

inline ILboolean ilutGLBuildMipmaps(void) {
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILubyte* data = ilGetData();

    if (!data || width <= 0 || height <= 0) {
        return IL_FALSE;
    }

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return IL_TRUE;
}

inline GLuint ilutGLBindTexImage(void) {
    GLuint TextureId = 0;
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    iluFlipImage();
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILubyte* data = ilGetData();

    if (data && width > 0 && height > 0) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    return TextureId;
}

inline GLuint ilutGLLoadImage(char* FileName) {
    ILuint ImageId;
    ilGenImages(1, &ImageId);
    ilBindImage(ImageId);

    if (!ilLoadImage(FileName)) {
        std::string lowerName = FileName;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (!ilLoadImage(const_cast<char*>(lowerName.c_str()))) {
            ilDeleteImages(1, &ImageId);
            return 0;
        }
    }

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    GLuint TextureId = ilutGLBindTexImage();
    ilDeleteImages(1, &ImageId);
    return TextureId;
}

} // extern "C"

#endif // ILUT_COMPAT_HPP_INCLUDED
