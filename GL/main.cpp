
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
#include "Model.h"
#include <filesystem>

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
//Camera * camera = new Camera(glm::vec3(0, 0, 3), glm::vec3(1, 1, 0));

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
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfwWindow, cursor_callback);
 //
	// //vertex array object
	// unsigned int VAO;
	// glGenVertexArrays(1, &VAO);
 //
	// //vertext buffer object
	// unsigned int VBO;
	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// glBindVertexArray(VAO);
 // //
	// // unsigned int EBO;
	// // glGenBuffers(1, &EBO);
	// // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 //
 //
	// //将vbo信息写到vao
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);
 //
	// // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// // glEnableVertexAttribArray(1);
 //
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
 //
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	// glEnableVertexAttribArray(2);

	//Camera * camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0,0,0));
	

	glm::mat4 modelMat(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1, 0, 0));
	
	glm::mat4 projectionMat(1.0f);
	projectionMat = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);

	// unsigned int LIGHT_VAO;
	// glGenVertexArrays(1, &LIGHT_VAO);
	// glBindVertexArray(LIGHT_VAO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
 //
	// //将vbo信息写到vao
	// glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(5);

	Shader * shader = new Shader("LightVertexShader.vert", "LightFragmentShader.frag");
	//Shader * simpleShader = new Shader("SimpleVertexShader.vert", "SimpleFragmentShader.frag");
	
	Model riko("nanosuit.obj");
	
	// Texture2D * picTex = Texture2D::Builder().setResourcePath("pic.jpg").build();
	// Texture2D * awesomeface = Texture2D::Builder().setResourcePath("awesomeface.png").build();
 //
	// Texture2D * container = Texture2D::Builder().setResourcePath("container.png").build();
	// Texture2D * specularTexture = Texture2D::Builder().setResourcePath("container_specular.png").build();
	// Texture2D * emission = Texture2D::Builder().setResourcePath("matrix.jpg").build();


	Light * spotLight01 = Light::Builder(shader, glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
		.setSpotLight(glm::vec3(0,1,3),glm::vec3(0,0,-1),glm::cos(glm::radians(12.5f)),glm::cos(glm::radians(25.0f)))
		.Build();

	Light * spotLight02 = Light::Builder(shader, glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
		.setSpotLight(glm::vec3(4, -1, -3), glm::vec3(0,0,-1), glm::cos(glm::radians(22.5f)), glm::cos(glm::radians(45.0f)))
		.Build();

	Light * pointLight01 = Light::Builder(shader, glm::vec3(1.0f, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
		.setPointLight(glm::vec3(0.7f, 0.2f, -2.0f), 1.0f, 0.9f, 0.032f)
		.Build();
	Light * pointLight02 = Light::Builder(shader, glm::vec3(0, 1.0f, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
		.setPointLight(glm::vec3(2.3f, -3.3f, -4.0f), 1.0f, 0.9f, 0.032f)
		.Build();
	Light * pointLight03 = Light::Builder(shader, glm::vec3(0, 0, 1.0f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
		.setPointLight(glm::vec3(-4.0f, 2.0f, -8.0f), 1.0f, 0.9f, 0.032f)
		.Build();
	Light * pointLight04 = Light::Builder(shader, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
		.setPointLight(glm::vec3(3.0f, 1.2f, 3.0f), 1.0f, 0.9f, 0.032f)
		.Build();

	Light * directionalLight = Light::Builder(shader, glm::vec3(4, 4, 4), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f))
		.setDirectionalLight(glm::vec3(glm::radians(-45.0f)))
		.Build();

	while(!glfwWindowShouldClose(glfwWindow))
	{
		float preRenderTime = glfwGetTime();

		//handle user input
		processInput(glfwWindow);

		//render command;
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 viewMat = camera->getViewMatrix();
		projectionMat = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);

		shader->use();
		shader->setMatrix4X4("m", 1, glm::value_ptr(modelMat));
		shader->setMatrix4X4("v", 1, glm::value_ptr(viewMat));
		shader->setMatrix4X4("p", 1, glm::value_ptr(projectionMat));

		riko.draw(shader);

		//  //draw call
		//   for (int i = 0; i < 10; i++)
		//   {
		//   	modelMat = IDENTITY_MATIX;
		//   	modelMat = glm::translate(modelMat, cubePositions[i]);
		//   	//modelMat = glm::rotate(modelMat, glm::radians(30.0f * i) * static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 1.0f, -1.0f));
  //
		//  	shader->use();
		//   	shader->setMatrix4X4("m", 1, glm::value_ptr(modelMat));
		//   	shader->setMatrix4X4("v", 1, glm::value_ptr(viewMat));
		//   	shader->setMatrix4X4("p", 1, glm::value_ptr(projectionMat));
		// 	glUniform3f(glGetUniformLocation(shader->id, "cameraPos"), camera->position.x, camera->position.y, camera->position.z);
  //
  //
			spotLight01->active("spotLight01");
			spotLight02->active("spotLight02");
			pointLight01->active("pointLight01");
			pointLight02->active("pointLight02");
			pointLight03->active("pointLight03");
			pointLight04->active("pointLight04");
			directionalLight->active("directionalLight01");
  //
		// 	container->active(GL_TEXTURE0);
		// 	specularTexture->active(GL_TEXTURE1);
		// 	emission->active(GL_TEXTURE2);
  //
		// 	//glUniform3f(glGetUniformLocation(shader->id, "material.ambient"), 1.0f,1.0f,1.0f);
		// 	glUniform1i(glGetUniformLocation(shader->id, "material.diffuse"),0);
		// 	glUniform1i(glGetUniformLocation(shader->id, "material.specular"), 1);
		// 	glUniform1i(glGetUniformLocation(shader->id, "material.emission"), 2);
		// 	glUniform1f(glGetUniformLocation(shader->id, "material.shininess"), 64.0f);
  //
		// 	shader->setFloat("time", glfwGetTime());
  //
		//   	//建立三角形
		//   	glBindVertexArray(VAO);
  //
		//   	glDrawArrays(GL_TRIANGLES, 0, 36);
		//   }
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, spotLight01->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", spotLight01->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, spotLight02->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", spotLight02->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, pointLight01->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", pointLight01->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, pointLight02->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", pointLight02->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, pointLight03->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", pointLight03->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, pointLight04->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		// simpleShader->setVector3("color", pointLight04->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
  //
		//  simpleShader->use();
		//  modelMat = IDENTITY_MATIX;
		//  modelMat = glm::translate(modelMat, directionalLight->getPosition());
		//  modelMat = glm::scale(modelMat, glm::vec3(0.5, 0.5, 0.5));
		//  simpleShader->setVector3("color", directionalLight->getLightColor());
		//  simpleShader->setMatrix4X4("modelMat", 1, glm::value_ptr(modelMat));
		//  simpleShader->setMatrix4X4("viewMat", 1, glm::value_ptr(viewMat));
		//  simpleShader->setMatrix4X4("projectionMat", 1, glm::value_ptr(projectionMat));
		//  glBindVertexArray(LIGHT_VAO);
		//  glDrawArrays(GL_TRIANGLES, 0, 36);
  //
		// //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //


		//render windows
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		deltaTime = glfwGetTime() - preRenderTime;
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
		camera->translate(CAMERA_FORWARD_DIRECTION * deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->translate(-CAMERA_FORWARD_DIRECTION * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->translate(CAMERA_RIGHT_DIRECTION * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->translate(-CAMERA_RIGHT_DIRECTION * deltaTime);
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