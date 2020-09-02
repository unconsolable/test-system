#ifndef STUDENTMAINFORM_H
#define STUDENTMAINFORM_H

#include <QWidget>

namespace Ui {
class StudentMainForm;
}

class StudentMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudentMainForm(QWidget *parent = nullptr);
    ~StudentMainForm();

private:
    Ui::StudentMainForm *ui;
};

#endif // STUDENTMAINFORM_H
