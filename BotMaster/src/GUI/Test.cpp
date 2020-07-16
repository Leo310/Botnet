#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "vendor/stb_image/stb_image.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}

static float visibil = 0.5f;
static float visibil1 = 0.5f;
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		visibil -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		visibil += 0.01;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		visibil1 -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		visibil1 += 0.01;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	{
		float vertices[] =
		{
			-0.5f,  -0.5f,  0.0f,       1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
			0.5f,   -0.5f,  0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
			0.5f,   0.5f,   0.0f,       0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
			-0.5f,  0.5f,   0.0f,       0.0f, 1.0f, 0.0f,       0.0f, 1.0f
		};

		unsigned int indices[] =
		{
			0, 1, 2, 2, 3, 0
		};

		unsigned int buffer;
		GLCall(glGenBuffers(1, &buffer));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 8 * sizeof(float), vertices, GL_STATIC_DRAW));

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), 0));

		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float))));

		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float))));

		unsigned int ibo;
		GLCall(glGenBuffers(1, &ibo));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

		glBindVertexArray(0);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

		Shader shader("src/GUI/res/Shaders/Vertex.shader", "src/GUI/res/Shaders/Fragment.shader");
		shader.Bind();

		unsigned int texture1;
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("src/GUI/res/textures/container.jpg", &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "failed loading texture" << std::endl;
		}
		stbi_image_free(data);

		unsigned int texture2;
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width1, height1, nrChannels1;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data1 = stbi_load("src/GUI/res/textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
		if (data1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "failed loading texture" << std::endl;
		}
		stbi_image_free(data1);
		glBindTexture(GL_TEXTURE_2D, 0);

		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);

		/* Loop until the user closes the window */
			GLCall(glClearColor(0.3f, 0.5f, 0.2f, 1.0f));
			float greenValue = 1.0f;
		while (!glfwWindowShouldClose(window))
		{
			processInput(window); 
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			float timeValue = glfwGetTime();
			//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		
			shader.setFloat("u_Opacity", greenValue);
			shader.setFloat("visibility", visibil);

			glm::mat4 trans = glm::mat4(1.0f);
			//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			trans = glm::translate(trans, glm::vec3(visibil1, visibil, 0.0f));

			shader.setMat4("transform", trans);

			//GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			GLCall(glBindVertexArray(vao));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}