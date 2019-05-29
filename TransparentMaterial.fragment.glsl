#version 430 core

//layout(location=0) out vec4 in_position; //bylo in
layout(location=0) out vec4 color; //bylo in


uniform vec4 material;



void main(void){

  color = material;
}


