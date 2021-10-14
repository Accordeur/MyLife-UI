#ifndef SETUP_WORKSPACE_H
#define SETUP_WORKSPACE_H

#include <QDialog>

namespace Ui {
class SetUpWorkspace;
}

class SetUpWorkspace : public QDialog
{
    Q_OBJECT

public:
    explicit SetUpWorkspace(QWidget *parent = nullptr);
    ~SetUpWorkspace();

    void setdata(const QString& tab, bool showCounter, bool syncSelection, bool syncZoom);

signals:
    void tabConfigChanged(const QString& tab, bool showCounter, bool syncSelection, bool syncZoom);
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
private:
    Ui::SetUpWorkspace *ui;

    QString tabName;
    bool showCounter;
    bool syncSelection;
    bool syncZoom;
};

#endif // SETUP_WORKSPACE_H
