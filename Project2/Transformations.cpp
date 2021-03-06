#include <GLFW/glfw3.h>
#include <math.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500

const float ox1 = 270, ox2 = 370, ox3 = 320, oy1 = 150, oy2 = 150, oy3 = 320;
float x = 0, y = 0;
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void Display();
int main(void)
{
	GLFWwindow *window;

	// Initialize the library
	if (!glfwInit())
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transformations", NULL, NULL);

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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glfwSetKeyCallback(window, keyCallback);
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void Display()
{
	glColor3f(1.0f, 0.5f, 0.2f);
	glBegin(GL_TRIANGLES);

	{

		glVertex3f(ox1 + x, oy1 + y, 0.0); //Left

		glVertex3f(ox2 + x, oy2 + y, 0.0); //Right

		glVertex3f(ox3 + x, oy3 + y, 0.0); //Top

	}

	glEnd();

}



void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{


	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	switch (key)
	{
	case GLFW_KEY_LEFT:
		if (x + ox1 >= 0)
			x--;
		break;
	case GLFW_KEY_RIGHT:
		if (x + ox2 <= 600)
			x++;
		break;
	case GLFW_KEY_UP:
		if (y + oy3 <= 500)
			y++;
		break;
	case GLFW_KEY_DOWN:
		if (y + oy1 >= 0)
			y--;
		break;
	case GLFW_KEY_L:
		glTranslatef(x + ox1, y + oy1, 0);
		glRotatef(5, 0, 0, 1);
		glTranslatef(-(x + ox1), -(y + oy1), 0);
		break;
	case GLFW_KEY_R:
		glTranslatef(x + ox1, y + oy1, 0);
		glRotatef(-5, 0, 0, 1);
		glTranslatef(-(x + ox1), -(y + oy1), 0);
		break;
	case GLFW_KEY_B:
		glTranslatef(x + ox1, y + oy1, 0);
		glScaled(1.5, 1.5, 0);
		glTranslatef(-(x + ox1), -(y + oy1), 0);
		break;
	case GLFW_KEY_S:
		glTranslatef(x + ox1, y + oy1, 0);
		glScaled(1 / 1.5, 1 / 1.5, 0);
		glTranslatef(-(x + ox1), -(y + oy1), 0);
		break;
	default:
		break;
	}
}