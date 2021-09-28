#ifndef VIEWDOCK_H
#define VIEWDOCK_H

#include <QDockWidget>

namespace Ui {
class ViewDock;
}

class ViewDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit ViewDock(QWidget *parent = nullptr);
    ~ViewDock();

private:
    Ui::ViewDock *ui;
};

#endif // VIEWDOCK_H
