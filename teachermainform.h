#ifndef TEACHERMAINFORM_H
#define TEACHERMAINFORM_H

#include <QWidget>

namespace Ui {
class TeacherMainForm;
}

class TeacherMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherMainForm(QWidget *parent = nullptr);
    ~TeacherMainForm();

private:
    Ui::TeacherMainForm *ui;
};

#endif // TEACHERMAINFORM_H
