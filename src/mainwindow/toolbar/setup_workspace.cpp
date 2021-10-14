#include "setup_workspace.h"
#include "ui_setup_workspace.h"

SetUpWorkspace::SetUpWorkspace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUpWorkspace)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setFocusPolicy(Qt::ClickFocus);

    //插入事件过滤器
    ui->lineEdit_tabName->installEventFilter(this);
    ui->checkBox_showCounter->installEventFilter(this);
    ui->checkBox_syncSelection->installEventFilter(this);
    ui->checkBox_syncZoom->installEventFilter(this);
}

SetUpWorkspace::~SetUpWorkspace()
{
    delete ui;
}

void SetUpWorkspace::setdata(const QString &tab, bool showCounter, bool syncSelection, bool syncZoom)
{
    this->tabName = tab;
    this->showCounter = showCounter;
    this->syncSelection = syncSelection;
    this->syncZoom = syncZoom;

    ui->lineEdit_tabName->setText(this->tabName);
    ui->checkBox_showCounter->setChecked(this->showCounter);
    ui->checkBox_syncSelection->setChecked(this->syncSelection);
    ui->checkBox_syncZoom->setChecked(this->syncZoom);

    QDialog::update();
}

bool SetUpWorkspace::eventFilter(QObject *watched, QEvent *event) {
    if(event->type() == QEvent::FocusOut) {
        if(!hasFocus() && !ui->lineEdit_tabName->hasFocus() &&
                !ui->checkBox_showCounter->hasFocus() &&
                !ui->checkBox_syncSelection->hasFocus() &&
                !ui->checkBox_syncZoom->hasFocus()) {

            hide();
            if(ui->lineEdit_tabName->text() != tabName ||
                    ui->checkBox_showCounter->isChecked() != showCounter ||
                    ui->checkBox_syncSelection->isChecked() != syncSelection ||
                    ui->checkBox_syncZoom->isChecked() != syncZoom) {
                emit tabConfigChanged(ui->lineEdit_tabName->text(), ui->checkBox_showCounter->isChecked(),
                                      ui->checkBox_syncSelection->isChecked(), ui->checkBox_syncZoom->isChecked());
            }
        }
    }

    return false;
}

