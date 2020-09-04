/*
File Name: singlechoiceproblem.h
Description: Define class SingleChoiceProblem
Author: unconsolable
*/

#ifndef SINGLECHOICEPROBLEM_H
#define SINGLECHOICEPROBLEM_H

#include "choiceproblem.h"

class SingleChoiceProblem : public ChoiceProblem
{
public:
    SingleChoiceProblem(int = 0, const std::string& = "", const std::vector<std::string>& = {}, char = 'A');
private:
    // 只有一个正确
    char m_charRightAns;
};

#endif // SINGLECHOICEPROBLEM_H
