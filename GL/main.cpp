
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
#include "Math/SimpleMath.h"
#include "Light.h"
#include <filesystem>
#include "Model.h"

#define AUTO_COUT_MSG(str) std::cout << str << std::endl

#pragma region  vertices
float lightvertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
#pragma endregion 

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

Camera * camera = new Camera(glm::vec3(0, 0, 0), glm::quat_cast(glm::mat4(1.0f)));

#define IDENTITY_MATIX glm::mat4(1.0f)

float deltaTime;
float windowWidth = 800.0f, windowHeight = 600.0f;

void processInput(GLFWwindow * window);
GLFWwindow * initWindow();

void cursor_callback(GLFWwindow * window, double posX, double posY);
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

int main()
{
	GLFWwindow * glfwWindow = initWindow();
	if(glfwWindow == nullptr)
	{
		return -1;
	}


	//剔除背面
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfwWindow, cursor_callback);
 
	 //vertex array object
	 unsigned int VAO;
	 glGenVertexArrays(1, &VAO);
 
	 //vertext buffer object
	 unsigned int VBO;
	 glGenBuffers(1, &VBO);
	 glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	 glBindVertexArray(VAO);

 
	 //将vbo信息写到vao
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	 glEnableVertexAttribArray(0);
 

	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	 glEnableVertexAttribArray(1);
 
	 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	 glEnableVertexAttribArray(2);

	glm::mat4 modelMat(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1, 0, 0));
	
	glm::mat4 projectionMat(1.0f);
	projectionMat = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);

	 unsigned int LIGHT_VAO;
	 glGenVertexArrays(1, &LIGHT_VAO);
	 glBindVertexArray(LIGHT_VAO);
	 glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
	 //将vbo信息写到vao
	 glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	 glEnableVertexAttribArray(5);

	 glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	 glEnableVertexAttribArray(6);

	Shader * shader = new Shader("LightVertexShader.vert", "LightFragmentShader.frag");
	Shader * simpleShader = new Shader("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
	
	Model book("Resource/fantasy_book/source/TEST2.fbx","Resource/fantasy_book/textures/");
	Model man("Resource/nanosuit/nanosuit.obj", "Resource/nanosuit/");

	 Texture2D * container = Texture2D::Builder().setResourcePath("container.png").build();


	Light * directionalLight = Light::Builder(shader, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f))
		.setDirectionalLight(glm::vec3(0,glm::radians(90.0f),0))
		.Build();

	Light * spotLight = Light::Builder(shader, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f))
		.setSpotLight(camera->getPosition(),glm::eulerAngles(camera->getOrientation()),12.5f,25.0f)
		.Build();

	while (!glfwWindowShouldClose(glfwWindow))
	{
		float preRenderTime = glfwGetTime();

		//handle user input
		processInput(glfwWindow);

		//render command;
		glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 viewMat = camera->getViewMatrix();
		projectionMat = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);

		shader->use();
		shader->setMatrix4X4("m", 1, glm::value_ptr(modelMat));
		shader->setMatrix4X4("v", 1, glm::value_ptr(viewMat));
		shader->setMatrix4X4("p", 1, glm::value_ptr(projectionMat));

		book.draw(shader);
		man.draw(shader);

		//directionalLight->active("directionalLight01");
		spotLight->active("spotLight01");

		spotLight->setPosition(camera->getPosition());

		simpleShader->use();
		modelMat = IDENTITY_MATIX;
		modelMat = glm::translate(modelMat, spotLight->getPosition());
		modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		simpleShader->setVector3("color", directionalLight->getLightColor());
		simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		container->active(GL_TEXTURE0);
		glBindVertexArray(LIGHT_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		simpleShader->use();
		modelMat = IDENTITY_MATIX;
		modelMat = glm::translate(modelMat, directionalLight->getPosition());
		modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		simpleShader->setVector3("color", directionalLight->getLightColor());
		simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		container->active(GL_TEXTURE0);
		glBindVertexArray(LIGHT_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//render windows
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		deltaTime = glfwGetTime() - preRenderTime;

		//std::cout << camera->toString() << std::endl;
	}

	delete shader;
	//delete spotLight01;
	//delete picTex;
	//delete awesomeface;
	delete camera;
	//delete simpleShader;
	//delete container;

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
		camera->translate(CAMERA_FORWARD_DIRECTION * deltaTime* 10.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->translate(-CAMERA_FORWARD_DIRECTION * deltaTime* 10.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->translate(CAMERA_RIGHT_DIRECTION * deltaTime * 10.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->translate(-CAMERA_RIGHT_DIRECTION * deltaTime * 10.0f);
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
	float detlaY = lastPosY - posY;

	lastPosX = posX;
	lastPosY = posY;

	camera->yaw(detlaX * deltaTime);
	camera->pitch(detlaY * deltaTime);

}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}