//// https://github.com/glfw/glfw/issues/2138
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<iostream>
using namespace std;

const char* vertex_shader_text =
"#version 330 core\n"
"layout(location = 0) in vec2 vPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 1, 1);\n"
"}\n";

const char* fragment_shader_text =
"#version 330 core\n"
"uniform vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color,1.0);\n"
"}\n";

GLuint loadShader(const char* vs, const char* fs) {
  const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vs, NULL);
  glCompileShader(vertex_shader);

  const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fs, NULL);
  glCompileShader(fragment_shader);

  const GLuint programID = glCreateProgram();
  glAttachShader(programID, vertex_shader);
  glAttachShader(programID, fragment_shader);
  glLinkProgram(programID);
  return programID;
}

float colors[2][3] = {
  {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mods) {
  if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void character_callback(GLFWwindow* window, unsigned int codepoint) {
  printf("character_callback: %p, codepoint:%c\n", window,codepoint);
  float r[3] = {1.0f, 0.0f, 0.0f};
  float g[3] = {0.0f, 1.0f, 0.0f};
  float b[3] = {0.0f, 0.0f, 1.0f};

  if (codepoint == '1') {
	for (int i = 0; i < 3; i++) {
	  colors[1][i] = r[i];
	}
  } else if (codepoint == '2') {
	for (int i = 0; i < 3; i++) {
	  colors[1][i] = g[i];
	}
  }
  if (codepoint == '3') {
	for (int i = 0; i < 3; i++) {
	  colors[1][i] = b[i];
	}
  } 
}

int main(int argc, char** argv) {
  const char* description;
  GLFWwindow* windows[2];
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  {
	windows[0] = glfwCreateWindow(300, 300, "window1", NULL, NULL);
	glfwSetCharCallback(windows[0], character_callback);
	glfwMakeContextCurrent(windows[0]);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//glfwSwapInterval(1);
  }

  const GLuint program = loadShader(vertex_shader_text, fragment_shader_text);

  GLuint vao[2];
  glGenVertexArrays(1, &vao[0]);
  GLuint vbo;
  glGenBuffers(1, &vbo);

  const GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f};
  {
	glUseProgram(program);
	glBindVertexArray(vao[0]);

	{
	  glBindBuffer(GL_ARRAY_BUFFER, vbo);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	  glEnableVertexAttribArray(0);
	}
	// glBindVertexArray(0);
  }

  // window2
  {
	windows[1] = glfwCreateWindow(300, 300, "window2", nullptr, windows[0]);

	glfwSetCharCallback(windows[1], character_callback);
	glfwMakeContextCurrent(windows[1]);

	glfwSwapInterval(1);
	{
	  glUseProgram(program);
	  glGenVertexArrays(1, &vao[1]);
	  glBindVertexArray(vao[1]);
	  {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
	  }
	  // glBindVertexArray(0);
	}
  }
  for (int i = 0; i < 2; i++) {
	glfwSetKeyCallback(windows[i], key_callback);

	glfwMakeContextCurrent(windows[i]);
	glClearColor(colors[0][0], colors[0][1], colors[0][2], 1.0);
	for (int k = 0; k < 3; k++) {
	  glClear(GL_COLOR_BUFFER_BIT);
	  glfwSwapBuffers(windows[i]);
	}
  }
  int color_pos = glGetUniformLocation(program, "color");
  glfwMakeContextCurrent(0);
  // ==========step 2============
  while (!glfwWindowShouldClose(windows[0]) &&
	  !glfwWindowShouldClose(windows[1])) {
	for (int i = 0; i < 2; i++) {
	  glfwPollEvents();
	  glfwMakeContextCurrent(windows[i]);
	  glClear(GL_COLOR_BUFFER_BIT);

	  glBindVertexArray(vao[i]);
	  glUniform3f(color_pos, colors[1][0], colors[1][1], colors[1][2]);
	  glDrawArrays(GL_TRIANGLES, 0, 3);
	  glfwSwapBuffers(windows[i]);
	  glBindVertexArray(0);
	  glfwMakeContextCurrent(0);
	}
  }
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
