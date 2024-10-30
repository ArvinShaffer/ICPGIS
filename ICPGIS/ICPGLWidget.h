#ifndef ICPGLWIDGET_H
#define ICPGLWIDGET_H
#include<QtWidgets/QWidget>
#include<QTimer>
#include"ICPGLContext.hpp"

class ICPGLWidget : public QWidget
{
    Q_OBJECT
protected:
    ICP::ICPGLContext _context;
    QTimer _renderTimer;
public:
    ICPGLWidget(QWidget* parent = 0);
    virtual ~ICPGLWidget();

public Q_SLOTS:
    virtual void render();
};

#endif // ICPGLWIDGET_H
