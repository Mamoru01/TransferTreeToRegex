/*!
* \file      Leaf.cpp	
* \brief     Классы узла для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      3 июня 2018 
*/
#include "Leaf.h"

Leaf::Leaf(QString oper,QStringList & error)
{

}

Leaf::Leaf(QString oper)
{
	leafOperand=oper;
}

int Leaf::precedence()
{
	return 1;
}

QString Leaf::createText(int prec)
{
	QString res;
	if (leafOperand == "empty")
		res = "";
	else if (leafOperand == "\\_")
		res = " ";
	else 
		res = leafOperand;
	return res;
}

QString Leaf::type()
{
	return QString("Leaf");
}

QString Leaf::get_node()
{
	return leafOperand;
}