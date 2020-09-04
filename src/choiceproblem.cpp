/*
File Name: choiceproblem.cpp
Description: Implement class ChoiceProblem
Author: unconsolable
*/
#include "choiceproblem.h"

ChoiceProblem::ChoiceProblem(problemType _ty, int _mark, const std::string& _desc, const std::vector<std::string>& _ansList)
    :Problem(_ty, _mark, _desc), m_strVecAnswerList(_ansList)
{

}
