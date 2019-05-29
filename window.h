#ifndef WINDOW_H
#define WINDOW_H

#include <ctime>

#include "pointlightprogram.h"
#include "pointlightmistprogram.h"
#include "texture.h"
#include "matma.h"
#include "objmodel.h"
#include "skybox.h"
#include "cubetexture.h"
#include "texturecameraprogram.h"
#include "texturemistcameraprogram.h"
#include "objmodel.h"
#include "camera.h"
#include "starprogram.h"
#include "star.h"
//#include "cone.h"
#include "pointlighttransparentprogram.h"

class Window{
 public:
    Window(const char*, int, int);
    void Initialize(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void Resize(int new_width, int new_height);
    void Render(void);
    void KeyPressed(unsigned char key, int x_coord, int y_coord);
    void SpecialKeyPressed(int key, int x_coord, int y_coord);
    void MouseButton(int button, int state, int x_coord, int y_coord);
    void MouseMove(int x_coord, int y_coord);
 private:
    int width_;
    int height_;
    const char* title_;

//    PointLightProgram point_program_; //--
	PointLightMistProgram point_program_; //++
	TextureMistCameraProgram sky_program_; //++
	TransparentMaterialModelProgram transparent_program_;
	
//-------------------------------------------------
	Texture brzeg2_texture_;
	Texture latarnia_texture_;
	Texture morze_texture_;
	Texture star_texture_;
	
	ObjModel brzeg2_;
	ObjModel latarnia_;
	ObjModel morze_;
//-------------------------------------------------
	Star star_;
	StarProgram star_program_;
//-------------------------------------------------
	SkyBox sky_;
	CubeTexture sky_texture_;
	//TextureCameraProgram sky_program_; //--
	

    int x_origin_;
    int y_origin_;

    clock_t last_time_;
    
    //Mat4 projection_matrix_;
    
    Camera camera_;
	Mat4 view_matrix_;


    void InitGlutOrDie(int argc, char* argv[], int major_gl_version, int minor_gl_version);
    void InitGlewOrDie();
    void InitTextures();
    void InitModels();
    void InitPrograms();

    void SetViewMatrix();
    void SetProjectionMatrix();

};


#endif // WINDOW_H

