#ifndef QUANTIFIERLR_H
#define QUANTIFIERLR_H

/*!
* \file      QuantifierLR.h
* \brief     ����� ���� �������������� "�� n �� m ���" ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 ��� 2018 
*/
#include "Quantifier.h"

/*!
* <h1>����������� ����� ���� ��������������� ������ "������������� �� n �� m ���"</h1>
*/
class QuantifierLR:public Quantifier
{
	Q_OBJECT

	private:

		QString operL;
		QString operR;

	public:

		/*!
		* ������� ������� ���� - "������������� �� n �� m ���", �������� ������ ����������.
		* \param[in] argL - ����� �������� ��������������
		* \param[in] argR - ������ �������� ��������������
		* \param[out] error - ������ ��� ���������� ���� 
		*/
		 QuantifierLR(QString argL,QString argR, errorQuant& error);

		/*!
		* ������� ������� ���� - "������������� �� n �� m ���",�� �������� ������ ����������.
		* \param[in] argL - ����� �������� ��������������
		* \param[in] argR - ������ �������� ��������������
		*/
		 QuantifierLR(QString argL,QString argR);

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

#endif // QUANTIFIERLR_H