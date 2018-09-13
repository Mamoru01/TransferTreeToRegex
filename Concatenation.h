#ifndef CONCATENATION_H
#define CONCATENATION_H

/*!
* \file      Concatenation.h
* \brief     Классы узла конкатенации для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "ExprNode.h"

/*!
* <h1>Производный класс узла синтаксического дерева конкатенации</h1>
*/
class Concatenation:public ExprNode
{
	Q_OBJECT

	public:	
		
		/*!
		* Собрать текущий узел - "конкатенация", учитывая ошибки построения.
		* \param[out] error - ошибки при построении узла 
		*/
		Concatenation(QStringList & error);

		/*!
		* Собрать текущий узел - "конкатенация", не учитывая ошибки построения.
		*/
		Concatenation();

		/*!
		* Определить приоритет текущего класса.
		* \return приоритет равный "3". 
		*/
		int precedence();

		/*!
		* Собрать текст регулярного выражения текущего узла.
		* \param[in] prec - приоритет родительского узла
		* \return строку эквивалентную текущему узлу на языке регулярных выражения. 
		*/
		QString createText(int prec);

		/*!
		* Тип текущего узла для построения дерева.
		* \return строку эквивалентную текущему узлу на языке регулярных выражения. 
		*/
		QString type();

		/*!
		* Текст текущий узла
		* \return собранную строку текущего узла . 
		*/
		QString get_node();
};
#endif // CONCATENATION_H