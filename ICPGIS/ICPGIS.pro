QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 5){
QT += opengl
#QT += openglwidgets
}

LIBS += -lOpengl32 -lgdi32
CONFIG += c++11
CONFIG += utf8_source

DEFINES += QT_DEPRECATED_WARNINGS

win32{
DEFINES += NOMINMAX
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ICPGLWidget.cpp \
    main.cpp \
    ICPGIS.cpp

HEADERS += \
    ICPGIS.h \
    ICPGLContext.hpp \
    ICPGLWidget.h \
    ICPPlatform.hpp

FORMS += \
    ICPGIS.ui

INCLUDEPATH += $$PWD/libs/glew/include
LIBS += -L$$PWD/libs/glew/lib/Release/x64 -lglew32

