#include <GL/glew.h>
#include <string.h>

#include "cubetexture.h"


void CubeTexture::Initialize(const char *filename){

    GLenum target = 0;
    char * filename1;

    // nowy indeks tekstury
    glGenTextures(1, &texture_);

//    glActiveTexture(GL_TEXTURE1);
    // aktywizacja
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);

    // parametry interpolacji tekstury
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // parametry
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



    unsigned long int len=strlen(filename);

    filename1 = new char[len+6];

    strcpy(filename1,filename);
    char n='1';
    filename1[len+1]='.';
    filename1[len+2]='t';
    filename1[len+3]='g';
    filename1[len+4]='a';
    filename1[len+5]='\0';

    for(char i=0;i<6;i++){
        filename1[len]=n++;
      switch(i){
        case 0:
//            right;
            target=GL_TEXTURE_CUBE_MAP_POSITIVE_X;
        break;
        case 1:
//             back;
          target=GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
        break;
        case 2:
//            top;
          target=GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
        break;
        case 3:
//            left;
          target=GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
        break;
        case 4:
//            front;
          target=GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
        break;
        case 5:
//            bottom;
          target=GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
        break;
      }
      LoadTGAFileOrDie(target, filename1);
    }

    delete filename1;
}

