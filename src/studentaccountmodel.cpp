/*
File Name:
Description:
Author: unconsolable
*/
#include "studentaccountmodel.h"

StudentAccountModel::StudentAccountModel(rapidjson::Document *_jsonDocumentAcc, QObject *parent)
    :QAbstractListModel(parent), m_jsonDocumentAccount(_jsonDocumentAcc)
{
}

void StudentAccountModel::addAccount(const std::string &account, const std::string &passwd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // account建为jsonValue格式
    rapidjson::Value jsonValueAccount;
    jsonValueAccount.SetString(account.c_str(), account.size(), m_jsonDocumentAccount->GetAllocator());
    // passwd建为jsonValue格式
    rapidjson::Value jsonValuePasswd;
    jsonValuePasswd.SetString(passwd.c_str(), passwd.size(), m_jsonDocumentAccount->GetAllocator());
    // 尾后追加
    (*m_jsonDocumentAccount)["student"].AddMember(jsonValueAccount, jsonValuePasswd, m_jsonDocumentAccount->GetAllocator());
    endInsertRows();
}

int StudentAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // 返回model中元素个数
    return (*m_jsonDocumentAccount)["student"].MemberCount();
}

void StudentAccountModel::rmAccount(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    // 传入对应key
    (*m_jsonDocumentAccount)["student"].EraseMember((*m_jsonDocumentAccount)["student"].MemberBegin() + pos);
    endRemoveRows();
}

QVariant StudentAccountModel::data(const QModelIndex &index, int role) const
{
    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>((*m_jsonDocumentAccount)["student"].MemberCount()))
        return QVariant();
    // 返回账号
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr(((*m_jsonDocumentAccount)["student"].MemberBegin() + index.row())->name.GetString());
    return QVariant();
}

std::pair<std::string, std::string> StudentAccountModel::getAccountAndPasswd(int pos)
{
    return std::make_pair(((*m_jsonDocumentAccount)["student"].MemberBegin() + pos)->name.GetString(), ((*m_jsonDocumentAccount)["student"].MemberBegin() + pos)->value.GetString());
}

