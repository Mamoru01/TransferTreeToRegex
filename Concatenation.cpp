/*!
* \file      Concatenation.cpp
* \brief     Реализация методов класса узла конкатенации для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      30 мая 2018 
*/

#include "Concatenation.h"

Concatenation::Concatenation(QStringList & error)
{

}

Concatenation::Concatenation()
{

}

int Concatenation::precedence()
{
	return 3;
}

QString Concatenation::createText(int prec)
{
	QString res = "";

	for (int i=0;i<Operands.size();i++)
	{
		res+=Operands.at(i)->createText(precedence());
	}

	return (Operands.size()==1)?res:ExprNode::reestablishPrecedence(prec, precedence(), res);
}

QString Concatenation::type()
{
	return QString("Concatenation");
}

QString Concatenation::get_node()
{
	return QString("");
}