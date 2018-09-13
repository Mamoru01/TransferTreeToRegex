#ifndef QUANTIFIER_H
#define QUANTIFIER_H

/*!
* \file      Quantifier.h
* \brief     Промежуточный класс квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "ExprNode.h"

/*!
* <h1>Промежуточный класс для квантификатора</h1>
*/
class Quantifier:public ExprNode
{
	Q_OBJECT
};

#endif // QUANTIFIER_H