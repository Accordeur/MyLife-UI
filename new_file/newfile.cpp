#include "newfile.h"
#include "ui_newfile.h"
#include <QListView>

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    int max_len=0;
    for(int idx=0;idx < ui->comboBox_template->count();idx++)
    {
        if(max_len < ui->comboBox_template->itemText(idx).length())
            max_len = ui->comboBox_template->itemText(idx).length();
    }

    int pt_val = this->font().pointSize();//获取字体的磅值
    dynamic_cast<QWidget*>(ui->comboBox_template->view())->setFixedWidth(max_len*pt_val*0.8);//（字符数*每个字符的宽度(磅)*0.75）个像素
}

NewFile::~NewFile()
{
    delete ui;
}
