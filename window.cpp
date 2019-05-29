#include "window.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cstring>

#include "glerror.h"
#include "material.h"
#include "light.h"
#include "camera.h"


const char* kStarVertexShader="Sprite.vertex.glsl";
const char* kStarFragmentShader="Sprite.fragment.glsl";

//const char* kPointLightVertexShader="PointLight.vertex.glsl";
const char* kPointLightVertexShader="PointLightMist.vertex.glsl";

//const char* kPointLightFragmentShader="PointLight.fragment.glsl";
const char* kPointLightFragmentShader="PointLightMist.fragment.glsl";

static const char* kTransparentVertexShader="TransparentMaterial.vertex.glsl"; // +lab_06
static const char* kTransparentFragmentShader="TransparentMaterial.fragment.glsl"; // +lab_06

//-----------------------------------------------------------
static const char* kSkyBoxVertexShader="SkyBox.vertex.glsl";
//static const char* kSkyBoxFragmentShader="SkyBox.fragment.glsl";
const char* kSkyBoxFragmentShader="SkyBoxMist.fragment.glsl";
static const char* kSkyTextureFile="skyboxsun25degtest/skyrender000"; // x.tga
//-----------------------------------------------------------


//const char* kCubeTextureFile="kostka.tga";
//const char* kCubeMtlFile="kostka.mtl";
//const char* kCubeObjFile="kostka.obj";

//----------------------------------------------------------
const char* kBrzeg2TextureFile="skyboxsun25degtest/brzeg2.tga";
const char* kBrzeg2MtlFile="skyboxsun25degtest/brzeg2.mtl";
const char* kBrzeg2ObjFile="skyboxsun25degtest/brzeg2.obj";

const char* kLatarniaTextureFile="skyboxsun25degtest/latarnia.tga";
const char* kLatarniaMtlFile="skyboxsun25degtest/latarnia.mtl";
const char* kLatarniaObjFile="skyboxsun25degtest/latarnia.obj";

const char* kMorzeTextureFile="skyboxsun25degtest/morzenie.tga";
const char* kMorzeMtlFile="skyboxsun25degtest/morzenie.mtl";
const char* kMorzeObjFile="skyboxsun25degtest/morzenie.obj";

//-----------------------------------------------------------
const char* kMistTextureFile="ice.tga";

static const char* kStarTextureFile = "star1.tga";

const PointLight kPointLight={
    {2.0f, -3.5f, 1.0f, 1.0f},//{0.0f, 1.5f, 4.0f, 1.0f}, //position
    {0.5f, 0.5f, 0.1f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f}, //specular
    {0.5f, 0.0005f, 0.00525f} //{0.5f, 0.005f, 0.0125f}	//attenuation
};

const PointLight kPointLight2={
    {4.0f, -5.5f, 3.0f, 1.0f},//{0.0f, 1.5f, 4.0f, 1.0f}, //position
    {0.5f, 0.5f, 0.1f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f}, //specular
    {0.5f, 0.0005f, 0.00525f} //{0.5f, 0.005f, 0.0125f}	//attenuation
};

const PointLight kPointLight3={
    {9.9f, 8.5f, 1.0f, 1.0f},//{0.0f, 1.5f, 4.0f, 1.0f}, //position
    {0.5f, 0.5f, 0.1f, 1.0f}, //ambient
    {1.0f, 1.0f, 1.0f, 1.0f}, //diffuse
    {1.0f, 1.0f, 1.0f, 1.0f}, //specular
    {0.5f, 0.0005f, 0.00525f} //{0.5f, 0.005f, 0.0125f}	//attenuation
};

const Mist kMist = {
0.8f, 0.8f, 0.7f, 1.0f, //color
1.0f, //start
45.0f, //end
3.0f //density
};



const TransparentMaterial kConeMaterial={
    {0.8f, 0.8f, 0.7f, 1.025f} 

};



Window::Window(const char * title, int width, int height){
    title_ = title;
    width_ = width;
    height_ = height;
    last_time_ = 0;
    x_origin_ = y_origin_ = -1;
}

void Window::Initialize(int argc, char * argv[], int major_gl_version, int minor_gl_version){

    InitGlutOrDie(argc, argv, major_gl_version, minor_gl_version);
    InitGlewOrDie();

    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    InitTextures();

    InitModels();

    InitPrograms();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);

}

void Window::InitGlutOrDie(int argc, char * argv[], int major_gl_version, int minor_gl_version){
    glutInit(&argc, argv);

    glutInitContextVersion(major_gl_version, minor_gl_version);
    glutInitContextProfile(GLUT_CORE_PROFILE);
#ifdef DEBUG
    glutInitContextFlags(GLUT_DEBUG);
#endif

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(width_, height_);

    glutInitDisplayMode(GLUT_DEPTH| GLUT_DOUBLE | GLUT_RGBA);

    int window_handle = glutCreateWindow(title_);

    if( window_handle < 1) {
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
        exit(EXIT_FAILURE);
    }


}

void Window::InitGlewOrDie(){
    GLenum glew_init_result;
    glewExperimental = GL_TRUE;
    glew_init_result = glewInit();

    if (GLEW_OK != glew_init_result) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    if(glDebugMessageCallback){
        std::cout << "Register OpenGL debug callback " << std::endl;
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROC) OpenglCallbackFunction, NULL);
        GLuint unused_ids = 0;
        glDebugMessageControl(GL_DONT_CARE,
            GL_DONT_CARE,
            GL_DONT_CARE,
            0,
            &unused_ids,
            GL_FALSE);
    }
    else
        std::cout << "glDebugMessageCallback not available" << std::endl;
#endif

}

void Window::InitModels(){
//    cube_.Initialize(kCubeObjFile, kCubeMtlFile);
//   cube_.SetTexture(cube_texture_);
//    cube_.SetTextureUnit(GL_TEXTURE0);
    
//----------------------------------------------------------       
    brzeg2_.Initialize(kBrzeg2ObjFile, kBrzeg2MtlFile);
    brzeg2_.SetTexture(brzeg2_texture_);
    brzeg2_.SetTextureUnit(GL_TEXTURE0);
    
    latarnia_.Initialize(kLatarniaObjFile, kLatarniaMtlFile);
    latarnia_.SetTexture(latarnia_texture_);
    latarnia_.SetTextureUnit(GL_TEXTURE0);
    
    morze_.Initialize(kMorzeObjFile, kMorzeMtlFile);
    morze_.SetTexture(morze_texture_);
    morze_.SetTextureUnit(GL_TEXTURE0);
    
    sky_.Initialize();
    sky_.SetTexture(sky_texture_);
    sky_.SetTextureUnit(GL_TEXTURE1);
    
//    cone_.Initialize(); //+lab_06
//    cone_.SetMaterial(kConeMaterial);
    
    
    star_.Initialize();
    star_.SetMaterial(kConeMaterial);
    star_.SetTexture(star_texture_);
    star_.SetTextureUnit(GL_TEXTURE0);
//----------------------------------------------------------
}

void Window::InitTextures(){
//    cube_texture_.Initialize(kCubeTextureFile);
//----------------------------------------------------------
	brzeg2_texture_.Initialize(kBrzeg2TextureFile);
	latarnia_texture_.Initialize(kLatarniaTextureFile);
	morze_texture_.Initialize(kMorzeTextureFile);
	sky_texture_.Initialize(kSkyTextureFile);
	star_texture_.Initialize(kStarTextureFile);
	
//----------------------------------------------------------
}

void Window::InitPrograms(){
    
    //projection_matrix_ = Mat4::CreateProjectionMatrix(20 , (float)width_/(float)height_, 0.1f, 100.0f);
    
    
    point_program_.Initialize(kPointLightVertexShader, kPointLightFragmentShader);
    glUseProgram(point_program_);
    point_program_.SetLight(kPointLight);
    point_program_.SetMistType(MIST_LINEAR); //++ mist
    point_program_.SetMist(kMist); //++ mist
    point_program_.SetTextureUnit(0);
    
    sky_program_.Initialize(kSkyBoxVertexShader, kSkyBoxFragmentShader);
    glUseProgram(sky_program_);
    sky_program_.SetTextureUnit(1);
    sky_program_.SetMist(kMist); //++ mist
    sky_program_.SetMistType(MIST_LINEAR); //++mist
    
    
    //-------------------------------------------------------
	 // transparent
    //transparent_program_.Initialize(kPointLightMaterialVertexShader, kPointLightMaterialFragmentShader);
    transparent_program_.Initialize(kTransparentVertexShader, kTransparentFragmentShader);
    glUseProgram(transparent_program_);
    //transparent_program_.SetLight(kPointLight);
   //transparent_program_.SetProjectionMatrix(projection_matrix_);
    //transparent_program_.SetViewMatrix(view_matrix_);
    
    star_program_.Initialize(kStarVertexShader, kStarFragmentShader);
    glUseProgram(star_program_);
    star_program_.SetTextureUnit(0);
    
    
    SetProjectionMatrix();
    SetViewMatrix();
    
    glUseProgram(0);
}

void Window::Resize(int new_width, int new_height){
    width_ = new_width;
    height_ = new_height;
    //projection_matrix_ = Mat4::CreateProjectionMatrix(60,(float)width_/(float)height_, 0.1f, 100.0f);
    //projection_matrix_ = Mat4::CreateProjectionMatrix(60, 
	//												static_cast<GLfloat>(width_)/
	//												static_cast<GLfloat>(height_), 0.1f, 100.0f);
    SetProjectionMatrix();
    glViewport(0, 0, width_, height_);
    glutPostRedisplay();
}

void Window::KeyPressed(unsigned char key, int /*x_coord*/, int /*y_coord*/){
    switch (key){
    case 27:
      glutLeaveMainLoop();
    break;
    default:
    break;
    }
}

void Window::SpecialKeyPressed(int key, int /*x_coord*/, int /*y_coord*/){
    switch (key){
    case GLUT_KEY_LEFT:
    break;
    default:
    break;
    }
}

void Window::SetViewMatrix(){
    glUseProgram(point_program_);
    point_program_.SetViewMatrix(camera_);
    glUseProgram(sky_program_); //++
    sky_program_.SetViewMatrix(camera_); //++
    glUseProgram(transparent_program_);
    transparent_program_.SetViewMatrix(camera_);
    glUseProgram(star_program_);
    star_program_.SetViewMatrix(camera_);
    
    glUseProgram(0);
}

void Window::SetProjectionMatrix(){
	Mat4 projection_matrix = Mat4::CreateProjectionMatrix(60, 
										static_cast<GLfloat>(width_)
										/static_cast<GLfloat>(height_), 0.1f, 100.0f);
    glUseProgram(point_program_);
    point_program_.SetProjectionMatrix(projection_matrix);
    glUseProgram(sky_program_); //++
    sky_program_.SetProjectionMatrix(projection_matrix); //++
    glUseProgram(transparent_program_);
    transparent_program_.SetProjectionMatrix(projection_matrix);
    glUseProgram(star_program_);
    star_program_.SetProjectionMatrix(projection_matrix);
    
    glUseProgram(0);
}


void Window::MouseMove(int x_coord, int y_coord){	// this will only be true when the left button is down
    float delta_x_angle=0;
    float delta_y_angle=0;
    if (x_origin_ >= 0 && y_origin_ >=0) {
        // update deltaAngle
        delta_x_angle = (x_coord - x_origin_) * 0.1f;
        delta_y_angle = (y_coord - y_origin_) * 0.1f;
        x_origin_=x_coord;
        y_origin_=y_coord;

        // update camera's direction
        camera_.RotateAboutY(delta_x_angle);
        camera_.RotateAboutX(delta_y_angle);
        SetViewMatrix();
        glutPostRedisplay();
   }
}


#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif

//void Window::MouseButton(int button, int state, int x_coord, int y_coord)
void Window::MouseButton(int button, int state, int x_coord, int y_coord) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
          // when the button is released
          if (state == GLUT_UP) {
              x_origin_ = -1;
              y_origin_ = -1;
          }
          else  {// state = GLUT_DOWN
              x_origin_ = x_coord;
              y_origin_ = y_coord;
          }
    }
    else if ( button == GLUT_WHEEL_UP ){
        camera_.Translate(0,0,-0.1f);
        SetViewMatrix();
        glutPostRedisplay();
    }
    else if( button == GLUT_WHEEL_DOWN ){
        camera_.Translate(0,0,0.1f);
        SetViewMatrix();
        glutPostRedisplay();
    }
}



void Window::Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    clock_t now = clock();
    if (last_time_ == 0) last_time_ = now;
    last_time_ = now;

//   cube_.Draw(point_program_);
   
//----------------------------------------------------------
	brzeg2_.Draw(point_program_);
	latarnia_.Draw(point_program_);
	morze_.Draw(point_program_);
	sky_.Draw(sky_program_);
//----------------------------------------------------------
//	cone_.Draw(transparent_program_);
	
	star_.Draw(star_program_);
	
    glutSwapBuffers();
    glutPostRedisplay();
}


