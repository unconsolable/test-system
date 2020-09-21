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
    // 返回类型
    problemType getType() const;
    // 设置类型
    void setType(problemType _ty);
    // 返回分数
    double getMark() const;
    // 设置分数
    void setMark(double Mark);
    // 返回题目描述
    const std::string& getDescription() const;
    // 设置题目描述
    void setDescription(const std::string &Description);
    // 将类型代号转为对应字符串
    const char* convertType() const;
protected:
    // 题目共通:类型,
    problemType m_problemTy;
    // 分值,
    double m_doubleMark;
    // 描述
    std::string m_strDescription;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(Problem);

#endif // PROBLEM_H
