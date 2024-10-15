#include "ICPGIS.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOffscreenSurface>
#include <QDebug>

bool parseOpenGLVersion(const QByteArray &versionString, int &major, int &minor)
{
    bool majorOk = false;
    bool minorOk = false;
    QList<QByteArray> parts = versionString.split(' ');
    if (versionString.startsWith(QByteArrayLiteral("OpenGL ES"))) {
        if (parts.size() >= 3) {
            QList<QByteArray> versionParts = parts.at(2).split('.');
            if (versionParts.size() >= 2) {
                major = versionParts.at(0).toInt(&majorOk);
                minor = versionParts.at(1).toInt(&minorOk);
                if (!minorOk)
                    if (int idx = versionParts.at(1).indexOf('V'))
                        minor = versionParts.at(1).left(idx).toInt(&minorOk);
            } else {
                qWarning("Unrecognized OpenGL ES version");
            }
        } else {
            qWarning("Unrecoginzed OpenGL ES version");
        }
    } else {
        QList<QByteArray> versionParts = parts.at(0).split('.');
        if (versionParts.size() >= 2) {
            major = versionParts.at(0).toInt(&majorOk);
            minor = versionParts.at(1).toInt(&minorOk);
        } else {
            qWarning("Unrecognized OpenGL version");
        }
    }

    if (!majorOk || !minorOk)
        qWarning("Unrecognized OpenGL version");
    return (majorOk && minorOk);
}

bool checkVersion(int minMajor, int minMinor)
{
    int major = 0;
    int minor = 0;
    QScreen *screen = qApp->primaryScreen();
    if (screen) {
        QOffscreenSurface surface(screen);
        surface.create();
        QOpenGLContext context;
        context.create();
        context.makeCurrent(&surface);
        const GLubyte *glstr = context.functions()->glGetString(GL_VERSION);
        if (glstr) {
            QByteArray bytestr = QByteArray(reinterpret_cast<const char*>(glstr));
            qDebug() << "glGetString" << bytestr;
            if (!parseOpenGLVersion(bytestr, major, minor)) {
                major = 0;
                minor = 0;
            }
        }
        context.doneCurrent();
        surface.destroy();
    }
    qDebug() << "Native OpenGL version:" << major << minor;
    return (major*10 + minor >= minMajor*10 + minMinor);
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);

    qDebug() << "Need OpenGL 4.5 desktop context";
    if(!checkVersion(4,5))
        return -1;

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    // After setting up Qt6, a black window is displayed, or the tab is switched and the crash occurs
    QsurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    fmt.setVersion(4, 5);
    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    //fmt.setSamples(8);  // Multiple sampling
    QSurfaceFormat::setDefaultFormat(fmt);
#endif

    ICPGIS w;
    w.show();
    return a.exec();
}






