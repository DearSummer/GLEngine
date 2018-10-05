

#define GLEW_STATIC 

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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

	Shader * shader = new Shader("VertexSource.txt", "FragmentSource.txt");

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

	//加载图片1
	//生成纹理
	unsigned int texture1,texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//配置纹理环绕和纹理过滤的方式
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char * picData = stbi_load("pic.jpg", &width, &height, &nrChannels, 0);
	if(picData)
	{
		//将图片载入cpu当中
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, picData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		AUTO_COUT_MSG("load img failed");
	}
	stbi_image_free(picData);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//配置纹理环绕和纹理过滤的方式
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载图片2
	picData = stbi_load("awesomeface.jpg", &width, &height, &nrChannels, 0);
	if (picData)
	{
		//将图片载入cpu当中
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, picData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		AUTO_COUT_MSG("load img failed");
	}
	stbi_image_free(picData);



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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//为shader添加uniform
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2);
		shader->setFloat("offset", greenValue);
		shader->use();

		//建立三角形
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//render windows
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}

	delete shader;
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
}