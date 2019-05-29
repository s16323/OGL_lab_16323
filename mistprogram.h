#ifndef MISTPROGRAM_H
#define MISTPROGRAM_H

#include <GL/glew.h>

#include "mist.h"

class MistProgram{
public:
    void SetMistType(GLuint mist_type);
    void SetMist(Mist mist);
protected:
    struct MistLocations {
        GLint color;
        GLint start;
        GLint end;
        GLint density;
        GLint type;
    } mist_locations_;
};

#endif // MISTPROGRAM_H
