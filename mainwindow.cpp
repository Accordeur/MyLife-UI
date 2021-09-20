#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_file/newfile_dialog.h"
#include "about_dialog.h"
#include <QToolBar>
#include <QToolButton>

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
    bar->addAction(ui->action_New_task);
    bar->addAction(ui->action_New_subtask);
    this->addToolBar(bar);
    setWindowIcon(QIcon(":/logo/fox"));
}

void MainWindow::on_action_About_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_New_triggered()
{
    NewFileDialog().exec();
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog().exec();
}
