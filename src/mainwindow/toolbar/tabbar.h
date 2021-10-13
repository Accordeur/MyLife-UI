#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include "configure/config.h"

class QPushButton;

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void paintAddTagButton();

signals:
    void tabIsTooLong(bool flag = false);

public slots:
    void addNewTab();

private slots:
    void closeTab(int index);

private:
    QPushButton* pushButton_Add_Tag;

    TabBarNode* tabBarConfig = nullptr;
};

#endif // TABBAR_H
