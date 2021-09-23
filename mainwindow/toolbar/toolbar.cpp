#include "toolbar.h"
#include "ui_toolbar.h"

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

}

ToolBar::~ToolBar()
{
    delete ui;
}
