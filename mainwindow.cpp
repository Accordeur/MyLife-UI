#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_file/newfile.h"
#include <QToolBar>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dialog(new NewFile(this))
{
    ui->setupUi(this);
    setupToolbar();
    QObject::connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(new_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::new_file() {
     dialog->show();
}

void MainWindow::setupToolbar() {
    QToolBar* bar = new QToolBar(this);
    bar->setAllowedAreas(Qt::TopToolBarArea);
    bar->setMovable(false);
    bar->addAction(ui->action_New_task);
    bar->addAction(ui->action_New_subtask);
    this->addToolBar(bar);
}
