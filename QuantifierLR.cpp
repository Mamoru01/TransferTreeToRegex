/*!
* \file      QuantifierLR.h
* \brief     Реализация методов класса узла квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      07 июня 2018 
*/
#include "QuantifierLR.h"

QuantifierLR::QuantifierLR(QString argL,QString argR,errorQuant& error)
{
	int L;
	int R;
	bool flagNumberR=false;
	bool flagNumberL=false;

	error=errorQuant::no_mistakes;

	L = argL.toInt(&flagNumberL);
	if (flagNumberL || argL=="zero")
	{
		R = argR.toInt(&flagNumberR);
		if (flagNumberR || argR=="infinity")
		{
				if ((flagNumberL==true && flagNumberR==true && L <= R) 
					|| flagNumberL==false || flagNumberR==false)
				{
					operL = argL;
					operR = argR;
				}else
				{
					error=errorQuant::left_argument_more_right;
				}
		}else
		{
			error=errorQuant::right_argument_does_not_exist;
		}
	}else
	{
		error=errorQuant::left_argument_does_not_exist;
	}
}

QuantifierLR::QuantifierLR(QString argL,QString argR)
{
		operL = argL;;
		operR = argR;;
}

QString QuantifierLR::createText(int prec)
{
	QString res = Operands.at(0)->createText(precedence());
	
	if (res!="")
	{
		if (operL=="zero" && operR=="infinity")
		{
			res += QString("{,}");
		}
		else if (operL=="zero")
		{
			res += QString("{,%1}").arg(operR);
		}
		else if (operR=="infinity")
		{
			res += QString("{%1,}").arg(operL);
		}
		else 
		{
			res+=QString("{%1,%2}").arg(operL).arg(operR);
		}
	}

	return ExprNode::reestablishPrecedence(prec, precedence(), res);
}

int QuantifierLR::precedence()
{
	return 2;
}

QString QuantifierLR::type()
{
	return QString("QuantifierLR");
}

QString QuantifierLR::get_node()
{
	return QString("{%1,%2}").arg(operL).arg(operR);
}