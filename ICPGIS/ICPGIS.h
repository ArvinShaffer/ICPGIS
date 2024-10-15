#ifndef ICPGIS_H
#define ICPGIS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ICPGIS;
}
QT_END_NAMESPACE

class ICPGIS : public QMainWindow
{
    Q_OBJECT

public:
    ICPGIS(QWidget *parent = nullptr);
    ~ICPGIS();

private:
    Ui::ICPGIS *ui;
};
#endif // ICPGIS_H
