#include <GL/glew.h>
#include <GL/glfw.h>

class GraphicsWindow {
private:
	int height, width;
	double r, g, b, a;

public:
		GraphicsWindow(int h, int w);
		void setBG(double r, double g, double b, double a);
		void show();
		void createWindow();
		void quit(int exit_status);
};
