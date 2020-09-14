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
    Q_OBJECT
public:
    // 拷贝控制函数
    ProblemListModel(QObject *parent = nullptr);
    ProblemListModel(const ProblemListModel&) = delete;
    ProblemListModel& operator=(const ProblemListModel&) = delete;
    ~ProblemListModel();
    // 返回行数,重载QAbstraceListModel
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    // 返回用于显示的数据,重载QAbstractListModel
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    // 返回表头,重载QAbstractListModel
    virtual QVariant headerData(int section,  Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // 让Controller部分知道Model可以编辑(编辑指的是可以双击或F2修改)
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    /* 因为数据有不同类别,所以不重写insertRows和removeRows
     * 为便于实现,假定只能单个数据添加和删除
     */
    // 添加一个题目,根据参数区分题目类型
    void addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right);
    void addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right);
    void addProblem(int pos, double _mark, const std::string& _desc, bool _right);
    void addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords);
    // 删除一个题目,由于虚析构函数不需区分类型
    bool rmProblem(int pos) ;
    // 转为JSON字符串便于保存
    std::string toJsonString() const;
    // 从JSON中获得试卷信息
    bool fromJsonDocument(const rapidjson::Document& doc);
    // 返回一个下标对应的题目指针,**不能对其delete**,若为nullptr则下标无效
    Problem* operator[](size_t index);
    // 计算所有题目总分，辅助判断是否低于100.
    double totalMark() const;
private:
    std::vector<Problem*> m_pProblemVecProList;
};

#endif // TESTMODEL_H
