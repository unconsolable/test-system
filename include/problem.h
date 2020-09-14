/*
File Name: problem.h
Description: Define class Problem
Author: unconsolable
*/

#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include "rapidjson/document.h"
#include <QVariant>

// 枚举类型定义题目类型
enum problemType
{
    SINGLE,
    MULTIPLE,
    JUDGEMENT,
    WRITE,
};
/* 本类为所有问题的基类,定义纯虚函数
 * 转换为JSON节点和判断题目得分
 * 由于不同题目判断得分需要的数据不同
 * 这里使用QVariant统一包含
 * 需要时自己根据类型解析
 */
class Problem
{
public:
    // 拷贝控制
    Problem(problemType = SINGLE, double = 0, const std::string& = "");
    virtual ~Problem() = default;
    // 转换为rapidjson中的节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const;
    // 判题
    virtual double checkAnswer(const QVariant&) = 0;
    // Getter & Setter
    problemType getType() const;
    void setType(problemType _ty);
    double getMark() const;
    void setMark(double Mark);
    const std::string& getDescription() const;
    void setDescription(const std::string &Description);
    // 将类型代号转为对应字符串
    const char* convertType() const;
protected:
    // 题目共通:类型,分值,描述
    problemType m_problemTy;
    double m_doubleMark;
    std::string m_strDescription;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(Problem);

#endif // PROBLEM_H
