/*!
* \file      QuantifierNoOper.h
* \brief     Реализация методов класса узла квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      07 июня 2018 
*/
#include "QuantifierNoOper.h"

QuantifierNoOper::QuantifierNoOper(QString oper)
{
	quant=oper;
}

QString QuantifierNoOper::createText(int prec)
{
	QString res = Operands.at(0)->createText(precedence());

	if (res=="")
	{
		res="";
	}
	else if (precedence()==Operands.at(0)->precedence() && (quant=="?" || quant=="+") )
	{
		res = QString("(?:%1)%2").arg(res).arg(quant);
	}
	else 
	{
		res = QString("%1%2").arg(res).arg(quant);
	}

	return ExprNode::reestablishPrecedence(prec, precedence(), res);
}

int QuantifierNoOper::precedence()
{
	return 2;
}

QString QuantifierNoOper::type()
{
	return QString("QuantifierNoOper");
}

QString QuantifierNoOper::get_node()
{
	return quant;
}
