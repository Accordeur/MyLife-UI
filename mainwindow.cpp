#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "new_file/newfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      dialog(new NewFile(this))
{
    ui->setupUi(this);
    QObject::connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(new_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::new_file() {
     dialog->show();
}
