#ifndef ROOTMAINFORM_H
#define ROOTMAINFORM_H

#include <QWidget>

namespace Ui {
class RootMainForm;
}

class RootMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit RootMainForm(QWidget *parent = nullptr);
    ~RootMainForm();

private:
    Ui::RootMainForm *ui;
};

#endif // ROOTMAINFORM_H
