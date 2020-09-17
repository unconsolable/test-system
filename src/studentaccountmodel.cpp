/*
File Name: studentaccountmodel.cpp
Description: Implement the Model for Student Account
Author: unconsolable
*/
#include "studentaccountmodel.h"

StudentAccountModel::StudentAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_pJsonDocumentAccount(_jsonDocumentAcc)
{
}

void StudentAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    jsonValueAccount.SetString(account.c_str(), account.size(), m_pJsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式
    rapidjson::Value jsonValuePasswd;
    jsonValuePasswd.SetString(passwd.c_str(), passwd.size(), m_pJsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_pJsonDocumentAccount)["student"].AddMember(jsonValueAccount, jsonValuePasswd, m_pJsonDocumentAccount->GetAllocator());
    endInsertRows();
}

int StudentAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_pJsonDocumentAccount)["student"].MemberCount();
}

void StudentAccountModel::rmAccount(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key
    (*m_pJsonDocumentAccount)["student"].EraseMember((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos);
    endRemoveRows();
}

QVariant StudentAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_pJsonDocumentAccount)["student"].MemberCount()))
        return QVariant();
    // 返回账号
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr(((*m_pJsonDocumentAccount)["student"].MemberBegin() + index.row())->name.GetString());
    return QVariant();
}

std::pair<std::string, std::string> StudentAccountModel::getAccountAndPasswd(int pos)
{
    return std::make_pair(((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos)->name.GetString(), ((*m_pJsonDocumentAccount)["student"].MemberBegin() + pos)->value.GetString());
}

