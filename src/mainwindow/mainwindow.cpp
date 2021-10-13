#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newfile_dialog.h"
#include "about_dialog.h"
#include "toolbar/toolbar.h"
#include "view_dock/viewdock.h"
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QTabBar>
#include <QLayout>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化用户配置
    config = Config::getConfig(":/config/default_config");
    Q_ASSERT(config->isValid());


    setupToolbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupToolbar() {
    QToolBar* bar = new QToolBar(this);
    bar->setAllowedAreas(Qt::TopToolBarArea);
    bar->setMovable(false);
    ToolBar* toolbar = new ToolBar(bar);
    bar->addWidget(toolbar);
    bar->layout()->setContentsMargins(0, 0, 0, 0);
    bar->layout()->setSpacing(0);
    bar->setStyleSheet("QToolBar {background-color:#E7E6E5; margin:0px; padding:0px; border:0px;}");
    this->addToolBar(bar);

    this->setContextMenuPolicy(Qt::NoContextMenu);

    auto viewDock = new ViewDock(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, viewDock);
}

void MainWindow::sorry() const
{
    QMessageBox::information(nullptr, tr("Sorry"), tr("Sorry, this feature is not implemented."), QMessageBox::Yes, QMessageBox::Yes);
}

void MainWindow::on_action_About_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_New_triggered()
{
    NewFileDialog newFile;
    //TODO: 处理打开自定义模板情况
    connect(&newFile, &NewFileDialog::selected_template_path, [](QString str){qDebug() << "Open file: " << str;});
    newFile.exec();
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog().exec();
}

void MainWindow::printChild(QObject* root, int blk) {
    if(root == nullptr) return;
    QObjectList child = root->children();
    for(auto& object: child) {
        for(int i=0;i<blk;i++)
            std::cout << "  ";
        QWidget* widget = qobject_cast<QWidget*>(object);
        std::cout  << "|- " <<object->metaObject()->className() << ": " << object->objectName().toStdString();
        if(widget) {
            //QPoint globalPoint = QWidget::mapToGlobal(qobject_cast<QWidget*>(object)->pos());
            QPoint globalPoint = widget->mapToGlobal(widget->pos());
            std::cout << "("
                << globalPoint.x() << ", "
                << globalPoint.y() << ", "
                << widget->size().width() << ", "
                << widget->size().height() << ")" << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
    for(auto& object: child) {
        printChild(object, blk+1);
    }
}

void MainWindow::on_action_Open_triggered()
{
    sorry();
}


void MainWindow::on_action_Reopen_triggered()
{
    sorry();
}


void MainWindow::on_action_Save_triggered()
{
    sorry();
}


void MainWindow::on_action_Save_as_triggered()
{
    sorry();
}


void MainWindow::on_action_Close_triggered()
{
    sorry();
}


void MainWindow::on_action_Import_triggered()
{
    sorry();
}


void MainWindow::on_action_Export_triggered()
{
    sorry();
}


void MainWindow::on_action_Archive_triggered()
{
    sorry();
}


void MainWindow::on_action_MyLife_website_triggered()
{
    sorry();
}


void MainWindow::on_action_Print_triggered()
{
    sorry();
}


void MainWindow::on_action_Print_PockeMod_triggered()
{
    sorry();
}


void MainWindow::on_action_Properrties_triggered()
{
    sorry();
}


void MainWindow::on_action_Undo_typing_triggered()
{
    sorry();
}


void MainWindow::on_action_Redo_typing_triggered()
{
    sorry();
}


void MainWindow::on_action_Search_triggered()
{
    sorry();
}


void MainWindow::on_action_Text_filter_triggered()
{
    sorry();
}


void MainWindow::on_action_Insert_Date_Time_triggered()
{
    sorry();
}


void MainWindow::on_action_Insert_Time_triggered()
{
    sorry();
}


void MainWindow::on_action_Insert_Date_triggered()
{
    sorry();
}


void MainWindow::on_action_Task_views_pane_triggered()
{
    sorry();
}


void MainWindow::on_action_Properties_pane_triggered()
{
    sorry();
}


void MainWindow::on_action_Toggle_Task_List_Task_Notes_triggered()
{
    sorry();
}


void MainWindow::on_action_Workspace_tabs_triggered()
{
    sorry();
}


void MainWindow::on_action_Toolbar_triggered()
{
    sorry();
}


void MainWindow::on_action_Full_screen_triggered()
{
    sorry();
}


void MainWindow::on_action_Reminders_window_triggered()
{
    sorry();
}


void MainWindow::on_action_Repid_task_entry_window_triggered()
{
    sorry();
}


void MainWindow::on_action_Open_in_new_window_triggered()
{
    sorry();
}


void MainWindow::on_action_Zoom_in_triggered()
{
    sorry();
}


void MainWindow::on_action_Zoom_out_triggered()
{
    sorry();
}


void MainWindow::on_action_Refresh_triggered()
{
    sorry();
}

