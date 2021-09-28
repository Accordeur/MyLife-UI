#include "viewdock.h"
#include "ui_viewdock.h"

ViewDock::ViewDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ViewDock)
{
    ui->setupUi(this);
    //titleBarWidget()->setContentsMargins(0, 0, 0, 0);
}

ViewDock::~ViewDock()
{
    delete ui;
}
