#ifndef ALTERNATIVE_H
#define ALTERNATIVE_H

/*!
* \file      Alternative.h
* \brief     Классы узла альтернативы для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "ExprNode.h"

/*!
* <h1>Производный класс узла синтаксического дерева альтернативы</h1>
*/
class Alternative:public ExprNode
{
	Q_OBJECT

	public:	
		
		/*!
		* Собрать текущий узел - "альтернатива", учитывая ошибки построения.
		* \param[out] error - ошибки при построении узла 
		*/
		Alternative(QStringList & error);

		/*!
		* Собрать текущий узел - "альтернатива", не учитывая ошибки построения.
		*/
		Alternative();

		/*!
		* Определить приоритет текущего класса.
		* \return приоритет равный "4". 
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

#endif // ALTERNATIVE_H