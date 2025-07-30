#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Renderer::Renderer() 
{

}

Renderer::~Renderer() {
}

//Renders the screen
void Renderer::Render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawTile();

	

}

//sets up tile and shader program using open gl
void Renderer::SetUpTile()
{
    if (tileInitialized) return;

    // Generate program, compile and link shaders (load from files or use the above strings)
	gProgramID = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    //Get vertex source
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\n"
        "uniform mat4 uMVP;"
        "in vec3 LVertexPos3D;"
        "void main() {"
        "   gl_Position = uMVP * vec4(LVertexPos3D, 1.0);"
        "}"
    };


    //Set vertex source
   glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

    //Compile vertex source
    glCompileShader(vertexShader);

    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE)
    {
        SDL_Log("Unable to compile vertex shader %d!\n", vertexShader);
        printShaderLog(vertexShader);
        
    }
    else
    {
        //Attach vertex shader to program
        glAttachShader(gProgramID, vertexShader);

        //Create fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        //Get fragment source
        const GLchar* fragmentShaderSource[] =
        {
            "#version 140\n"
            "out vec4 LFragment;"
            "void main() {"
            "   LFragment = vec4(1.0, 1.0, 1.0, 1.0);"
            "}"
        };

        //Set fragment source
        glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

        //Compile fragment source
        glCompileShader(fragmentShader);

        //Check fragment shader for errors
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
        if (fShaderCompiled != GL_TRUE)
        {
            SDL_Log("Unable to compile fragment shader %d!\n", fragmentShader);
            printShaderLog(fragmentShader);
        }
        else
        {
            //Attach fragment shader to program
            glAttachShader(gProgramID, fragmentShader);

            //Link program
            glLinkProgram(gProgramID);

            //Check for errors
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
            if (programSuccess != GL_TRUE)
            {
                SDL_Log("Error linking program %d!\n", gProgramID);
                printProgramLog(gProgramID);
            }
            else
            {
                gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos3D");
                if (gVertexPos2DLocation == -1) {
                    SDL_Log("LVertexPos3D is not a valid glsl program variable!\n");
                    return;
                }

                // VBO data (unit quad)
                GLfloat vertexData[] = {
                    -0.5f, -0.5f, 0.0f, // bottom left
                     0.5f, -0.5f, 0.0f, // bottom right
                     0.5f,  0.5f, 0.0f, // top right
                    -0.5f,  0.5f, 0.0f  // top left
                };
                GLuint indexData[] = { 0, 1, 2, 3 };

                glGenBuffers(1, &gVBO);
                glBindBuffer(GL_ARRAY_BUFFER, gVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

                glGenBuffers(1, &gIBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

                tileInitialized = true;
            }
        }
    }

}
//don't exactly know what it does
bool Renderer::Initialize()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // If you have nothing else to initialize, just return true
    return true;

    
}

//draws an isometric tile on the screen
void Renderer::DrawTile()
{
    SetUpTile();

    //sets up orthographic projection
    glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -10.0f, 10.0f);
    //sets camera position
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.577f, 0.577f, 0.577f), // isometric camera position
        glm::vec3(0.0f, 0.0f, 0.0f),       // look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)        // up vector
    );
    //Rotates the tile for iso view
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0,0,1));
    model = glm::rotate(model, glm::radians(35.264f), glm::vec3(1,0,0));
    glm::mat4 mvp = proj * view * model;

    // --- Use shader program and set uniform ---
    glUseProgram(gProgramID);
    GLint mvpLoc = glGetUniformLocation(gProgramID, "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

    // --- Bind VBO/IBO and set up attribute ---
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glEnableVertexAttribArray(gVertexPos2DLocation);
    glVertexAttribPointer(gVertexPos2DLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(gVertexPos2DLocation);
    glUseProgram(0);
}

//shader log
void Renderer::printShaderLog(GLuint shader)
{
    //Make sure name is shader
    if (glIsShader(shader))
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0)
        {
            //Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a shader\n", shader);
    }
}
//program logs
void Renderer::printProgramLog(GLuint program)
{
    //Make sure name is shader
    if (glIsProgram(program))
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0)
        {
            //Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a program\n", program);
    }
}