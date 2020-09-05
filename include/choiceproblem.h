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
public:
    // 共通:选项
    std::vector<std::string> m_strVecAnswerList;
};

#endif // CHOICEPROBLEM_H
