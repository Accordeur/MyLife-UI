#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class NewFile;
class About;
class CentralWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_About_Qt_triggered();
    void on_action_New_triggered();
    void on_action_Exit_triggered();
    void on_action_About_triggered();

private:
    void setupToolbar();
    Ui::MainWindow *ui;
    NewFile* new_file_dialog;
    About* about_dialog;
    CentralWidget* central_widget;
};
#endif // MAINWINDOW_H
