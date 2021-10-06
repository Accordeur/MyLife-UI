#include "viewdock.h"
#include "ui_viewdock.h"
#include <QLayout>

ViewDock::ViewDock(QWidget *parent) :
    QDockWidget(parent/*, Qt::Window | Qt::CustomizeWindowHint*/),
    ui(new Ui::ViewDock)
{
    ui->setupUi(this);
    setTitleBarWidget(new QWidget(this));
    for (int i = 0; i < ui->toolBox->count(); i++){
        ui->toolBox->setItemIcon( i, QIcon(":/only/placeholder"));
    }
}

ViewDock::~ViewDock()
{
    delete ui;
}
