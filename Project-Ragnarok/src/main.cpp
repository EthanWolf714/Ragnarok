//Using SDL, SDL OpenGL, GLEW, and strings
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>

//Screen Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//starts up SDL, creates window, and initializes OpenGL
bool init();

//initializes rendering program and clear color
bool initGL();

//Input Handler
void handleKeys(unsigned char key, int x, int y);


void update();

void render();

void close();



//Shader loading utility programs
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);

//window
SDL_Window* gWindow = nullptr;
//open gl context
SDL_GLContext gContext;

bool gRenderQuad = true;


//Graphics Programs
GLuint gProgramID = 0;


bool init()
{
	bool success = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
	
	}
}

int main(int argc, char* argv[]) 
{


	return 0;
}