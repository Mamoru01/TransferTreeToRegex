/*!
* \file      TestClass.h
* \brief     Реализация модульного тестирования
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      20 июня 2018 
*/
#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <QtTest>
#include "textRegExpToTree.h"

typedef QList<QString> newTableLexems;


class TestClass: public QObject
{
	Q_OBJECT

	public:
		TestClass(QObject *parent=0);
		~TestClass();

	private slots: 
		void testTextRegExpToTree_data();
		void testTextRegExpToTree();
		void testCreateTextLeaf_data();
		void testCreateTextLeaf();
		void testCreateTextConcatenation_data();
		void testCreateTextConcatenation();
		void testCreateTextAlternative_data();
		void testCreateTextAlternative();
		void testCreateTextQuantNoOper_data();
		void testCreateTextQuantNoOper();
		void testCreateTextQuantN_data();
		void testCreateTextQuantN();
		void testCreateTextQuantLR_data();
		void testCreateTextQuantLR();


		bool cmpNode(ExprNode *left,ExprNode *right, QString &message);
		bool cmpTree(ExprNode *left,ExprNode *right, QString &message);
};
#endif // TESTCLASS_H