#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printChild(QObject* root, int blk = 0);

private slots:
    void on_action_About_Qt_triggered();
    void on_action_New_triggered();
    void on_action_Exit_triggered();
    void on_action_About_triggered();

private:
    void setupToolbar();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H