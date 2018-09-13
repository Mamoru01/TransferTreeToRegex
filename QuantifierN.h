#ifndef QUANTIFIERN_H
#define QUANTIFIERN_H
/*!
* \file      QuantifierNoOper.h
* \brief     ����� ���� ����������� �������������� ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 ��� 2018 
*/
#include "Quantifier.h"

/*!
* <h1>����������� ����� ���� ��������������� ������ "������������� n ���"</h1>
*/
class QuantifierN:public Quantifier
{
	Q_OBJECT
	
	private:

		QString operN;

	public:

		/*!
		* C������ ������� ���� - "������������� n ���", ������� ������ ���������.
		* \param[in] operN -  �������� ��������������
		* \param[out] error - ������ ��� ���������� ���� 
		*/
		 QuantifierN(QString argN,errorQuant& error);

		/*!
		* C������ ������� ���� - "������������� n ���",�� ������� ������ ���������.
		* \param[in] operN -  �������� ��������������
		*/
		 QuantifierN(QString argN);

		/*! 
		* C������ ����� ���������� �������� �������� ����.
		* \param[in] prec - ��������� ������������� ����
		* \return ������ ������������� �������� ���� �� ����� ��������� ��������. 
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

#endif // QUANTIFIERN_H