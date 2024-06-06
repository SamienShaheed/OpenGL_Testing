#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// create vertex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // attach source code to the vertex shader object
	glCompileShader(vertexShader); // compile vertex shader to machine code

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //  create frag shader obj
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // attach source code to frag shader object
	glCompileShader(fragmentShader); // compile to machine code

	ID = glCreateProgram(); // create shader program
	glAttachShader(ID, vertexShader); // attach vertex obj to shader program
	glAttachShader(ID, fragmentShader); // attach frag obj 

	glLinkProgram(ID); // link all shaders together into the shader program

	// delete after linking 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}