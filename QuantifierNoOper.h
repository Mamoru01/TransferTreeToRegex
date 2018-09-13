#ifndef QUANTIFIERNOOPER_H
#define QUANTIFIERNOOPER_H
/*!
* \file      QuantifierNoOper.h
* \brief     Класс узла символьного квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "Quantifier.h"

/*!
* <h1>Производный класс узла синтаксического дерева "символьный квантификатор"</h1>
*/
class QuantifierNoOper:public Quantifier
{
	Q_OBJECT
	
	private:

		QString quant;

	public:

		/*!
		* Собрать текущий узел - "символьный квантификатор",не учитывая ошибки построения.
		* \param[in] oper -  тип квантификатора
		*/
		 QuantifierNoOper(QString oper);

		/*!
		* Собрать текст регулярного выражения текущего узла.
		* \param[in] prec - приоритет родительского узла
		* \return строку эквивалентную текущему узлу на языке регулярных выражения. 
		*/
		QString createText(int prec);

		/*!
		* Определить приоритет текущего класса.
		* \return приоритет равный "2". 
		*/
		int precedence();

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

#endif // QUANTIFIERNOOPER_H