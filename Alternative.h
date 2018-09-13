#ifndef ALTERNATIVE_H
#define ALTERNATIVE_H

/*!
* \file      Alternative.h
* \brief     ������ ���� ������������ ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 ��� 2018 
*/
#include "ExprNode.h"

/*!
* <h1>����������� ����� ���� ��������������� ������ ������������</h1>
*/
class Alternative:public ExprNode
{
	Q_OBJECT

	public:	
		
		/*!
		* ������� ������� ���� - "������������", �������� ������ ����������.
		* \param[out] error - ������ ��� ���������� ���� 
		*/
		Alternative(QStringList & error);

		/*!
		* ������� ������� ���� - "������������", �� �������� ������ ����������.
		*/
		Alternative();

		/*!
		* ���������� ��������� �������� ������.
		* \return ��������� ������ "4". 
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

#endif // ALTERNATIVE_H