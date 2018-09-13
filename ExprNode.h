#ifndef EXPRNODE_H
#define EXPRNODE_H

/*!
* \file      ExprNode.h
* \brief      лассы узла дл€ построени€ синтаксического дерева 
* \author    «убков јлександр ¬ладимирович (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      20 ма€ 2018 
*/
#include "Error.h"
#include <QList.h>
#include <qstring.h>
#include <QObject>

/*!
* <h1>јбстрактный класс узла синтаксического дерева</h1>
* <p>ƒл€ построени€ синтаксического дерева используетс€ иде€ полиморфизма, когда один узел-класс УExprNodeФ
* может иметь много форм (экземпл€ров) как операндов, так и операторов. »ерархи€ классов дл€ описани€ узлов 
* дерева представлена на диаграмме.</p> 
*/
class ExprNode : public QObject
{
	Q_OBJECT

	protected : 

		QList<ExprNode*> Operands;   

	public :
		/*!
		* ќпределить приоритет текущего класса.
		* \return приоритет или 0, если функци€ не переопределена 
		*/
		virtual int precedence()
		{
			return 0;
		}

		/*!
		* —обрать текст регул€рного выражени€ текущего узла.
		* \param[in] prec - приоритет родительского узла
		* \return строку эквивалентную текущему узлу на €зыке регул€рных выражени€. 
		*/
		virtual QString createText(int prec)
		{
			return QString("");
		}

		/*!
		* ‘ункци€ записывающа€ список наследуемых классов в текущий узел
		* \param[in] data - контейнер текущий дочерних узлов 
		*/
		void set_Operands(QList<ExprNode*> data);

		/*!
		* ‘ункци€ возвращающа€ список наследуемых классов текущего узла
		* \return контейнер текущих дочерних узлов 
		*/
		QList<ExprNode*> *get_Operands();

		/*!
		* “ип текущего узла дл€ построени€ дерева.
		* \return строку эквивалентную текущему узлу на €зыке регул€рных выражени€. 
		*/
		virtual QString type()
		{
			return QString("");
		}

		/*!
		* “екст текущий узла
		* \return собранную строку текущего узла . 
		*/
		virtual QString get_node()
		{
			return QString("");
		}

		/*!
		* ‘ункци€ восстановлени€ приоритета.
		* \param[in] perent - приоритет родительского узла
		* \param[in] child - приоритет дочернего узла
		* \param[in,out] arg - текст регул€рного выражени€ дл€ которого возвращаетс€ приоритет 
		* \return текст регул€рного выражени€ с восстановленным приоритетом  
		*/
		QString reestablishPrecedence(int perent, int child, QString & arg);
};


#endif // EXPRNODE_H