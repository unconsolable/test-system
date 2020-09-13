#include "rootmainform.h"
#include "ui_rootmainform.h"
#include <QMessageBox>

extern rapidjson::Document g_jsonDocumentAccount;

RootMainForm::RootMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RootMainForm)
{
    ui->setupUi(this);
    // 设置学生的对应model
    m_listModelStudentAccount = new StudentAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewStuAccount->setModel(m_listModelStudentAccount);
    // 设置老师的对应model
    m_listModelTeacherAccount = new TeacherAccountModel(&g_jsonDocumentAccount);
    ui->m_listViewTeacherAccount->setModel(m_listModelTeacherAccount);
    // studentView与slot绑定
    connect(ui->m_listViewStuAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_studentAccountItemDoubleClicked(const QModelIndex&)));
    // teacherView与slot绑定
    connect(ui->m_listViewTeacherAccount, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_teacherAccountItemDoubleClicked(const QModelIndex&)));
}

RootMainForm::~RootMainForm()
{
    delete ui;
    CheckDeleteSetNull(m_listModelStudentAccount);
    CheckDeleteSetNull(m_listModelTeacherAccount);
}
// 学生账号删除功能
void RootMainForm::on_m_btnRmStu_clicked()
{
    auto selectModel = ui->m_listViewStuAccount->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未点击的UB
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        for (auto &i : indexList)
            m_listModelStudentAccount->rmAccount(i.row());
    }
}
// 老师账号删除功能
void RootMainForm::on_m_btnRmTea_clicked()
{
    auto selectModel = ui->m_listViewTeacherAccount->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未点击的UB
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        for (auto &i : indexList)
            m_listModelTeacherAccount->rmAccount(i.row());
    }
}
// 添加示例账户
void RootMainForm::on_m_btnAddStu_clicked()
{
    m_listModelStudentAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}
// 添加示例账户
void RootMainForm::on_m_btnAddTea_clicked()
{
    m_listModelTeacherAccount->addAccount("示例", "修改账户和密码,不要直接保存");
}
// 选择学生账户
void RootMainForm::on_m_studentAccountItemDoubleClicked(const QModelIndex& index)
{
    m_accountType = STUDENT;
    m_intAccountChoiceIndex = index.row();
    auto accountAndPasswdPair = m_listModelStudentAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}
// 选择教师账户
void RootMainForm::on_m_teacherAccountItemDoubleClicked(const QModelIndex& index)
{
    m_accountType = FACULTY;
    m_intAccountChoiceIndex = index.row();
    auto accountAndPasswdPair = m_listModelTeacherAccount->getAccountAndPasswd(m_intAccountChoiceIndex);
    ui->m_lineEditAccount->setText(tr(accountAndPasswdPair.first.c_str()));
    ui->m_lineEditPasswd->setText(tr(accountAndPasswdPair.second.c_str()));
}
// 加载管理员账号信息
void RootMainForm::on_m_btnLoadRoot_clicked()
{
    m_accountType = ROOT;
    ui->m_lineEditAccount->setText(tr("root"));
    ui->m_lineEditPasswd->setText(tr(g_jsonDocumentAccount["root"].GetString()));
}
