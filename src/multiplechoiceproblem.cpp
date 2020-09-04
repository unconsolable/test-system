/*
File Name: multiplechoiceproblem.h
Description: Implement class MultipleChoice
Author: unconsolable
*/

#include "multiplechoiceproblem.h"

MultipleChoiceProblem::MultipleChoiceProblem(problemType _ty, int _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<std::string>& _right):
    ChoiceProblem(_ty, _mark, _desc, _ansList), m_charVecRightAns(_right)
{

}
