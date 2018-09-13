#ifndef QUANTIFIERNOOPER_H
#define QUANTIFIERNOOPER_H
/*!
* \file      QuantifierNoOper.h
* \brief     ����� ���� ����������� �������������� ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 ��� 2018 
*/
#include "Quantifier.h"

/*!
* <h1>����������� ����� ���� ��������������� ������ "���������� �������������"</h1>
*/
class QuantifierNoOper:public Quantifier
{
	Q_OBJECT
	
	private:

		QString quant;

	public:

		/*!
		* ������� ������� ���� - "���������� �������������",�� �������� ������ ����������.
		* \param[in] oper -  ��� ��������������
		*/
		 QuantifierNoOper(QString oper);

		/*!
		* ������� ����� ����������� ��������� �������� ����.
		* \param[in] prec - ��������� ������������� ����
		* \return ������ ������������� �������� ���� �� ����� ���������� ���������. 
		*/
		QString createText(int prec);

		/*!
		* ���������� ��������� �������� ������.
		* \return ��������� ������ "2". 
		*/
		int precedence();

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

#endif // QUANTIFIERNOOPER_H