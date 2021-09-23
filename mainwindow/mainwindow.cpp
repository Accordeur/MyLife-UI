#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newfile_dialog.h"
#include "about_dialog.h"
#include "toolbar/toolbar.h"
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QTabBar>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    bar->layout()->setMargin(0);
    bar->layout()->setSpacing(0);
    bar->setStyleSheet("QToolBar {background-color: #E7E6E5;}");
    this->addToolBar(bar);

    this->setContextMenuPolicy(Qt::NoContextMenu);

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
