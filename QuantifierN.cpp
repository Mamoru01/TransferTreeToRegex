/*!
* \file      QuantifierN.h
* \brief     Реализация методов класса узла квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      07 июня 2018 
*/
#include "QuantifierN.h"

QuantifierN::QuantifierN(QString argN,errorQuant& error)
{
	int N;

	bool flagNumber=false;

	error=errorQuant::no_mistakes;

	N = argN.toInt(&flagNumber);
	if (flagNumber)
	{
		operN=argN;
	}else
	{
		error=errorQuant::N_does_not_exist;
	}
}

QuantifierN::QuantifierN(QString argN)
{
	operN=argN;
}

QString QuantifierN::createText(int prec)
{
	QString res = Operands.at(0)->createText(precedence());

	if (res!="") 
		res+=QString("{%1}").arg(operN);

	return ExprNode::reestablishPrecedence(prec, precedence(), res);
}

int QuantifierN::precedence()
{
	return 2;
}

QString QuantifierN::type()
{
	return QString("QuantifierN");
}

QString QuantifierN::get_node()
{
	return QString("{%1}").arg(operN);
}