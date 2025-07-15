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

//Update function
void update();

//Renders quad to the screen
void render();

//frees media and shuts down sdl
void close();



//Shader loading utility programs
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);

//window
SDL_Window* gWindow = nullptr;
//open gl context
SDL_GLContext gContext;

//Render Flag
bool gRenderQuad = true;


//Graphics Programs
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;


bool init()
{
	bool success = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError);
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		//Create Window
		gWindow = SDL_CreateWindow("Ragnarok Engine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (gWindow == NULL)
		{
			SDL_Log("Window coult not be created! SDL Error: %s\n", SDL_GetError);
		}
		else 
		{
			//create Context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					SDL_Log("Error initializing GLEW! %s\n", glewGetErrorString(glewError));

				}

				//Use VSynce
				if (!SDL_GL_SetSwapInterval(1))
				{
					SDL_Log("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//initialize OpenGL
				if (!initGL())
				{
					SDL_Log("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}

	}
	return success;

}

bool initGL()
{
	//Sucess flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex sourve
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//compile vertex

	glCompileShader(vertexShader);

	//check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;

	}
	else
	{
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);

		//create fragment shader to program
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		//set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		//compile fragment source
		glCompileShader (fragmentShader);

		//check fragment shader for errors 
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!/n", fragmentShader);
			printShaderLog(fragmentShader);
			success = true;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);

			//link program
			glLinkProgram(gProgramID);

			 //Check errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{
				//Get Vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if(gVertexPos2DLocation == -1)
				{
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else
				{
					//initalize clear color
					glClearColor(0.f, 0.f, 0.f, 1.f);

					//VBO data
					GLfloat vertexData[] =
					{
						 -0.5f, -0.5f,
						 0.5f, -0.5f,
						 0.5f,  0.5f,
						-0.5f,  0.5f
					};

					//IBO Data
					GLuint indexData[] = { 0,1,2,3 };

					//create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

					//create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
				}
			}


		}
	}
	return success;
}

void printProgramLog()
{

}

int main(int argc, char* argv[]) 
{


	return 0;
}