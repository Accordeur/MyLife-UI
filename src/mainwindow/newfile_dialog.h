#ifndef NEWFILE_DIALOG_H
#define NEWFILE_DIALOG_H

#include <QDialog>

class QMenu;
class QEvent;

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = nullptr);
    ~NewFileDialog();
signals:
    void selected_template_path(QString path);

private slots:
    void on_action_More_Templates_triggered();

private:
    void setupNewFileMenu();
    void setupSelectTemplateMenu();

    Ui::NewFileDialog *ui;
    QMenu* menu_select_template;
    QMenu* menu_new_file;
};

#endif // NEWFILE_DIALOG_H
