/*
文件名: studentaccountmodel.h
版本: 1.0
目的与主要功能: 实现学生账号模型
创建日期: 2020.9.13
描述: 实现学生账号模型
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "studentaccountmodel.h"

/***************************
 * Name:
 *   StudentAccountModel
 * Input:
 *   parent 父级模型
 * Return:
 *   none
 * Description:
 *   学生账号模型构造函数
 ***************************/

StudentAccountModel::StudentAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_pJsonDocumentAccount(_jsonDocumentAcc)
{
}

/***************************
 * Name:
 *   addAccount
 * Input:
 *   account 账号名
 *   passwd 密码
 * Return:
 *   none
 * Description:
 *   添加学生账号
 ***************************/

void StudentAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    // 发送将变化的信号
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    // 转为string存储账号信息
    jsonValueAccount.SetString(account.c_str(), account.size(), m_pJsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式，转为string
    rapidjson::Value jsonValuePasswd;
    // 转为string存储密码信息
    jsonValuePasswd.SetString(passwd.c_str(), passwd.size(), m_pJsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_pJsonDocumentAccount)["student"].AddMember(jsonValueAccount, jsonValuePasswd, m_pJsonDocumentAccount->GetAllocator());
    // 发送变化完成的信号
    endInsertRows();
}

/***************************
 * Name:
 *   rowCount
 * Input:
 *   parent 无用
 * Return:
 *   none
 * Description:
 *   返回数据数目
 ***************************/

int StudentAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_pJsonDocumentAccount)["student"].MemberCount();
}

/***************************
 * Name:
 *   rmAccount
 * Input:
 *   pos
 * Return:
 *   bool
 * Description:
 *   删除pos处账号
 ***************************/

void StudentAccountModel::rmAccount(int pos)
{
    // 发送开始删除的信息
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key，删除数据
    (*m_pJsonDocumentAccount)["student"].EraseMember((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos);
    // 发送删除完成的信息
    endRemoveRows();
}

/***************************
 * Name:
 *   data
 * Input:
 *   index 数据坐标
 *   role 数据类型
 * Return:
 *   QVariant
 * Description:
 *   输出用于显示的数据
 ***************************/

QVariant StudentAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_pJsonDocumentAccount)["student"].MemberCount()))
        return QVariant();
    // 返回显示的信息
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr(((*m_pJsonDocumentAccount)["student"].MemberBegin() + index.row())->name.GetString());
    return QVariant();
}

/***************************
 * Name:
 *   getAccountAndPasswd
 * Input:
 *   pos
 * Return:
 *   std::pair<std::string, std::string>
 * Description:
 *   返回账号密码对
 ***************************/

std::pair<std::string, std::string> StudentAccountModel::getAccountAndPasswd(int pos)
{
    // 返回<账号，密码>对
    return std::make_pair(((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos)->name.GetString(), ((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos)->value.GetString());
}

