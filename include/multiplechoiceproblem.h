/*
File Name: multiplechoiceproblem.h
Description: Define class MultipleChoice
Author: unconsolable
*/

#ifndef MULTIPLECHOICEPROBLEM_H
#define MULTIPLECHOICEPROBLEM_H

#include "choiceproblem.h"

class MultipleChoiceProblem : public ChoiceProblem
{
public:
    MultipleChoiceProblem(problemType = SINGLE, int = 0, const std::string& = "", const std::vector<std::string>& = {}, const std::vector<std::string>& = {});
private:
    // 正确答案用列表表示
    std::vector<std::string> m_charVecRightAns;
};

#endif // MULTIPLECHOICEPROBLEM_H
