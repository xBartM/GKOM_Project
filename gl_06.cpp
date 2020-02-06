#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <vector>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeModel.h"
#include "HexagonalPrismModel.h"
#include "ThreadModel.h"
#include "TableModel.h"
#include "Camera.h"
#include "SpannerModel.h"
#include "SimpleTableModel.h"
#include "Animation.h"

const GLuint WIDTH = 1600, HEIGHT = 900;

// key buffer for camera movement
bool keys[1024];
double gxpos1 = 0;
double gypos1 = 0;
double gxpos2 = 0;
double gypos2 = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 3.0f, 3.0f);
GLfloat pitch = 0.0f; // elewacja
const GLfloat pitch_max = 80.0f, pitch_min = -80.0f;

GLfloat yaw = 0.0f; // azymut
const GLfloat yaw_max = 360.0f, yaw_min = 0.0f;

GLfloat roll = 0.0f; // "roll" xd

glm::vec3 viewPoint = glm::vec3(0.0f, 0.0f, 0.0f);


glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	// "up" is along increasing y axis

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	gxpos2 = gxpos1;
	gypos2 = gypos1;
	gxpos1 = xpos;
	gypos1 = ypos;
}


void do_movement(Camera* camera, Animation* animation)
{
	//camera.ProcessKeyboard();
	//camera.ProcessMouseMovement();
	
	// Camera controls
	if (keys[GLFW_KEY_UP])
	{
		animation->spannerIn();
	}
	
	if (keys[GLFW_KEY_DOWN])
	{
		animation->spannerOut();
	}

	if (keys[GLFW_KEY_LEFT])
	{
		animation->screwOut();
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		animation->screwIn();
	}


	if (keys[GLFW_KEY_W])
	{
		camera->ProcessKeyboard(FORWARD, 0.001f);
	}
	if (keys[GLFW_KEY_S])
	{
		camera->ProcessKeyboard(BACKWARD, 0.001f);
	}
	if (keys[GLFW_KEY_A])
	{
		camera->ProcessKeyboard(LEFT, 0.001f);
	}
	if (keys[GLFW_KEY_D])
	{
		camera->ProcessKeyboard(RIGHT, 0.001f);
	}
	if (keys[GLFW_KEY_E])
	{
		camera->ProcessKeyboard(UP, 0.001f);
	}
	if (keys[GLFW_KEY_Q])
	{
		camera->ProcessKeyboard(DOWN, 0.001f);
	}

}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

extern "C" // run on NVIDIA GPU
{
	//_declspec(dllexport) int NvOptimusEnablement = 0x00000001;
}

int main()
{
	
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 06", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_06.vert", "gl_06.frag");

		// Set up cube model
		CubeModel cube(10.0f);
		HexagonalPrismModel prism(1.99f);
		ThreadModel thread(32.0f);
		TableModel table(3.0f);
		SpannerModel spanner(8.0f);
		SimpleTableModel simpleTable(7.0f, 1.0f);
		Animation animation(&prism, &thread, &table, &spanner);
		//Animation animation(&prism, &thread, &simpleTable, &spanner);

		// Set up camera
		Camera camera(cameraPos, cameraUp, -90.0f, 0.0f);

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "iipw.png");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "weiti.png");
		GLuint texture2 = LoadMipmapTexture(GL_TEXTURE2, "bolthead.jpg");
		GLuint texture3 = LoadMipmapTexture(GL_TEXTURE3, "metal3.jpg");
		GLuint texture4 = LoadMipmapTexture(GL_TEXTURE4, "skybox2.png");

		glEnable(GL_DEPTH_TEST); // let's use z-buffer

		glm::mat4 trans = glm::mat4();

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Calculate deltatime of current frame
			GLfloat currentFrame = (GLfloat)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			do_movement(&camera, &animation);
			camera.ProcessMouseMovement(-(gxpos2 - gxpos1), gypos2 - gypos1);
			gxpos2 = gxpos1;
			gypos2 = gypos1;
			
			//camera.GetViewMatrix();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Bind Textures using texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture4);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
		
			theProgram.Use();
			GLuint modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");
			GLuint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLuint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");

			// set perspective projection & pass it to GPU
			glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// set view transformation & pass it to GPU
			glm::mat4 view;
			view = camera.GetViewMatrix();//glm::lookAt(cameraPos, viewPoint, cameraUp);	// camera position, viewpoint, "up" axis
			//glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			// draw skybox
			glm::mat4 transky = glm::mat4();
			transky = glm::translate(transky, camera.getPosition());
			transky = glm::scale(transky, glm::vec3(10.0f, 10.0f, 10.0f));	// make skybox bigger
			cube.Draw(transky, modelLoc);

			// draw scene
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture3);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
			
			
			// draw table
			animation.drawTable(modelLoc);
			//animation.drawSimpleTable(modelLoc);
			
			// draw thread
			animation.drawThread(modelLoc);

			// draw spanner
			animation.drawSpanner(modelLoc);

			// draw bolt head
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);

			animation.drawPrism(modelLoc);

			// draw alternative table

			
			
			//animation.drawScene(modelLoc);
			


			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
