#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_file/newfile.h"
#include "about.h"
#include <QToolBar>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      new_file_dialog(new NewFile(this)),
      about_dialog(new About(this))
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
}

void MainWindow::on_action_About_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_New_triggered()
{
    new_file_dialog->show();
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_action_About_triggered()
{
    about_dialog->show();
}
