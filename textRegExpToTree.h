#ifndef TEXTREGEXPTOTREE_H
#define TEXTREGEXPTOTREE_H
/*!
* \file      textRegExpToTree.h
* \brief     �������� ������� �������� ������ ������� �� �������� �������� �������.
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      7 ���� 2018 
*/
#include "includeTree.h"

/*!
* ������� �������� ������ ������� �� �������� �������� �������.
* \param[in] table_lexems - ������� ������
* \param[out] error - ������ ������
* \return c����� �� ������ ������. 
*/
ExprNode *textRegexpToTree(QStringList & table_lexems, QStringList &error);

/*!
* ������� ����������� ��������� ������� � ���� ������������.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isAlternative(QString & lexem);

/*!
* ������� ����������� ��������� ������� � ���� ������������.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isConcatenation(QString & lexem);

/*!
* ������� ����������� ��������� ������� � ���� �������������� � ����� �����������.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isQuantifierLR(QString & lexem);

/*!
* ������� ����������� ��������� ������� � ���� �������������� � ����� ����������.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isQuantifierN(QString & lexem);

/*!
* ������� ����������� ��������� ������� � ���� �������������� ��� ����������.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isQuantifierNoOper(QString & lexem);

/*!
* ������� ����������� ��������� ������� � ���� �����.
* \param[in] lexem - ������� ��� ��������
* \return 1 ���� ���������, ����� 0. 
*/
bool isLeaf(QString & lexem);

/*!
* ������� �������� ������.
* \param[in] Tree - ������ ������
*/
void deleteTree(ExprNode * Tree);

/*!
* ������� ��������� ����� ������������ �����.
* \param[in,out] tmp - ���� ��� ���������
*/
void revers(QList<ExprNode*> & tmp);

#endif // TEXTREGEXPTOTREE_H