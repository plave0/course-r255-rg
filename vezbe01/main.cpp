#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

#include "shader.h"

// Pomoćne funkcije (u definicijama je detaljniji opis)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void update(GLFWwindow* window);
void key_callback(GLFWwindow*, int, int, int, int);

int main() {

	// INICIJALIZACIJA PROZORA
	// ###############################################################################

	// Podešavanje prozora

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Kreiranje prozora

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello window", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to open window.\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// Učitavanje OpenGL funkcija

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		std::cout << "Failed to init GLAD\n";
		exit(EXIT_FAILURE);
	}

	// ###############################################################################

	float vertices[] = {
	-0.5f, -0.5f, 0, 1.0f, 0.0f, 0.0f, // levo teme
	0.5f, -0.5f, 0, 0.0f, 0.0f, 1.0f, //desno teme
	0, 0.5f, 0, 0.0f, 1.0f, 0.0f //gornje teme
	};

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Shader sh("vertex.glsl", "fragment.glsl");


	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sh.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		std::cerr << "Error\n";
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		glClearColor(1.0, 0, 0, 1.0);
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		glClearColor(0, 1, 0, 1.0);
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		glClearColor(0, 0, 1, 1.0);
	}

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void update(GLFWwindow* windows) {

	if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windows, true);
	}
}
