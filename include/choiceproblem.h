/*
File Name: choiceproblem.h
Description: Define class ChoiceProblem
Author: unconsolable
*/

#ifndef CHOICEPROBLEM_H
#define CHOICEPROBLEM_H

#include "problem.h"
#include <vector>

class ChoiceProblem : public Problem
{
public:
    // 构造选择题
    ChoiceProblem(problemType = SINGLE, double = 0, const std::string& = "", const std::vector<std::string>& = {});
    virtual double checkAnswer(const QVariant&) override = 0;
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    virtual ~ChoiceProblem() override = default;
    // 选项的Setter和Getter
    std::vector<std::string> getAnswerList() const;
    void setAnswerList(const std::vector<std::string> &AnswerList);
protected:
    // 共通:选项
    std::vector<std::string> m_strVecAnswerList;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(ChoiceProblem);

#endif // CHOICEPROBLEM_H
