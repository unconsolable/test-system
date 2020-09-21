/*
文件名: judgementproblem.h
版本: 1.0
目的与主要功能:定义判断题类
创建日期: 2020.9.4
描述: 定义判断题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#ifndef JUDGEMENTPROBLEM_H
#define JUDGEMENTPROBLEM_H

#include "problem.h"

class JudgementProblem : public Problem
{
public:
    // 构造函数
    JudgementProblem(double = 0, const std::string& = "", bool = true);
    // 判断得分
    virtual double checkAnswer(const QVariant&) override;
    // 转为JSON节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    // 析构函数
    virtual ~JudgementProblem() override = default;
    // 返回判断的正确与否
    bool getRightAns() const;
    // 设置判断的正确与否
    void setRightAns(bool rightAns);

private:
    // 存储判断是否为真
    bool m_boolRightAns;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(JudgementProblem);

#endif // JUDGEMENTPROBLEM_H
