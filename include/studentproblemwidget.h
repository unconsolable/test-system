/*
文件名: studentproblemwidget.h
版本: 1.0
目的与主要功能: 定义显示题目和提供作答区的Widget
创建日期: 2020.9.10
描述: 定义显示题目和提供作答区的Widget
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#ifndef STUDENTPROBLEMWIDGET_H
#define STUDENTPROBLEMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QRadioButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QButtonGroup>

// 释放非空指针
#define CheckDeleteSetNull(Ptr) \
    do                          \
    {                           \
        if ((Ptr))              \
        {                       \
            delete (Ptr);       \
            (Ptr) = nullptr;    \
        }                       \
    }while(0)

class StudentProblemWidget : public QWidget
{
    Q_OBJECT
    friend class StudentMainForm;
public:
    StudentProblemWidget(QWidget *parent = nullptr);
    ~StudentProblemWidget();
private:
    // 网格布局
    QGridLayout *m_gridLayoutProblem = nullptr;
    // 题型
    QLabel *m_labelProblemType = nullptr;
    // 分值
    QLabel *m_labelProblemMark = nullptr;
    // 题干
    QPlainTextEdit *m_plainTextProblemDesc = nullptr;
    // 答题区提示
    QLabel *m_labelProblemAnswerHint = nullptr;
    // 以下部分可能部分题会用不到
    // 因此析构时检查是否为空
    // 并避免悬垂指针

    // 以下部分仅选择题会用到
    // 选项的描述
    QLabel *m_labelProblemChoiceA = nullptr;
    QLabel *m_labelProblemChoiceB = nullptr;
    QLabel *m_labelProblemChoiceC = nullptr;
    QLabel *m_labelProblemChoiceD = nullptr;
    // 单选中选择正确选项
    QRadioButton *m_radioProblemRightChoiceA = nullptr;
    QRadioButton *m_radioProblemRightChoiceB = nullptr;
    QRadioButton *m_radioProblemRightChoiceC = nullptr;
    QRadioButton *m_radioProblemRightChoiceD = nullptr;
    QButtonGroup *m_btnGroupSingleChoice = nullptr;
    // 多选中选择正确选项
    QCheckBox *m_chkBoxProblemRightChoiceA = nullptr;
    QCheckBox *m_chkBoxProblemRightChoiceB = nullptr;
    QCheckBox *m_chkBoxProblemRightChoiceC = nullptr;
    QCheckBox *m_chkBoxProblemRightChoiceD = nullptr;
    // 以下部分仅判断题会用到
    QCheckBox *m_chkBoxIsRight = nullptr;
    // 以下部分仅简答题会用到
    QPlainTextEdit *m_plainTextWriteAnswer = nullptr;
    // 之前选择的选项,-1表示之前没有控件
    int m_intLastProblemTypeIndex = -1;
private slots:
    // 负责在题目类型变化时重新绘制题面
    void onProblemTypeChanged(int newtype);
};

#endif // STUDENTPROBLEMWIDGET_H
