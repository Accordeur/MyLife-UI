#include "toolbar.h"
#include "ui_toolbar.h"
#include <QDebug>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    ui->toolButton_New_Task->addAction(ui->action_New_Subtask);
    ui->toolButton_New_Task->addAction(ui->action_New_Folder);
    ui->toolButton_New_Task->addAction(ui->action_New_Project);
    ui->toolButton_New_Task->addAction(ui->action_New_From_Template);
    ui->toolButton_More->addAction(ui->action_Workspace_Tabs);
    ui->toolButton_More->addAction(ui->action_Toolbar);

    ui->pushButton_Add_Tab->setVisible(false);
    //QObject::connect(ui->tabBar, SIGNAL(tabIsTooLong(bool)), this, SLOT(setAddTabButtonVisible(bool)));
}

ToolBar::~ToolBar()
{
    delete ui;
}

void ToolBar::setAddTabButtonVisible(bool visible) {
    ui->pushButton_Add_Tab->setVisible(visible);
}
