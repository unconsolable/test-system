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
    ProblemListModel() = default;
    ProblemListModel(const ProblemListModel&) = delete;
    ProblemListModel& operator=(const ProblemListModel&) = delete;
    ~ProblemListModel();
    // 添加单选题
    void addSingleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right);
    // 添加多选题
    void addMultipleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right);
    // 添加判断题
    void addJudgementProblem(double _mark, const std::string& _desc, bool _right);
    // 添加简答题
    void addWriteProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords);
    std::string toJsonString() const;
    bool fromJsonDocument(const rapidjson::Document& doc);
private:
    std::vector<Problem*> m_pProblemVecProList;
};

#endif // TESTMODEL_H
