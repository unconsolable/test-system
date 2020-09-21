/*
File Name: judgementproblem.h
Description: Define the Class JudgementProblem
Author: unconsolable
*/
#ifndef JUDGEMENTPROBLEM_H
#define JUDGEMENTPROBLEM_H

#include "problem.h"

class JudgementProblem : public Problem
{
public:
    JudgementProblem(double = 0, const std::string& = "", bool = true);
    // 判断得分
    virtual double checkAnswer(const QVariant&) override;
    // 转为JSON节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    // 析构函数
    virtual ~JudgementProblem() override = default;
    // 返回与设置判断的正确与否
    bool getRightAns() const;
    void setRightAns(bool rightAns);

private:
    bool m_boolRightAns;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(JudgementProblem);

#endif // JUDGEMENTPROBLEM_H
