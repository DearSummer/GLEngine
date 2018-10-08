
#define GLEW_STATIC 

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"


#define AUTO_COUT_MSG(str) std::cout << str << std::endl

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

const unsigned int indices[] = {
	0,1,3,
	1,2,3
};

float mixValue = 0.1f;

Camera * camera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f));
//Camera * camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(1, 1, 0));

#define IDENTITY_MATIX glm::mat4(1.0f)

float deltaTime;

void processInput(GLFWwindow * window);
GLFWwindow * initWindow();

void cursor_callback(GLFWwindow * window, double posX, double posY);

int main()
{
	GLFWwindow * glfwWindow = initWindow();
	if(glfwWindow == nullptr)
	{
		return -1;
	}

	//�޳�����
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfwWindow, cursor_callback);

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


	//��vbo��Ϣд��vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader * shader = new Shader("VertexSource.txt", "FragmentSource.txt");

	Texture2D * picTex = Texture2D::Builder().setResourcePath("pic.jpg").build();
	Texture2D * awesomeface = Texture2D::Builder().setResourcePath("awesomeface.png").build();


	//�趨�ĸ�texture2D��Ӧ�ĸ�simpler2D
	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	//Camera * camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0,0,0));
	

	glm::mat4 modelMat(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1, 0, 0));
	
	glm::mat4 projectionMat(1.0f);
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	while(!glfwWindowShouldClose(glfwWindow))
	{
		float preRenderTime = glfwGetTime();

		//handle user input
		processInput(glfwWindow);

		//render command;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		picTex->active(GL_TEXTURE0);
		awesomeface->active(GL_TEXTURE1);

		//Matrix4 trans = IDENTITY_MATIX;
		//trans = glm::translate(trans, glm::vec3(0.5f, 0, 0));
		//shader->setMatrix4X4("transform", 1, glm::value_ptr(trans));

		//Ϊshader���uniform
		//float timeValue = glfwGetTime();
		//float offsetValue = (sin(timeValue) / 2);
		//shader->setFloat("offset", offsetValue);
		glm::mat4 viewMat = camera->getViewMatrix();

		//draw call
		for (int i = 0; i < 10; i++)
		{
			modelMat = IDENTITY_MATIX;
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, glm::radians(30.0f * i) * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, -1.0f));

			shader->setFloat("mixValue", mixValue);
			shader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
			shader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
			shader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
			shader->use();

			//����������
			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//render windows
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		deltaTime = glfwGetTime() - preRenderTime;
	}

	delete shader;
	delete picTex;
	delete awesomeface;
	delete camera;

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

	if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->updatePos(glm::vec3(1, 1, 1) * camera->forward * deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->updatePos(glm::vec3(-1, -1, -1) * camera->forward * deltaTime);
	}
}

float lastPosX, lastPosY;
bool isFristCursorCallback = true;
void cursor_callback(GLFWwindow * window, double posX, double posY)
{
	if(isFristCursorCallback)
	{
		isFristCursorCallback = false;
		lastPosX = posX;
		lastPosY = posY;
	}

	float detlaX = posX - lastPosX;
	float detlaY = posY - lastPosY;

	lastPosX = posX;
	lastPosY = posY;

	camera->updateLookAt(detlaY * deltaTime, detlaX * deltaTime);

}