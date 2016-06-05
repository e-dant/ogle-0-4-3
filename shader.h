#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <iostream>
#include <fstream>
#include <OpenGL/GL.h>
#include "transform.h"
#include "commonData.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
    void Update(const Transform& transform, const Camera& camera, xyz_i lightDir);
    void Update(const Transform& transform, const Camera& camera);
    void UpdateLight(float lightDir[3]);
    void UpdateMatrix();
    static const unsigned int NUM_SHADERS = 2;
    static const unsigned int NUM_UNIFORMS = 3;
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
	virtual ~Shader();
//protected:
//private:

	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);


};

#endif
