#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

private slots:
    void setAddTabButtonVisible(bool visible);
private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR_H
