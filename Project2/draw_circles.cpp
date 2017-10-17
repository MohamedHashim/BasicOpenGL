
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);
void processInput(GLFWwindow *window);
float r = 1.0, g = 0.0, b = 0.0;
float r2 = 0.0, g2 = 1.0, b2 = 0.0;
float r3 = 0.0, g3 = 0.0, b3 = 1.0;
int main(void)
{
	GLFWwindow *window;

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Draw Circles", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment

					  // Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		// render OpenGL here
		glColor3f(r, g, b);
		drawCircle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, 120);
		glColor3f(r2, g2, b2);
		drawCircle(SCREEN_WIDTH / 1.9, SCREEN_HEIGHT / 1.5, 0, 120);
		glColor3f(r3, g3, b3);
		drawCircle(SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 4, 0, 120);
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{
	GLfloat twicePi = 2.0f * 3.14;

	GLfloat circleVerticesX[363];
	GLfloat circleVerticesY[363];
	GLfloat circleVerticesZ[363];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < 363; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i *  twicePi / 360));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / 360));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(363) * 3];

	for (int i = 0; i <363; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 363);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (r == 1.0 && g == 0.0&& b == 0.0)
		{
			r = 0.0;
			g = 1.0;
			b = 0.0;

			r2 = 0.0;
			g2 = 0.0;
			b2 = 1.0;

			r3 = 1.0;
			g3 = 0.0;
			b3 = 0.0;
		}
		else if (r == 0.0 &&g == 1.0&&b == 0.0)
		{
			r = 0.0;
			g = 0.0;
			b = 1.0;

			r2 = 1.0;
			g2 = 0.0;
			b2 = 0.0;

			r3 = 0.0;
			g3 = 1.0;
			b3 = 0.0;
		}
		else if (r == 0.0 &&g == 0.0&&b == 1.0)
		{
			r = 1.0;
			g = 0.0;
			b = 0.0;

			r2 = 0.0;
			g2 = 1.0;
			b2 = 0.0;

			r3 = 0.0;
			g3 = 0.0;
			b3 = 1.0;
		}
	}

}
