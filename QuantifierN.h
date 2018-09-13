#ifndef QUANTIFIERN_H
#define QUANTIFIERN_H
/*!
* \file      QuantifierNoOper.h
* \brief     Класс узла символьного квантификатора для построения синтаксического дерева 
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      29 мая 2018 
*/
#include "Quantifier.h"

/*!
* <h1>Производный класс узла синтаксического дерева "квантификатор n раз"</h1>
*/
class QuantifierN:public Quantifier
{
	Q_OBJECT
	
	private:

		QString operN;

	public:

		/*!
		* Cобрать текущий узел - "квантификатор n раз", учитыва¤ ошибки построени¤.
		* \param[in] operN -  аргумент квантификатора
		* \param[out] error - ошибки при построении узла 
		*/
		 QuantifierN(QString argN,errorQuant& error);

		/*!
		* Cобрать текущий узел - "квантификатор n раз",не учитыва¤ ошибки построени¤.
		* \param[in] operN -  аргумент квантификатора
		*/
		 QuantifierN(QString argN);

		/*! 
		* Cобрать текст регул¤рного выражени¤ текущего узла.
		* \param[in] prec - приоритет родительского узла
		* \return строку эквивалентную текущему узлу на ¤зыке регул¤рных выражени¤. 
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

#endif // QUANTIFIERN_H