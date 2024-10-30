#include "ICPGLWidget.h"

ICPGLWidget::ICPGLWidget(QWidget* parent) : QWidget(parent, Qt::MSWindowsOwnDC)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(true);

    _context.init((HWND)winId(), GetDC((HWND)winId()));

    //glewInit();
    QObject::connect(&_renderTimer, SIGNAL(timeout()), this, SLOT(render()));
    _renderTimer.setInterval(16);
    _renderTimer.start();
}

ICPGLWidget::~ICPGLWidget()
{
    _context.shutdown();
}


void ICPGLWidget::render()
{
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _context.swapBuffer();
}
