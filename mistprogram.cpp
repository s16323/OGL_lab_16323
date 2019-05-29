#include "mistprogram.h"


void MistProgram::SetMistType(GLuint mist_type){
    glUniform1i(mist_locations_.type, mist_type);
}

void MistProgram::SetMist(Mist mist){
    glUniform4fv(mist_locations_.color, 1, mist.color);
    glUniform1f(mist_locations_.start, mist.start);
    glUniform1f(mist_locations_.end, mist.end);
    glUniform1f(mist_locations_.density, mist.density);
}

