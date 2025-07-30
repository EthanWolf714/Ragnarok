#pragma once  
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include "Texture.h"

class Renderer  
{  
public:  

    Renderer(); // <-- Add this line
    ~Renderer(); // <-- And this line
    

    bool Initialize();  
    void Render();  
	void DrawSprite(const Texture& texture, const glm::vec2& position);
	void DrawTile();
    static glm::vec2 WorldToScreen(float worldX, float worldY);
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
private:
    //Graphics program
    GLuint gProgramID = 0;
    GLint gVertexPos2DLocation = -1;
    GLuint gVBO = 0;
    GLuint gIBO = 0;
    void SetUpTile();
    bool tileInitialized = false;
    float rotation = 0.0f;
   
};
