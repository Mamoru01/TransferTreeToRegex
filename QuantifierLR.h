#ifndef QUANTIFIERLR_H
#define QUANTIFIERLR_H

/*!
* \file      QuantifierLR.h
* \brief     Класс узла квантификатора "от n до m раз" для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "Quantifier.h"

/*!
* <h1>Производный класс узла синтаксического дерева "квантификатор от n до m раз"</h1>
*/
class QuantifierLR:public Quantifier
{
	Q_OBJECT

	private:

		QString operL;
		QString operR;

	public:

		/*!
		* Собрать текущий узел - "квантификатор от n до m раз", учитывая ошибки построения.
		* \param[in] argL - левый аргумент квантификатора
		* \param[in] argR - правый аргумент квантификатора
		* \param[out] error - ошибки при построении узла 
		*/
		 QuantifierLR(QString argL,QString argR, errorQuant& error);

		/*!
		* Собрать текущий узел - "квантификатор от n до m раз",не учитывая ошибки построения.
		* \param[in] argL - левый аргумент квантификатора
		* \param[in] argR - правый аргумент квантификатора
		*/
		 QuantifierLR(QString argL,QString argR);

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

#endif // QUANTIFIERLR_H