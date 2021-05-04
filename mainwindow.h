#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class NewFile;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void new_file();
private:
    void setupToolbar();
    Ui::MainWindow *ui;
    NewFile* dialog;
};
#endif // MAINWINDOW_H
