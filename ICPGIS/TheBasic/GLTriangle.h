#ifndef GLTRIANGLE_H
#define GLTRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Compatibility>

class GLTriangle : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Compatibility
{
public:
    explicit GLTriangle(QWidget *parent = nullptr);
    ~GLTriangle();

protected:
    //After inheriting QOpenGLWidget, rewrite these three virtual functions
    //Sets OpenGL resources and state, called once before the first call to resizeGL or paintGL
    void initializeGL() override;
    //Renders the OpenGL scene, used whenever a widget needs to be updated
    void paintGL() override;
    //Set the OpenGL viewport, projection, etc., called whenever the size changes
    void resizeGL(int width, int height) override;

private:
    void checkShaderError(GLuint id, const QString &type);
    GLuint shaderProgram { 0 };
    GLuint vao { 0 };
    GLuint vbo { 0 };
};

#endif // GLTRIANGLE_H
