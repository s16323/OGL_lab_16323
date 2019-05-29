#ifndef ARRAYMODEL_H
#define ARRAYMODEL_H

#include <GL/glew.h>

class ArrayModel{
public:
    ~ArrayModel();
protected:
    GLuint vao_;
    GLuint vertex_buffer_;
};


#endif // ARRAYMODEL_H
