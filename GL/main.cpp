
#define GLEW_STATIC 

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture2D.h"


#define AUTO_COUT_MSG(str) std::cout << str << std::endl

float vertices[] = {
	//位置--------------颜色-----------------uv--------
	0.5f,   0.5f, 0.0f,  1.0f, 0,    0,      1.0f,1.0f,
	0.5f,  -0.5f, 0.0f,  0,    1.0f, 0,      1.0f,  0,
	-0.5f, -0.5f, 0.0f,  0,    0,    1.0f,   0,     0,
	-0.5f,  0.5f, 0.0f,  1.0f, 0,    1.0f,   0,   1.0f
};

const unsigned int indices[] = {
	0,1,3,
	1,2,3
};

float mixValue = 0.1f;

typedef glm::mat4 Matrix4;

#define IDENTITY_MATIX Matrix4(1.0f)


void processInput(GLFWwindow * window);
GLFWwindow * initWindow();


int main()
{
	GLFWwindow * glfwWindow = initWindow();
	if(glfwWindow == nullptr)
	{
		return -1;
	}

	//剔除背面
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//vertext buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//将vbo信息写到vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader * shader = new Shader("VertexSource.txt", "FragmentSource.txt");


	Texture2D * picTex = Texture2D::Builder().setResourcePath("pic.jpg").build();
	Texture2D * awesomeface = Texture2D::Builder().setResourcePath("awesomeface.png").build();


	//设定哪个texture2D对应哪个simpler2D
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	

	while(!glfwWindowShouldClose(glfwWindow))
	{
		//handle user input
		processInput(glfwWindow);

		//render command;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		picTex->active(GL_TEXTURE0);
		awesomeface->active(GL_TEXTURE1);

		Matrix4 trans = IDENTITY_MATIX;
		trans = glm::translate(trans, glm::vec3(0.5f, 0, 0));
		shader->setMatrix4X4("transform", 1, glm::value_ptr(trans));

		//为shader添加uniform
		float timeValue = glfwGetTime();
		float offsetValue = (sin(timeValue) / 2);
		shader->setFloat("mixValue", mixValue);
		shader->setFloat("offset", offsetValue);
		shader->use();
		
		//建立三角形
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	    trans = IDENTITY_MATIX;
		trans = glm::scale(trans, glm::vec3(sin(glfwGetTime()) /2 + 0.5f, sin(glfwGetTime())/2 + 0.5f, 1));
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0));
		shader->setMatrix4X4("transform", 1, glm::value_ptr(trans));
		shader->setFloat("mixValue", -mixValue);
		shader->setFloat("offset", 0);
		shader->use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//render windows
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}

	delete shader;
	delete picTex;
	delete awesomeface;

	glfwTerminate();
	return 0;
}



GLFWwindow * initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow * glfwWindow = glfwCreateWindow(800, 600, "My OpenGL", nullptr, nullptr);
	if (glfwWindow == nullptr)
	{
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(glfwWindow);


	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return nullptr;
	}

	glViewport(0, 0, 800, 600);
	return glfwWindow;
}


void processInput(GLFWwindow * window)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f;
	}
	if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f;
	}
}