#ifndef STARPROGRAM_H
#define STARPROGRAM_H

#include "modelprogram.h"
#include "material.h"

class StarProgram : public ModelProgram
{
	public:
		void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
		void SetStarColor(const TransparentMaterial & color) const;
	private:
		GLint star_color_location_;
};

#endif //STARPROGRAM_H
