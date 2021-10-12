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

    void on_action_Open_triggered();

    void on_action_Reopen_triggered();

    void on_action_Save_triggered();

    void on_action_Save_as_triggered();

    void on_action_Close_triggered();

    void on_action_Import_triggered();

    void on_action_Export_triggered();

    void on_action_Archive_triggered();

    void on_action_MyLife_website_triggered();

    void on_action_Print_triggered();

    void on_action_Print_PockeMod_triggered();

    void on_action_Properrties_triggered();

    void on_action_Undo_typing_triggered();

    void on_action_Redo_typing_triggered();

    void on_action_Search_triggered();

    void on_action_Text_filter_triggered();

    void on_action_Insert_Date_Time_triggered();

    void on_action_Insert_Time_triggered();

    void on_action_Insert_Date_triggered();

    void on_action_Task_views_pane_triggered();

    void on_action_Properties_pane_triggered();

    void on_action_Toggle_Task_List_Task_Notes_triggered();

    void on_action_Workspace_tabs_triggered();

    void on_action_Toolbar_triggered();

    void on_action_Full_screen_triggered();

    void on_action_Reminders_window_triggered();

    void on_action_Repid_task_entry_window_triggered();

    void on_action_Open_in_new_window_triggered();

    void on_action_Zoom_in_triggered();

    void on_action_Zoom_out_triggered();

    void on_action_Refresh_triggered();

private:
    void setupToolbar();

    void sorry() const;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
