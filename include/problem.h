/*
File Name: problem.h
Description: Define class Problem
Author: unconsolable
*/

#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <QVariant>
#include "rapidjson/document.h"
// 枚举类型定义题目类型
enum problemType
{
    SINGLE,
    MULTIPLE,
    JUDGEMENT,
    WRITE,
};

class Problem
{
public:
    // 构造函数
    Problem(problemType = SINGLE, double = 0, const std::string& = "");
    problemType getType() const;
    virtual double checkAnswer(const QVariant&) = 0;
    // 转换为rapidjson中的节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const;
    virtual ~Problem() = default;
protected:
    // 题目共通:类型,分值,描述
    problemType m_problemTy;
    double m_doubleMark;
    std::string m_strDescription;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(Problem);

#endif // PROBLEM_H
