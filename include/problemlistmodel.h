/*
File Name: problemlistmodel.h
Description: Inherit QAbstractListModel to define ProblemListModel
Author: unconsolable
*/

#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "problem.h"
#include <QAbstractListModel>
#include <vector>
#include <string>

class ProblemListModel : public QAbstractListModel
{
    Q_OBJECT;
public:
    // 拷贝控制函数
    ProblemListModel(QObject *parent = nullptr);
    ProblemListModel(const ProblemListModel&) = delete;
    ProblemListModel& operator=(const ProblemListModel&) = delete;
    ~ProblemListModel();
    // 返回行数,重载QAbstraceListModel
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    // 返回数据,重载QAbstractListModel
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    // 返回表头,重载QAbstractListModel
    // virtual QVariant headerData(int section,  Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // 添加单选题
    void addSingleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right);
    // 添加多选题
    void addMultipleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right);
    // 添加判断题
    void addJudgementProblem(double _mark, const std::string& _desc, bool _right);
    // 添加简答题
    void addWriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords);
    // 转为JSON字符串便于保存
    std::string toJsonString() const;
    // 从JSON中获得试卷信息
    bool fromJsonDocument(const rapidjson::Document& doc);
private:
    std::vector<Problem*> m_pProblemVecProList;
};

#endif // TESTMODEL_H
