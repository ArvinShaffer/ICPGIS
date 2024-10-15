#include "ICPGIS.h"
#include "ui_ICPGIS.h"

ICPGIS::ICPGIS(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ICPGIS)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

ICPGIS::~ICPGIS()
{
    delete ui;
}
