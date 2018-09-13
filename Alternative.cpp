/*!
* \file      Alternative.cpp
* \brief     Реализация методов класса узла альтернативы для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      30 мая 2018 
*/

#include "Alternative.h"

Alternative::Alternative(QStringList & error)
{
	;
}

Alternative::Alternative()
{
	;
}

int Alternative::precedence()
{
	return 4;
}

QString Alternative::createText(int prec)
{
	QString res = (Operands.size()==0)?0:Operands.at(0)->createText(precedence());
	bool empty = false;

	for (int i=1;i<Operands.size();i++)
	{
		if (Operands.at(i)->createText(precedence())!="")
			res += QString("|%1").arg(Operands.at(i)->createText(precedence()));
		else 
			empty = true;
	}

	if (Operands.size()==1 || empty)
	{
		res = QString("(?:%1|)").arg(res);
	}else 
	{
		res = ExprNode::reestablishPrecedence(prec, precedence(), res);
	}

	return res;
}

QString Alternative::type()
{
	return QString("Alternative");
}

QString Alternative::get_node()
{
	return QString("|");
}