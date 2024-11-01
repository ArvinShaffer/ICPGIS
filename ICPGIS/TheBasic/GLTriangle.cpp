#include "GLTriangle.h"
#include <QDebug>

GLTriangle::GLTriangle(QWidget *parent) : QOpenGLWidget(parent) {}

GLTriangle::~GLTriangle()
{
    // initializeGL Called only when displaying, releasing uninitialized will result in an exception
    if (!isValid())
        return;
    //QOpenGLWidget
    //The three virtual functions do not require makeCurrent, the corresponding operations have been completed by the framework
    //But the current context needs to be set when releasing
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    doneCurrent();
}

void GLTriangle::initializeGL()
{
    // QOpenGLFunctions
    // Initializes OpenGL function parsing for the current context
    initializeOpenGLFunctions();
    // Shader code
    // Uniform sent from CPU to GPU
    const char *vertex_str=R"(#version 450
layout (location = 0) in vec3 vertices;
void main() {
gl_Position = vec4(vertices, 1.0);
})";
    const char *fragment_str = R"(#version 450
uniform vec3 myColor;
out vec4 fragColor;
void main() {
fragColor = vec4(myColor, 1.0);
})";
    // Vertex Shader
    //GLuint glCreateShader(GLenum shaderType);
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // Set the code in the shader object
    // void glShderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
    // Parameter 1 specifies the shader object
    // Parameter 2 specifies the number of strings
    // Parameter 3 specifies the pointer to a 2D string array
    // Parameter 4 specifies the string length array, if NULL, '\0' is used as the string terminator
    glShaderSource(vertex_shader, 1, &vertex_str, NULL);
    // Compiling shader objects
    // void glCompileShader(GLuint shader);
    glCompileShader(vertex_shader);
    //Check if the shader is abnormal
    checkShaderError(vertex_shader, "vertex");

    // Fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_str, NULL);
    glCompileShader(fragment_shader);
    checkShaderError(fragment_shader, "fragment");
    // Shader Program
    // Creates an empty program object and returns a non-zero value that can be referenced
    // GLuint glCreateProgram(void);
    shaderProgram = glCreateProgram();
    // Attaches the shader object to the program object
    //void glAttachShder(GLuint program, GLuint shader);
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    // Links the program object
    // void glLinkProgram(GLuint program);
    glLinkProgram(shaderProgram);
    checkShaderError(shaderProgram, "program");
    // Delete the shaders, they are already linked to our shader program object
    //void glDeleteShader(GLuint shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // The three vertices of the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f, // top
    };
    //[1]On August 12, 2014, Khronos released the OpenGL 4.5 standard specification,
    //Among them, the ARB_direct_state_access extension entered the core,
    //It allows direct access and modification of OpenGL objects without binding OpenGL objects (bind operation, such as glBindBuffer),
    //Improving the efficiency of applications and middleware.
    //[2]The id generated by the glGen* series of functions does not initialize the state of the object internally. It will only be initialized when glBind* is called.
    //And Core/ARB's DSA directly provides the glCreate* series of functions, which can create ids and initialize in one step.

    //Generate vertex array objects
    //void glCreateVertexArrays(GLsizei n, GLuint *arrays);
    glCreateVertexArrays(1, &vao);
    //Generate buffer object
    //void glCreateBuffers(GLsizei n, GLuint *buffers);
    glCreateBuffers(1, &vbo);
    //Allocate size storage units to store data or index
    //glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfielf flags);
    //Parameter 1 buffer object
    //Parameter 2 data block size
    //Parameter 3 if NULL is size initialized data, otherwise initialize with data copy
    //Parameter 4 data related purposes
    glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
    // vbo binds to vao
    //glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
    //Parameter 1 vertex array object
    //Parameter 2 index of vbo in vao
    //Parameter 3 vertex buffer object
    //Parameter 4 offset of the first element of the buffer
    //Parameter 5 vertex stepping of the buffer, 3 floats per point of a triangle
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3*sizeof(float));
    //Enable index index of the general vertex attribute array, corresponding to layout location
    //glEnableVertexArrayAttrib(GLuint vaobj, GLuint index);
    glEnableVertexArrayAttrib(vao, 0);
    //Specify the organization of the vertex array
    //glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
    //Parameter 1 vertex array object
    //Parameter 2 general vertex attribute array, corresponding to layout location
    //Parameter 3 several data per vertex
    //Parameter 4 storage type
    //Parameter 5 whether to normalize
    //Parameter 6 vertex stepping
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    //Associate vertex attribute attributes and vertex buffer bindings
    //glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
    //Parameter 1 vertex array object
    //Parameter 2 attribute attribute index, corresponding to layout location
    //Parameter 3 vbo index in vao
    glVertexArrayAttribBinding(vao, 0, 0);
}

void GLTriangle::paintGL()
{
    //Clear screen settings
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Install the specified program object program as part of the current rendering state
    glUseProgram(shaderProgram);
    //Pass values
    glUniform3f(glGetUniformLocation(shaderProgram, "myColor"), 1.0f, 0.0f, 0.0f);
    //Bind array objects
    glBindVertexArray(vao);
    //Use the currently activated shader and vertex attribute configuration and VBO (indirectly bound through VAO) to draw primitives
    //void glDrawArrays(GLenum mode​, GLint first​, GLsizei count​);
    //Parameter 1 is the primitive type
    //Parameter 2 specifies the starting index of the vertex array
    //Parameter 3 specifies the number of vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLTriangle::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLTriangle::checkShaderError(GLuint id, const QString &type)
{
    int check_flag;
    char check_info[1024];
    if(type != "program") {
        glGetShaderiv(id, GL_COMPILE_STATUS, &check_flag);
        if(!check_flag) {
            glGetShaderInfoLog(id, 1024, NULL, check_info);
            qDebug() << type << " error:" << check_info;
        }
    } else {
        glGetShaderiv(id, GL_LINK_STATUS, &check_flag);
        if(!check_flag) {
            glGetProgramInfoLog(id, 1024, NULL, check_info);
            qDebug() << type << " error:" << check_info;
        }
    }
}
