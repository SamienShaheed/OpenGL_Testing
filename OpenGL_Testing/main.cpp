#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"

int main() {
	
	glfwInit(); // Initialize GLFW Window for OpenGL

	// Let glfw know the version of openGL (version 3.3 means major 3 and minor 3 version)
	// Change according to OpenGL version used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL profiles (core and compatibility) determine which features of the OpenGL API are available in the code.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile

	GLfloat vertices[] = { // Store vertices of a triangle
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper vertex
	};

	// arguments (width, height, window name, monitor handle for full screen, window handle to share OpenGL contents)
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test Graphiscs", NULL, NULL);
	if (window == NULL) { // error checking
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// OpenGL Context is a data structure that stores all the OpenGL states and resources
	glfwMakeContextCurrent(window); // Assign current context to window pointer 

	gladLoadGL(); // Load OpenGL configurations
	glViewport(0, 0, 800, 800); // Set viewport from (0,0) to (800, 800)

	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
;
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Teal
	glClear(GL_COLOR_BUFFER_BIT); // Back buffer with set color, front buffer with default bg color
	glfwSwapBuffers(window); // Swap buffers to display new bg color

	// Main while loop
	while (!glfwWindowShouldClose(window)) { // Keep window open till closed by user
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Teal
		glClear(GL_COLOR_BUFFER_BIT); // Back buffer with set color, front buffer with default bg color
		shaderProgram.Activate(); // assign opengl to use written program
		VAO1.Bind(); // bind VAO to opengl
		glDrawArrays(GL_TRIANGLES, 0, 3); // draw triangle using openGL primitives 
		glfwSwapBuffers(window);

		glfwPollEvents(); // Process all pending events within the window. Called once per frame
	}

	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window); // Destroy context window once done
	glfwTerminate(); // Terminate GLFW Window at the end of code

	return 0;
}