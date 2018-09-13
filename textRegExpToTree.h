#ifndef TEXTREGEXPTOTREE_H
#define TEXTREGEXPTOTREE_H
/*!
* \file      textRegExpToTree.h
* \brief     Прототип функции создания дерева классов по обратной польской нотации.
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      7 июня 2018 
*/
#include "includeTree.h"

/*!
* Функция создания дерева классов по обратной польской нотации.
* \param[in] table_lexems - таблица лексем
* \param[out] error - список ошибок
* \return cсылка на корень дерева. 
*/
ExprNode *textRegexpToTree(QStringList & table_lexems, QStringList &error);

/*!
* Функция определения отношения лексемы к узлу Альтернативы.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isAlternative(QString & lexem);

/*!
* Функция определения отношения лексемы к узлу Конкатинации.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isConcatenation(QString & lexem);

/*!
* Функция определения отношения лексемы к узлу Квантификатора с двумя аргументами.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isQuantifierLR(QString & lexem);

/*!
* Функция определения отношения лексемы к узлу Квантификатора с одним аргументом.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isQuantifierN(QString & lexem);

/*!
* Функция определения отношения лексемы к узлу Квантификатора без аргументов.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isQuantifierNoOper(QString & lexem);

/*!
* Функция определения отношения лексемы к узлу Листа.
* \param[in] lexem - лексема для проверки
* \return 1 если относится, иначе 0. 
*/
bool isLeaf(QString & lexem);

/*!
* Функция удаления дерева.
* \param[in] Tree - корень дерева
*/
void deleteTree(ExprNode * Tree);

/*!
* Функция отражения Люста относительно конца.
* \param[in,out] tmp - лист для обработки
*/
void revers(QList<ExprNode*> & tmp);

#endif // TEXTREGEXPTOTREE_H