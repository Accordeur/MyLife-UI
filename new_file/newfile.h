#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>

class QMenu;
namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = nullptr);
    ~NewFile();

private:
    void setupNewFileMenu();
    void setupSelectTemplateMenu();

    Ui::NewFile *ui;
    QMenu* menu_select_template;
    QMenu* menu_new_file;
};

#endif // NEWFILE_H
