/*
File Name: problem.h
Description: Define class Problem
Author: unconsolable
*/

#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
// 枚举类型定义题目类型
enum problemType
{
    SINGLE,
    MULTIPLE,
    TORF,
    WRITE,
};

class Problem
{
public:
    // 构造函数
    Problem(problemType = SINGLE, int = 0, const std::string& = "");
protected:
    // 题目共通:类型,分值,描述
    problemType m_problemTy;
    int m_intMark;
    std::string m_strDescription;
};

#endif // PROBLEM_H
