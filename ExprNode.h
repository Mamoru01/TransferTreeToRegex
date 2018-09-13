#ifndef EXPRNODE_H
#define EXPRNODE_H

/*!
* \file      ExprNode.h
* \brief     ������ ���� ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      20 ��� 2018 
*/
#include "Error.h"
#include <QList.h>
#include <qstring.h>
#include <QObject>

/*!
* <h1>����������� ����� ���� ��������������� ������</h1>
* <p>��� ���������� ��������������� ������ ������������ ���� ������������, ����� ���� ����-����� �ExprNode�
* ����� ����� ����� ���� (�����������) ��� ���������, ��� � ����������. �������� ������� ��� �������� ����� 
* ������ ������������ �� ���������.</p> 
*/
class ExprNode : public QObject
{
	Q_OBJECT

	protected : 

		QList<ExprNode*> Operands;   

	public :
		/*!
		* ���������� ��������� �������� ������.
		* \return ��������� ��� 0, ���� ������� �� �������������� 
		*/
		virtual int precedence()
		{
			return 0;
		}

		/*!
		* ������� ����� ����������� ��������� �������� ����.
		* \param[in] prec - ��������� ������������� ����
		* \return ������ ������������� �������� ���� �� ����� ���������� ���������. 
		*/
		virtual QString createText(int prec)
		{
			return QString("");
		}

		/*!
		* ������� ������������ ������ ����������� ������� � ������� ����
		* \param[in] data - ��������� ������� �������� ����� 
		*/
		void set_Operands(QList<ExprNode*> data);

		/*!
		* ������� ������������ ������ ����������� ������� �������� ����
		* \return ��������� ������� �������� ����� 
		*/
		QList<ExprNode*> *get_Operands();

		/*!
		* ��� �������� ���� ��� ���������� ������.
		* \return ������ ������������� �������� ���� �� ����� ���������� ���������. 
		*/
		virtual QString type()
		{
			return QString("");
		}

		/*!
		* ����� ������� ����
		* \return ��������� ������ �������� ���� . 
		*/
		virtual QString get_node()
		{
			return QString("");
		}

		/*!
		* ������� �������������� ����������.
		* \param[in] perent - ��������� ������������� ����
		* \param[in] child - ��������� ��������� ����
		* \param[in,out] arg - ����� ����������� ��������� ��� �������� ������������ ��������� 
		* \return ����� ����������� ��������� � ��������������� �����������  
		*/
		QString reestablishPrecedence(int perent, int child, QString & arg);
};


#endif // EXPRNODE_H