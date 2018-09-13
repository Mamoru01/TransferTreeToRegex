/*!
* \file      ExprNode.cpp	
* \brief     ������ ���� ��� ���������� ��������������� ������ 
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      30 ��� 2018 
*/
#include "ExprNode.h"


void ExprNode::set_Operands(QList<ExprNode*> data)
{
	Operands=data;
}

QList<ExprNode*> *ExprNode::get_Operands()
{
	return &Operands;
};

QString ExprNode::reestablishPrecedence(int perent, int child, QString & arg)
{
	
	QString res = arg;

	if (perent<child)
		arg = QString ("(?:%1)").arg(res);

	return arg;
}
