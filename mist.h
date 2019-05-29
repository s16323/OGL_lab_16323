#ifndef MIST
#define MIST

#define MIST_LINEAR 0
#define MIST_EXP1 1
#define MIST_EXP2 2
#define MIST_NONE 3

#include <GL/gl.h>

typedef struct Mist{
  GLfloat color[4];
  GLfloat start;
  GLfloat end;
  GLfloat density;
} Mist;


#endif // MIST

