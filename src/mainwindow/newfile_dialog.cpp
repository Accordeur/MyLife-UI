#include "newfile_dialog.h"
#include "ui_newfile_dialog.h"
#include <QListView>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog), menu_select_template(new QMenu(this)), menu_new_file(new QMenu(this))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setupSelectTemplateMenu();
    setupNewFileMenu();
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}


void NewFileDialog::setupNewFileMenu() {
    menu_new_file->addAction(ui->action_Create_blank_data_file);
    menu_new_file->addAction(ui->action_Create_blank_data_file_with_default);
    ui->toolButton_New_file->setMenu(menu_new_file);
}
void NewFileDialog::setupSelectTemplateMenu() {
    menu_select_template->addAction(ui->action_Traditional_FranklinCovey);
    menu_select_template->addAction(ui->action_Do_It_Tomorrow);
    menu_select_template->addAction(ui->action_Getting_Things_Done_Beginners_Action);
    menu_select_template->addAction(ui->action_Getting_Things_Done_Zones_of_Focus);
    menu_select_template->addAction(ui->action_Getting_Things_Done_Zones_of_Focusd_Action);
    menu_select_template->addAction(ui->action_Getting_Things_Done_with_FranklinCovey_Roles);
    menu_select_template->addAction(ui->action_FlyLady_Control_Journal);
    menu_select_template->addSeparator();
    menu_select_template->addAction(ui->action_MyLife_Demo_File);
    menu_select_template->addSeparator();
    menu_select_template->addAction(ui->action_More_Templates);
    ui->toolButton_Select_templates->setMenu(menu_select_template);
}


void NewFileDialog::on_action_More_Templates_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString(),
                                                    QString(),
                                                    tr("MyLife Template(*.mlt)"));

    if(!fileName.isEmpty()) {
        emit selected_template_path(fileName);
        close();
    }
}

