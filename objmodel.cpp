#include "objmodel.h"
#include "vertices.h"


#include <cstdlib>
#include <cstring>
//#include <cstdio>

#include <fstream>
#include <iostream>

using namespace std;

typedef GLfloat Vec2[2];
typedef GLfloat Vec3[3];


ObjModel::~ObjModel(){
    DestroyGroups();
    DestroyMaterials();
}

void ObjModel::Initialize(const char *obj_file, const char *mtl_file){

    n_of_materials_=LoadMaterials(mtl_file);
    n_of_groups_=LoadGroups(obj_file);


}


void ObjModel::DestroyGroup(VertexGroup gr){
    glDeleteBuffers(1, &gr.vao);
    glDeleteBuffers(1, &gr.vertices);
}

void ObjModel::DestroyGroups(void){
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  int i;
  for (i=0;i< n_of_groups_; i++){
    DestroyGroup(groups_[i]);
  }
  free(groups_);
  n_of_groups_=0;
}

void ObjModel::DestroyMaterials(void)
{
  free(materials_);
  n_of_materials_=0;
}

void ObjModel::Draw(const LightProgram &prog){

  model_matrix_.SetUnitMatrix();
  model_matrix_.RotateAboutX(0);
  model_matrix_.RotateAboutY(0);

  normal_matrix_.SetUnitMatrix();
  normal_matrix_.RotateAboutY(0);
  normal_matrix_.RotateAboutX(0);


  glUseProgram(prog);
  prog.SetModelMatrix(model_matrix_);
  prog.SetNormalMatrix(normal_matrix_);


//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
//  glFrontFace(GL_CCW);

  glActiveTexture(texture_unit_);
  glBindTexture(GL_TEXTURE_2D, texture_);

  for (int i=0; i<n_of_groups_; i++){

      glBindVertexArray(groups_[i].vao);
      prog.SetMaterial(materials_[groups_[i].mat_number].m);

      glDrawArrays(GL_TRIANGLES, 0, groups_[i].n_of_vertices);

      glBindVertexArray(0);
 }


//  glDisable(GL_CULL_FACE);

  glUseProgram(0);
}

int ObjModel::LoadGroups(const char * filename){
  int n_of=-1; // Groups
  int max=2;
  int delta=2;
  int mat_number=-1;
  int n_of_vert=-1; //vertices
  int max_vert=2;
  int d_vert=2;
  int n_of_vert_in_gr=-1; // vertices in group
  int max_v_in_g=6;
  int d_v_in_g=6; // >=3
  int n_of_tex=-1; // Texture
  int max_tex=2;
  int d_tex=2;
  int n_of_norm=-1; // normals
  int max_norm=2;
  int d_norm=2;
  char mode[10];
  char g;//slash
  char mat_name[30];
  int i;
  VertexGroup * new_groups;
  Vec3 * vertices;
  NormalTextureVertex * vertices_in_gr;
  Vec2 * tex_coords;
  Vec3 * normals;
  Vec3 * new_vertices;
  NormalTextureVertex * new_vertices_in_gr;
  Vec2 * new_tex_coords;
  Vec3 * new_normals;

  int v,t,n;//vertex data

  ifstream file (filename, ios::in|ios::binary);

  if (file.is_open()) {
    groups_ = (VertexGroup*) malloc(max*sizeof(VertexGroup));
    vertices = (Vec3*) malloc(max_vert*sizeof(Vec3));
    vertices_in_gr = (NormalTextureVertex*) malloc(max_v_in_g*sizeof(NormalTextureVertex));
    tex_coords = (Vec2*) malloc(max_tex*sizeof(Vec2));
    normals = (Vec3*) malloc(max_norm*sizeof(Vec3));

    while (file>>mode) {
        if(strcmp("v",(const char*)mode)==0){
            //Vertex
            n_of_vert++;
            if(n_of_vert>=max_vert){
              max_vert+=d_vert;
              new_vertices = (Vec3*) realloc(vertices,max_vert*sizeof(Vec3));
              if(NULL!=new_vertices) vertices=new_vertices;
              else {
                cerr<< "ERROR: Could not allocate memory for vertices\n";
                exit(EXIT_FAILURE);
              }
            }
            file >> vertices[n_of_vert][0]>> vertices[n_of_vert][1]>> vertices[n_of_vert][2];
        }
        else if(strcmp("vn",(const char*)mode)==0){
            //Normal
            n_of_norm++;
            if(n_of_norm>=max_norm){
              max_norm+=d_norm;
              new_normals =  (Vec3*) realloc(normals,max_norm*sizeof(Vec3));
              if(NULL!=new_normals) normals=new_normals;
              else {
                cerr<< "ERROR: Could not allocate memory for normals\n";
                exit(EXIT_FAILURE);
              }
            }
            file>> normals[n_of_norm][0]>> normals[n_of_norm][1]>> normals[n_of_norm][2];
        }
        else if(strcmp("vt",(const char*)mode)==0){
            //Texture
            n_of_tex++;
            if(n_of_tex>=max_tex){
              max_tex+=d_tex;
              new_tex_coords =  (Vec2*) realloc(tex_coords,max_tex*sizeof(Vec2));
              if(NULL!=new_tex_coords) tex_coords=new_tex_coords;
              else {
                cerr<< "ERROR: Could not allocate memory for texture coordinates\n";
                exit(EXIT_FAILURE);
              }
            }
            file>> tex_coords[n_of_tex][0]>> tex_coords[n_of_tex][1];
//            qDebug()<<tex_coords[n_of_tex][0]<<'\t'<<tex_coords[n_of_tex][1];
        }
        else if(strcmp("f",(const char*)mode)==0){
            //Face
            if(n_of_vert_in_gr+3>=max_v_in_g){
              max_v_in_g+=d_v_in_g;
              new_vertices_in_gr = (NormalTextureVertex*) realloc(vertices_in_gr,max_v_in_g*sizeof(NormalTextureVertex));
              if(NULL!=new_vertices_in_gr) vertices_in_gr=new_vertices_in_gr;
              else {
                cerr << "ERROR: Could not allocate memory for new vertices\n";
                exit(EXIT_FAILURE);
              }
            }
            for(i=0;i<3;i++){
              // three vertices
              file >> v>>g>> t>>g>>n;
              n_of_vert_in_gr++;
              cpf(vertices[v-1],vertices_in_gr[n_of_vert_in_gr].position,4);
              cpf(tex_coords[t-1],vertices_in_gr[n_of_vert_in_gr].texture,2);
              cpf(normals[n-1],vertices_in_gr[n_of_vert_in_gr].normal,3);
            }
        }
        else if(strcmp("usemtl",(const char*)mode)==0){
        //Nowa grupa
        if(n_of>=0){

          //send current group to GPU
          glGenVertexArrays(1, &groups_[n_of].vao);
          glBindVertexArray(groups_[n_of].vao);

          glEnableVertexAttribArray(0);
          glEnableVertexAttribArray(2);
          glEnableVertexAttribArray(3);

          glGenBuffers(1, &groups_[n_of].vertices);
          glBindBuffer(GL_ARRAY_BUFFER, groups_[n_of].vertices);
          glBufferData(GL_ARRAY_BUFFER, (n_of_vert_in_gr+1)*sizeof(NormalTextureVertex), vertices_in_gr, GL_STATIC_DRAW);

          glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)0);
          glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)sizeof(vertices_in_gr[0].position));
          glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)(sizeof(vertices_in_gr[0].position)+ sizeof(vertices_in_gr[0].texture)));

          glBindVertexArray(0);

          groups_[n_of].n_of_vertices=n_of_vert_in_gr+1;

        }
        n_of++;

        if(n_of>=max){
          max+=delta;
          new_groups=(VertexGroup*) realloc(groups_,max*sizeof(VertexGroup));
          if(NULL!=new_groups) groups_=new_groups;
          else {
            cerr<< "ERROR: Could not allocate memory for new groups\n";
            exit(EXIT_FAILURE);
          }
        }
        file >> mat_name;
        mat_number=FindMatNumber(mat_name);
        if(mat_number<0){
          cerr<< "ERROR: Could not find material\n";
          exit(EXIT_FAILURE);
        }
        groups_[n_of].mat_number=mat_number;
        n_of_vert_in_gr=-1;
      }
      else file.ignore(1024,'\n') ;

    }// While
    file.close();
    if(n_of>=0){
//        n_of_vert_in_gr-=3;
      //send current group to GPU
      glGenVertexArrays(1, &groups_[n_of].vao);
      glBindVertexArray(groups_[n_of].vao);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);

      glGenBuffers(1, &groups_[n_of].vertices);
      glBindBuffer(GL_ARRAY_BUFFER, groups_[n_of].vertices);
      glBufferData(GL_ARRAY_BUFFER, (n_of_vert_in_gr+1)*sizeof(NormalTextureVertex), vertices_in_gr, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)0);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)sizeof(vertices_in_gr[0].position));
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_in_gr[0]), (GLvoid*)(sizeof(vertices_in_gr[0].position)+ sizeof(vertices_in_gr[0].texture)));

      glBindVertexArray(0);

      groups_[n_of].n_of_vertices=n_of_vert_in_gr+1;

    }

    free(vertices);
    free(vertices_in_gr);
    free(tex_coords);
    free(normals);
    file.close();

  }// If fopen
  else{ //
      cerr<< "ERROR: Could not open file "<<filename<<endl;
  }
  return n_of+1;
}



int ObjModel::LoadMaterials(const char* filename){
  int n_of=-1;
  int maxMat=2;
  int d_mat=2;
  char mode[10];
  NamedMaterial * new_materials;

  ifstream file (filename, ios::in|ios::binary);

  if (file.is_open()) {
    materials_=(NamedMaterial*) malloc(maxMat*sizeof(NamedMaterial));

    while(file>>mode){
      if(strcmp("newmtl",(const char*)mode)==0){
        //Material Name
        n_of++;
        if(n_of>=maxMat){
          maxMat+=d_mat;
          new_materials=(NamedMaterial*)realloc(materials_,maxMat*sizeof(NamedMaterial));
          if(NULL!=new_materials) materials_=new_materials;
          else {
            cerr<< "ERROR: Could not allocate memory for materials\n";
            file.close();
            exit(EXIT_FAILURE);
          }
        }
        file>>materials_[n_of].name_;
        materials_[n_of].m.emission[0]=0.0f;
        materials_[n_of].m.emission[1]=0.0f;
        materials_[n_of].m.emission[2]=0.0f;
        materials_[n_of].m.emission[3]=1.0f;
      }
      else if(strcmp("Ns",(const char*)mode)==0){
        // shininess
        file>> materials_[n_of].m.shininess;
      }
      else if(strcmp("Ka",(const char*)mode)==0){
        // ambient
        file>>materials_[n_of].m.ambient[0]>>materials_[n_of].m.ambient[1]>>materials_[n_of].m.ambient[2];
         materials_[n_of].m.ambient[3]=1.0f;
      }
      else if(strcmp("Kd",(const char*)mode)==0){
        // diffuse
        file>>materials_[n_of].m.diffuse[0]>>materials_[n_of].m.diffuse[1]>>materials_[n_of].m.diffuse[2];
         materials_[n_of].m.diffuse[3]=1.0f;
      }
      else if(strcmp("Ks",(const char*)mode)==0){
        // specular
        file>>materials_[n_of].m.specular[0]>>materials_[n_of].m.specular[1]>>materials_[n_of].m.specular[2];
         materials_[n_of].m.specular[3]=1.0f;
      }
      else file.ignore(1024,'\n');
    }
    file.close();
  }
  else{
      cerr<<"ERROR: Could not open file" << filename<<endl;
      exit(EXIT_FAILURE);
   }
  return n_of+1;
}


void ObjModel::cpf(GLfloat* from, GLfloat* to, int n){
    if(n==4){
        to[3]=1.0f;
        n--;
    }
    while(n-->0){
        to[n]=from[n];
    }
    return;
}

int ObjModel::FindMatNumber(const char* mat_name){
    int i;
    for (i=0;i<n_of_materials_;i++){
        if(strcmp(mat_name,(const char* )materials_[i].name_)==0){
            return i;
        }
    }
    return -1;
}
