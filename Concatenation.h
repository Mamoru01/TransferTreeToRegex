#ifndef CONCATENATION_H
#define CONCATENATION_H

/*!
* \file      Concatenation.h
* \brief     ������ ���� ������������ ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 ��� 2018 
*/
#include "ExprNode.h"

/*!
* <h1>����������� ����� ���� ��������������� ������ ������������</h1>
*/
class Concatenation:public ExprNode
{
	Q_OBJECT

	public:	
		
		/*!
		* ������� ������� ���� - "������������", �������� ������ ����������.
		* \param[out] error - ������ ��� ���������� ���� 
		*/
		Concatenation(QStringList & error);

		/*!
		* ������� ������� ���� - "������������", �� �������� ������ ����������.
		*/
		Concatenation();

		/*!
		* ���������� ��������� �������� ������.
		* \return ��������� ������ "3". 
		*/
		int precedence();

		/*!
		* ������� ����� ����������� ��������� �������� ����.
		* \param[in] prec - ��������� ������������� ����
		* \return ������ ������������� �������� ���� �� ����� ���������� ���������. 
		*/
		QString createText(int prec);

		/*!
		* ��� �������� ���� ��� ���������� ������.
		* \return ������ ������������� �������� ���� �� ����� ���������� ���������. 
		*/
		QString type();

		/*!
		* ����� ������� ����
		* \return ��������� ������ �������� ���� . 
		*/
		QString get_node();
};
#endif // CONCATENATION_H