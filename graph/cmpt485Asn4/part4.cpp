// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>

int main( void )
{
    
    
    
    /**********************************/
    /*** APPLICATION INITIALIZATION ***/
    /**********************************/
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "CMPT 485", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    // Initialize mouse callbacks
    initializeMouseCallbacks();
    
    
    /**********************************/
    /***** OPENGL INITIALIZATION ******/
    /**********************************/
    
    
    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
    // Use our shader
    glUseProgram(programID);
    
    // Get a handle for our "MVP" uniform
    GLuint ViewProjectionMatrixID = glGetUniformLocation(programID, "VP");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    
    // Initialize GLFW control callbacks
    initializeMouseCallbacks();
    
    // Projection and Model matrices are fixed
    //glm::mat4 ProjectionMatrix = getProjectionMatrix();
    
    /**********************************/
    /**** LOAD MODEL INFORMATION ******/
    /**********************************/
    
    std::vector<Model> models;
    loadModels("default.models", models);
    Model model = models[0]; // for now just take the first model in the file
    Model model1 = models[1];
    Model model2 = models[2];
    Model model3 = models[3];
    
    GLuint Texture = loadBMP_custom(model.textureFilename.c_str());
    GLuint Texture1 = loadBMP_custom(model1.textureFilename.c_str());
    GLuint Texture2 = loadBMP_custom(model2.textureFilename.c_str());
    GLuint Texture3 = loadBMP_custom(model3.textureFilename.c_str());
    
    GLuint TextureID = glGetUniformLocation(programID,"myTextureSampler");
    
    /**********************************/
    /*** SET MODEL MATRIX FROM INFO ***/
    /**********************************/
    
    //object0
    glm::mat4 I = glm::mat4(1.0f); // Identity Matrix
    glm::mat4 Ms = glm::scale(I, glm::vec3(model.sx, model.sy, model.sz));
    glm::mat4 Mr = glm::rotate(I, model.ra,glm::vec3(model.rx, model.ry, model.rz));
    glm::mat4 Mt = glm::translate(I, glm::vec3(model.tx, model.ty, model.tz));
    //glm::mat4 Mminust = glm::translate(I, glm::vec3(-model.tx, -model.ty, -model.tz));
    glm::mat4 ModelMatrix = Mt * Mr * Ms;
    
    //object1
    glm::mat4 I1 = glm::mat4(1.0f); // Identity Matrix
    glm::mat4 Ms1 = glm::scale(I1, glm::vec3(model1.sx, model1.sy, model1.sz));
    glm::mat4 Mr1 = glm::rotate(I1, model1.ra,glm::vec3(model1.rx, model1.ry, model1.rz));
    glm::mat4 Mt1 = glm::translate(I1, glm::vec3(model1.tx, model1.ty, model1.tz));
    glm::mat4 ModelMatrix1 = Mt1 * Mr1 * Ms1;
    
    //object2
    glm::mat4 I2 = glm::mat4(1.0f); // Identity Matrix
    glm::mat4 Ms2 = glm::scale(I2, glm::vec3(model2.sx, model2.sy, model2.sz));
    glm::mat4 Mr2 = glm::rotate(I2, model2.ra,glm::vec3(model2.rx, model2.ry, model2.rz));
    glm::mat4 Mt2 = glm::translate(I2, glm::vec3(model2.tx, model2.ty, model2.tz));
    glm::mat4 ModelMatrix2 = Mt2 * Mr2 * Ms2;
    
    //object3
    glm::mat4 I3 = glm::mat4(1.0f); // Identity Matrix
    glm::mat4 Ms3 = glm::scale(I3, glm::vec3(model3.sx, model3.sy, model3.sz));
    glm::mat4 Mr3 = glm::rotate(I3, model3.ra,glm::vec3(model3.rx, model3.ry, model3.rz));
    glm::mat4 Mt3 = glm::translate(I3, glm::vec3(model3.tx, model3.ty, model3.tz));
    glm::mat4 ModelMatrix3 = Mt3 * Mr3 * Ms3;
    
    
    
    
    /**********************************/
    /* CREATE VERTEX-ATTRIBUTE ARRAYS */
    /**********************************/
    
    // Read our .obj0 file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    //std::vector<glm::ivec3> vertex_indices;
    //std::vector<glm::ivec3> uv_indices;
    //std::vector<glm::ivec3> normal_indices;
    
    bool loadSuccess = loadOBJ(model.objFilename.c_str(), vertices, uvs, normals);
    if (!loadSuccess) {
        return -1;
    }
    
    // Read our .obj1 file
    std::vector<glm::vec3> vertices1;
    std::vector<glm::vec2> uvs1;
    std::vector<glm::vec3> normals1;
    //std::vector<glm::ivec3> vertex_indices;
    //std::vector<glm::ivec3> uv_indices;
    //std::vector<glm::ivec3> normal_indices;
    
    bool loadSuccess1 = loadOBJ(model1.objFilename.c_str(), vertices1, uvs1, normals1);
    if (!loadSuccess1) {
        return -1;
    }
    
    // Read our .obj2 file
    std::vector<glm::vec3> vertices2;
    std::vector<glm::vec2> uvs2;
    std::vector<glm::vec3> normals2;
    //std::vector<glm::ivec3> vertex_indices;
    //std::vector<glm::ivec3> uv_indices;
    //std::vector<glm::ivec3> normal_indices;
    
    bool loadSuccess2 = loadOBJ(model2.objFilename.c_str(), vertices2, uvs2, normals2);
    if (!loadSuccess2) {
        return -1;
    }
    
    // Read our .obj3 file
    std::vector<glm::vec3> vertices3;
    std::vector<glm::vec2> uvs3;
    std::vector<glm::vec3> normals3;
    //std::vector<glm::ivec3> vertex_indices;
    //std::vector<glm::ivec3> uv_indices;
    //std::vector<glm::ivec3> normal_indices;
    
    bool loadSuccess3 = loadOBJ(model3.objFilename.c_str(), vertices3, uvs3, normals3);
    if (!loadSuccess3) {
        return -1;
    }
    
    // need to keep track of vbo sizes for drawing later
    GLsizei numVertices = vertices.size(); // should be same as numNormals
    GLsizei numVertices1 = vertices1.size();
    GLsizei numVertices2 = vertices2.size();
    GLsizei numVertices3 = vertices3.size();
    
    
    
    //GLsizei numVertexIndices = vertex_indices.size();
    
    
    /**********************************/
    /** CREATE VERTEX-BUFFER OBJECTS **/
    /**********************************/
    
    /**********************************/
    /***** BIND VERTEX-ARRAY OBJECT ***/
    /**********************************/
    
    /********************************************/
    /*** ASSOCIATE DATA WITH SHADER VARIABLES ***/
    /********************************************/
    
    //bind VAO for obj0
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    glBindVertexArray(0);
    
    
    
    //bind VAO for obj1
    GLuint vertexbuffer1;
    glGenBuffers(1, &vertexbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glBufferData(GL_ARRAY_BUFFER, numVertices1 * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer1;
    glGenBuffers(1, &uvbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
    glBufferData(GL_ARRAY_BUFFER, uvs1.size() * sizeof(glm::vec2), &uvs1[0], GL_STATIC_DRAW);
    
    GLuint VertexArrayID1;
    glGenVertexArrays(1, &VertexArrayID1);
    glBindVertexArray(VertexArrayID1);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    glBindVertexArray(0);
    /**********************************/
    /*** UNBIND VERTEX-ARRAY OBJECT ***/
    /**********************************/
    
    
    //bind VAO for obj2
    GLuint vertexbuffer2;
    glGenBuffers(1, &vertexbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
    glBufferData(GL_ARRAY_BUFFER, numVertices2 * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer2;
    glGenBuffers(1, &uvbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
    glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);
    
    GLuint VertexArrayID2;
    glGenVertexArrays(1, &VertexArrayID2);
    glBindVertexArray(VertexArrayID2);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    glBindVertexArray(0);
    
    
    
    
    //bind VAO for obj3
    GLuint vertexbuffer3;
    glGenBuffers(1, &vertexbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
    glBufferData(GL_ARRAY_BUFFER, numVertices3 * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer3;
    glGenBuffers(1, &uvbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
    glBufferData(GL_ARRAY_BUFFER, uvs3.size() * sizeof(glm::vec2), &uvs3[0], GL_STATIC_DRAW);
    
    GLuint VertexArrayID3;
    glGenVertexArrays(1, &VertexArrayID3);
    glBindVertexArray(VertexArrayID3);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          2,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    glBindVertexArray(0);
    
    do{
        
        // get updated View matrix from keyboard and mouse input
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        //glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 VP = ProjectionMatrix * ViewMatrix;
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(ViewProjectionMatrixID, 1, GL_FALSE, &VP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        
        
        
        /**********************************/
        /************** DRAW  *************/
        /**********************************/
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //draw obj0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glUniform1i(TextureID, 0);
        glBindVertexArray(VertexArrayID);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        
        
        
        //draw obj1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glUniform1i(TextureID, 1);
        glBindVertexArray(VertexArrayID1);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, numVertices1);
        
        
        ///draw obj2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        glUniform1i(TextureID, 2);
        glBindVertexArray(VertexArrayID2);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, numVertices2);
        
        
        //draw obj3
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, Texture3);
        glUniform1i(TextureID, 3);
        glBindVertexArray(VertexArrayID3);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);

    
        // Unbind VAO
        glBindVertexArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    //glDeleteBuffers(1, &normalsbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &vertexbuffer1);
    glDeleteBuffers(1, &uvbuffer1);
    glDeleteBuffers(1, &vertexbuffer2);
    glDeleteBuffers(1, &uvbuffer2);
    glDeleteBuffers(1, &vertexbuffer3);
    glDeleteBuffers(1, &uvbuffer3);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteVertexArrays(1, &VertexArrayID1);
    glDeleteVertexArrays(1, &VertexArrayID2);
    glDeleteVertexArrays(1, &VertexArrayID3);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

