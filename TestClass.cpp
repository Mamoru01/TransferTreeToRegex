/*!
* \file      TestClass.cpp
* \brief     Реализация модульного тестирования
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.02(development)
* \data      20 июня 2018 
*/
#include "TestClass.h"
#include "textRegExpToTree.h"
#include <QtTest>

TestClass::TestClass(QObject *parent)
	: QObject(parent)
{

}

TestClass::~TestClass()
{

}

//test-API: сравнение двух узлов 
bool TestClass::cmpNode(ExprNode *left,ExprNode *right, QString &message)
{
	bool its_ok=true;
	if (!(left==NULL && right==NULL))
	{
		if (left!=NULL && right==NULL ||left==NULL && right!=NULL)
		{
			its_ok=false;
			message+="Error! One of the NULL nodes.";
		}else
		{
			if (left->type()!=right->type())
			{
				its_ok=false;
				message+="\nError: Node types do not match:";
				message+="\nExpected:";
				message+= left->type();
				message+="  Output:";
				message+=right->type();
			}
			if (left->get_node()!=right->get_node())
			{
				its_ok=false;
				message+="\nError! The value of the nodes does not match:";
				message+="\nExpected:";
				message+= left->get_node();
				message+="  Output:";
				message+=right->get_node();
			}
			if	(left->get_Operands()->length()!=right->get_Operands()->length())
			{
				message+="\nError: The number of operands of the current node does not match:";
				message+="\nExpected:"+ QString::number(left->get_Operands()->length());
				message+="   Output:"+ QString::number(right->get_Operands()->length());
				its_ok=false;
			}
		}
	}
	return its_ok;
}

//test-API: сравнение двух деревьев 
bool TestClass::cmpTree(ExprNode *left,ExprNode *right, QString &message)
{
	bool its_ok=true;
	its_ok=cmpNode(left,right,message);
	for (int i=0;its_ok!=false &&i<left->get_Operands()->size();i++)
	{
		its_ok=cmpTree(left->get_Operands()->at(i),right->get_Operands()->at(i),message);
	}
	return its_ok;
}

void TestClass::testTextRegExpToTree_data()
{
	//input
	QTest::addColumn<QStringList>("textTree");
	//output
	QTest::addColumn<QStringList>("output_error"); 
	//resault
	QTest::addColumn<QStringList>("result_error"); 
	QTest::addColumn<ExprNode*>("result_Tree");	

	QStringList out_errorEmpty;//Пустой входной список
	QStringList res_errorEmpty;//Пустой предпологаемый список
	ExprNode* TreeNULL=NULL;

	//Номер: 1
	//Одна лексема, которая не являетя оператором
	////////////Входная строка///////////////////
	QStringList inputTable1;
	inputTable1 << "a";
	//////////////Дерево/////////////////////////
	ExprNode* Tree1 = new Leaf(QString("a"));
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.1 One lexeme that is an argument.")<<inputTable1<<out_errorEmpty<<res_errorEmpty<<Tree1;


	//Номер: 2
	//Одна лексема, которая являетя оператором
	////////////Входная строка///////////////////
	QStringList inputTable2;
	inputTable2 << "*";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error2;
	QStringList res_error2;
	/////////Заполнить тест//////////////////////
	res_error2<<QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"*\".\nНомер лексемы:0."));
	QTest::newRow("1.2 One lexeme that is an operator.")<<inputTable2<<out_error2<<res_error2<<TreeNULL;


	//Номер: 3
	//Альтернатива. Оператор принимает два аргумента.
	////////////Входная строка///////////////////
	QStringList inputTable3;
	inputTable3 << "a" << "b" << "2" << "|";
	//////////////Дерево/////////////////////////
	ExprNode* Tree3 = new Alternative();
	QList<ExprNode*> Operands31;
	Operands31<<new Leaf("a")<<new Leaf("b");
	Tree3->set_Operands(Operands31);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.3 Alternative. The operator takes two arguments.") <<inputTable3<<out_errorEmpty<<res_errorEmpty<<Tree3;


	//Номер: 4
	//Альтернатива. Оператор принимает один аргумента.
	////////////Входная строка///////////////////
	QStringList inputTable4;
	inputTable4 << "a" << "1" << "|";
	//////////////Дерево/////////////////////////
	ExprNode* Tree4 = new Alternative();
	QList<ExprNode*> Operands41;
	Operands41<<new Leaf("a");
	Tree4->set_Operands(Operands41);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.4 Alternative. The operator takes one argument.") <<inputTable4<<out_errorEmpty<<res_errorEmpty<<Tree4;

	//Номер: 5
	//Альтернатива. Оператор принимает пустой аргумента.
	////////////Входная строка///////////////////
	QStringList inputTable5;
	inputTable5 << "a" << "b" << "empty" << "3" << "|";
	//////////////Дерево/////////////////////////
	ExprNode* Tree5 = new Alternative();
	QList<ExprNode*> Operands51;
	Operands51<<new Leaf("a")<<new Leaf("b")<< new Leaf("empty");
	Tree5->set_Operands(Operands51);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.5 Alternative. The operator takes an empty argument.")<<inputTable5<<out_errorEmpty<<res_errorEmpty<<Tree5;

	//Номер: 6
	//Конкатенация. Оператор принимает два аргумента.
	////////////Входная строка///////////////////
	QStringList inputTable6;
	inputTable6 << "a" << "b" << "2" << "&";
	//////////////Дерево/////////////////////////
	ExprNode* Tree6 = new Concatenation();
	QList<ExprNode*> Operands61;
	Operands61<<new Leaf("a")<<new Leaf("b");
	Tree6->set_Operands(Operands61);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.6 Concatenation. The operator takes two arguments.")<<inputTable6<<out_errorEmpty<<res_errorEmpty<<Tree6;

	//Номер: 7
	//Квантификатор. "0 или более".
	////////////Входная строка///////////////////
	QStringList inputTable7;
	inputTable7 << "a" << "*";
	//////////////Дерево/////////////////////////
	ExprNode* Tree7 = new QuantifierNoOper("*");
	QList<ExprNode*> Operands71;
	Operands71<<new Leaf("a");
	Tree7->set_Operands(Operands71);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.7 Quantifier. \"0 or more\".")<<inputTable7<<out_errorEmpty<<res_errorEmpty<<Tree7;

	//Номер: 8
	//Квантификатор. "1 или более".
	////////////Входная строка///////////////////
	QStringList inputTable8;
	inputTable8 << "a" << "+";
	//////////////Дерево/////////////////////////
	ExprNode* Tree8 = new QuantifierNoOper("+");
	QList<ExprNode*> Operands81;
	Operands81<<new Leaf("a");
	Tree8->set_Operands(Operands81);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.8 Quantifier. \"1 or more\".")<<inputTable8<<out_errorEmpty<<res_errorEmpty<<Tree8;

	//Номер: 9
	//Квантификатор. "0 или 1".
	////////////Входная строка///////////////////
	QStringList inputTable9;
	inputTable9 << "a" << "?";
	//////////////Дерево/////////////////////////
	ExprNode* Tree9 = new QuantifierNoOper("?");
	QList<ExprNode*> Operands91;
	Operands91<<new Leaf("a");
	Tree9->set_Operands(Operands91);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.9 Quantifier. \"0 or 1\".")<<inputTable9<<out_errorEmpty<<res_errorEmpty<<Tree9;

	//Номер: 10
	//Квантификатор. "n или m".
	////////////Входная строка///////////////////
	QStringList inputTable10;
	inputTable10 << "a" << "2" << "4" << "{,}";
	//////////////Дерево/////////////////////////
	ExprNode* Tree10 = new QuantifierLR("2","4");
	QList<ExprNode*> Operands101;
	Operands101<<new Leaf("a");
	Tree10->set_Operands(Operands101);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.10 Quantifier. \"n or m\".")<<inputTable10<<out_errorEmpty<<res_errorEmpty<<Tree10;

	//Номер: 11
	//Квантификатор. "n или m(left range empty)".
	////////////Входная строка///////////////////
	QStringList inputTable11;
	inputTable11 << "a" << "zero" << "4" << "{,}";
	//////////////Дерево/////////////////////////
	ExprNode* Tree11 = new QuantifierLR("zero","4");
	QList<ExprNode*> Operands111;
	Operands111<<new Leaf("a");
	Tree11->set_Operands(Operands111);	
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.11 Quantifier. \"n or m(left range empty)\".")<<inputTable11<<out_errorEmpty<<res_errorEmpty<<Tree11;

	//Номер: 12
	//Квантификатор. "n или m(left range is not a number and not zero)".
	////////////Входная строка///////////////////
	QStringList inputTable12;
	inputTable12 << "a" << "q" << "2" << "{,}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error12;
	QStringList res_error12;
	res_error12<<QString::fromStdWString(std::wstring(L"Ошибка! Левый диапазон не может принимать \"q\". Номер лексемы: 1."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.12 Quantifier. \"n or m(left range is not a number and not zero)\".")<<inputTable12<<out_error12<<res_error12<<TreeNULL;

	//Номер: 13
	//Квантификатор. "n или m(the left range assumes infinity)".
	////////////Входная строка///////////////////
	QStringList inputTable13;
	inputTable13 << "a" << "infinity" << "2" << "{,}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error13;
	QStringList res_error13;
	res_error13<<QString::fromStdWString(std::wstring(L"Ошибка! Левый диапазон не может принимать \"infinity\". Номер лексемы: 1."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.13 Quantifier. \"n or m(the left range assumes infinity)\".")<<inputTable13<<out_error13<<res_error13<<TreeNULL;

	//Номер: 14
	//Квантификатор. "n или m(the right element is empty)".
	////////////Входная строка///////////////////
	QStringList inputTable14;
	inputTable14 << "a"<< "2" << "infinity" << "{,}";
	//////////////Дерево/////////////////////////
	ExprNode* Tree14 = new QuantifierLR("2","infinity");
	QList<ExprNode*> Operands141;
	Operands141<<new Leaf("a");
	Tree14->set_Operands(Operands141);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.14 Quantifier. \"n or m(the right element is empty)\".")<<inputTable14<<out_errorEmpty<<res_errorEmpty<<Tree14;

	//Номер: 15
	//Квантификатор. "n или m(the right range does not take a number and not infinity)".
	////////////Входная строка///////////////////
	QStringList inputTable15;
	inputTable15 << "a" << "1" << "q" << "{,}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error15;
	QStringList res_error15;
	res_error15<<QString::fromStdWString(std::wstring(L"Ошибка! Правый диапазон не может принимать \"q\". Номер лексемы: 2."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.15 Quantifier. \"n or m(the right range does not take a number and not infinity)\".")<<inputTable15<<out_error15<<res_error15<<TreeNULL;

	//Номер: 16
	//Квантификатор. "n или m(the right range zero)".
	////////////Входная строка///////////////////
	QStringList inputTable16;
	inputTable16 << "a" << "1" << "zero" << "{,}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error16;
	QStringList res_error16;
	res_error16<<QString::fromStdWString(std::wstring(L"Ошибка! Правый диапазон не может принимать \"zero\". Номер лексемы: 2."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.16 Quantifier. \"n or m(the right range zero)\".")<<inputTable16<<out_error16<<res_error16<<TreeNULL;

	//Номер: 17
	//Квантификатор. "n time".
	////////////Входная строка///////////////////
	QStringList inputTable17;
	inputTable17 << "a" << "23" << "{}";
	//////////////Дерево/////////////////////////
	ExprNode* Tree17 =new QuantifierN("23");
	QList<ExprNode*> Operands171;
	Operands171<<new Leaf("a");
	Tree17->set_Operands(Operands171);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.17 Quantifier. \"n time\".")<<inputTable17<<out_errorEmpty<<res_errorEmpty<<Tree17;

	//Номер: 18
	//Квантификатор. "n time(N- not a number)".
	////////////Входная строка///////////////////
	QStringList inputTable18;
	inputTable18 << "a" << "q" << "{}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error18;
	QStringList res_error18;
	res_error18<<QString::fromStdWString(std::wstring(L"Ошибка! Количество повторений не может принимать \"q\". Номер лексемы: 1."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.18 Quantifier. \"n or m(N- not a number)\".")<<inputTable18<<out_error18<<res_error18<<TreeNULL;

	//Номер: 19
	//Аргумент. Character class.
	////////////Входная строка///////////////////
	QStringList inputTable19;
	inputTable19 << "[:print:]";
	//////////////Дерево/////////////////////////
	ExprNode* Tree19 = new Leaf("[:print:]");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.19 Leaf. Character class ")<<inputTable19<<out_errorEmpty<<res_errorEmpty<<Tree19;
	
	//Номер: 20
	//Аргумент. Empty.
	////////////Входная строка///////////////////
	QStringList inputTable20;
	inputTable20 << "empty";
	//////////////Дерево/////////////////////////
	ExprNode* Tree20 = new Leaf("empty");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.20 Leaf. Empty")<<inputTable20<<out_errorEmpty<<res_errorEmpty<<Tree20;

	//Номер: 21
	//Аргумент. Dot.
	////////////Входная строка///////////////////
	QStringList inputTable21;
	inputTable21 << ".";
	//////////////Дерево/////////////////////////
	ExprNode* Tree21 = new Leaf(".");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.21 Leaf. Dot")<<inputTable21<<out_errorEmpty<<res_errorEmpty<<Tree21;

	//Номер: 22
	//Аргумент. Escape-symbol.
	////////////Входная строка///////////////////
	QStringList inputTable22;
	inputTable22 << "\\w";
	//////////////Дерево/////////////////////////
	ExprNode* Tree22 = new Leaf("\\w");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.22 Leaf. Escape-symbol")<<inputTable22<<out_errorEmpty<<res_errorEmpty<<Tree22;

	//Номер: 23
	//Аргумент. Shielding symbol.
	////////////Входная строка///////////////////
	QStringList inputTable23;
	inputTable23 << "\\_";
	//////////////Дерево/////////////////////////
	ExprNode* Tree23 = new Leaf("\\_");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.23 Leaf. Shielding symbol")<<inputTable23<<out_errorEmpty<<res_errorEmpty<<Tree23;

	//Номер: 24
	//Аргумент. Принимает последовательность символов, которые не являются
	// символьнми классами, ключевыми словов пустого символа, escape 
	//-последовательностью и экранируемым символом.
	////////////Входная строка///////////////////
	QStringList inputTable24;
	inputTable24 << "qwe";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error24;
	QStringList res_error24;
	res_error24<<QString::fromStdWString(std::wstring(L"Ошибка! Лексема \"qwe\" не опознана. Номер лексемы: 0."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.24 Leaf. Unprocessed character string")<<inputTable24<<out_error24<<res_error24<<TreeNULL;

	//Номер: 25
	//Демонстрационный пример(ошибок нет).
	////////////Входная строка///////////////////
	QStringList inputTable25;
	inputTable25 << "\\w" << "!" << "=" << "empty"<< "3" << "|" << "=" << "\\d" << "4" << "&";
	//////////////Дерево/////////////////////////
	ExprNode* Tree25 = new Concatenation();
	QList<ExprNode*> Operands251;
	Operands251<<new Leaf("\\w") << new Alternative() << new Leaf("=") << new Leaf ("\\d");
	Tree25->set_Operands(Operands251);
	QList<ExprNode*> Operands252;
	Operands252<<new Leaf("!")<<new Leaf ("=") << new Leaf ("empty");
	Tree25->get_Operands()->at(1)->set_Operands(Operands252);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.25 Demo-Tree.")<<inputTable25<<out_errorEmpty<<res_errorEmpty<<Tree25;

	//Номер: 26
	//Квантификатор. "n или m(the right range is less than the left)"
	////////////Входная строка///////////////////
	QStringList inputTable26;
	inputTable26 << "a" << "7" << "3" << "{,}";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error26;
	QStringList res_error26;
	res_error26<<QString::fromStdWString(std::wstring(L"Ошибка! Левый аргумент квантификатор не может быть больше правого. Номер лексемы: 1,2."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.26 Quantifier.\"n or m(the right range is less than the left)\"")<<inputTable26<<out_error26<<res_error26<<TreeNULL;

	//Номер: 27
	//Квантификатор. "n или n(the right range is left)"
	////////////Входная строка///////////////////
	QStringList inputTable27;
	inputTable27 << "\\+" << "7" << "7" << "{,}";
	//////////////Дерево/////////////////////////
	ExprNode* Tree27 = new QuantifierLR("7","7");
	QList<ExprNode*> Operands271;
	Operands271<<new Leaf("\\+");
	Tree27->set_Operands(Operands271);
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.27 Quantifier.\"n or m(the right range is left)\"")<<inputTable27<<out_errorEmpty<<res_errorEmpty<<Tree27;

	//Номер: 28
	//Аргумент. Escape character under the slash.
	////////////Входная строка///////////////////
	QStringList inputTable28;
	inputTable28 << "\\\\";
	//////////////Дерево/////////////////////////
	ExprNode* Tree28 = new Leaf("\\\\");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.28 Leaf.  Escape character under the slash")<<inputTable28<<out_errorEmpty<<res_errorEmpty<<Tree28;

	//Номер: 29
	//Аргумент. Экранируется экранируемый символ один раз.
	////////////Входная строка///////////////////
	QStringList inputTable29;
	inputTable29 << "[\\\\\\\\\\]a-z\\]\\\\\\]\\\\]";
	//////////////Дерево/////////////////////////
	ExprNode* Tree29 = new Leaf("[\\\\\\\\\\]a-z\\]\\\\\\]\\\\]");
	//////////////Лист Ошибок////////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.29.1 Leaf.  Shielding screening symbol once.")<<inputTable29<<out_errorEmpty<<res_errorEmpty<<Tree29;

	//Номер: 30
	//Аргумент. Экранируется экранируемый символ один раз.
	////////////Входная строка///////////////////
	QStringList inputTable30;
	inputTable30 << "[a-z\\\\\\]";
	//////////////Дерево/////////////////////////
	//////////////Лист Ошибок////////////////////
	QStringList out_error30;
	QStringList res_error30;
	res_error30<<QString::fromStdWString(std::wstring(L"Ошибка! Лексема \"[a-z\\\\\\]\" не опознана. Номер лексемы: 0."));
	/////////Заполнить тест//////////////////////
	QTest::newRow("1.29.2 Leaf.  Shielding screening symbol once.")<<inputTable30<<out_error30<<res_error30<<TreeNULL;
}


void TestClass::testTextRegExpToTree()
{
	QFETCH(QStringList, textTree);
	QFETCH(QStringList, output_error);
	QFETCH(QStringList, result_error);
	QFETCH(ExprNode*, result_Tree);
	QString message = QString("");

	bool its_ok = 1;

	ExprNode* output_Tree=textRegexpToTree(textTree,output_error);
	if (output_Tree!=NULL || result_Tree!=NULL)
	{
		its_ok=cmpTree(result_Tree,output_Tree,message);
	}
	else if (output_error!=result_error)
	{
		message+="Error: Error messages do not match.\n";
		message+=output_error[0] + "\n";
		message+=result_error[0];
		its_ok=false;
	}
	deleteTree(output_Tree);
	deleteTree(result_Tree);
	QVERIFY2(its_ok, message.toUtf8().constData());
}

void TestClass::testCreateTextLeaf_data()
{
	//input
	QTest::addColumn<Leaf*>("nodeTree");
	//output
	QTest::addColumn<QString>("textTree"); 

	QTest::newRow("2.1 Leaf.  Character class \"letter or number\"")                               <<new Leaf("[:alnum:]")<<QString("[:alnum:]");
	QTest::newRow("2.2 Leaf.  Character class \"letter\"")                                         <<new Leaf("[:alpha:]")<<QString("[:alpha:]");
	QTest::newRow("2.3 Leaf.  Character class \"characters with codes 0 - 127\"")                  <<new Leaf("[:ascii:]")<<QString("[:ascii:]");
	QTest::newRow("2.4 Leaf.  Character class \"space or tab character\"")                         <<new Leaf("[:blank:]")<<QString("[:blank:]");
	QTest::newRow("2.5 Leaf.  Character class \"control characters\"")                             <<new Leaf("[:cntrl:]")<<QString("[:cntrl:]");
	QTest::newRow("2.6 Leaf.  Character class \"number\"")                                         <<new Leaf("[:digit:]")<<QString("[:digit:]");
	QTest::newRow("2.7 Leaf.  Character class \"printed character is not a space\"")               <<new Leaf("[:graph:]")<<QString("[:graph:]");
	QTest::newRow("2.8 Leaf.  Character class \"lowercase letter\"")                               <<new Leaf("[:lower:]")<<QString("[:lower:]");
	QTest::newRow("2.9 Leaf.  Character class \"printed characters\"")                             <<new Leaf("[:print:]")<<QString("[:print:]");
	QTest::newRow("2.10 Leaf.  Character class \"printed characters are not letters and numbers\"")<<new Leaf("[:punct:]")<<QString("[:punct:]");
	QTest::newRow("2.11 Leaf.  Character class \"space character\"")                               <<new Leaf("[:space:]")<<QString("[:space:]");
	QTest::newRow("2.12 Leaf.  Character class \"uppercase letters\"")                             <<new Leaf("[:upper:]")<<QString("[:upper:]");
	QTest::newRow("2.13 Leaf.  Character class \"word symbols\"")                                  <<new Leaf("[:word:]")<<QString("[:word:]");
	QTest::newRow("2.14 Leaf.  Character class \"hexadecimal digits\"")                            <<new Leaf("[:xdigit:]")<<QString("[:xdigit:]");
	QTest::newRow("2.15 Leaf.  The screening symbol \"\\d\"")                                      <<new Leaf("\\d")<<QString("\\d");
	QTest::newRow("2.16 Leaf.  The screening symbol \"\\D\"")                                      <<new Leaf("\\D")<<QString("\\D");
	QTest::newRow("2.17 Leaf.  The screening symbol \"\\w\"")                                      <<new Leaf("\\w")<<QString("\\w");
	QTest::newRow("2.18 Leaf.  The screening symbol \"\\W\"")                                      <<new Leaf("\\W")<<QString("\\W");
	QTest::newRow("2.19 Leaf.  The screening symbol \"\\s\"")                                      <<new Leaf("\\s")<<QString("\\s");
	QTest::newRow("2.20 Leaf.  The screening symbol \"\\S\"")                                      <<new Leaf("\\S")<<QString("\\S");
	QTest::newRow("2.21 Leaf.  The screening symbol \"\\t\"")                                      <<new Leaf("\\t")<<QString("\\t");
	QTest::newRow("2.22 Leaf.  The screening symbol \"\\r\"")                                      <<new Leaf("\\r")<<QString("\\r");
	QTest::newRow("2.23 Leaf.  The screening symbol \"\\n\"")                                      <<new Leaf("\\n")<<QString("\\n");
	QTest::newRow("2.24 Leaf.  The screening symbol \"\\v\"")                                      <<new Leaf("\\v")<<QString("\\v");
	QTest::newRow("2.25 Leaf.  Empty")                                                             <<new Leaf("empty")<<QString("");
	QTest::newRow("2.26 Leaf.  Dot")                                                               <<new Leaf(".")<<QString(".");
	QTest::newRow("2.27 Leaf.  Space")                                                             <<new Leaf("\\_")<<QString(" ");
	QTest::newRow("2.28 Leaf.  The screening dot")                                                 <<new Leaf("\\.")<<QString("\\.");
	QTest::newRow("2.29 Leaf.  digits")                                                            <<new Leaf("123")<<QString("123");
	QTest::newRow("2.30 Leaf.  Alpha")                                                             <<new Leaf("G")<<QString("G");
	QTest::newRow("2.31 Leaf.  Range")                                                             <<new Leaf("[A-Z]")<<QString("[A-Z]");
	QTest::newRow("2.32 Leaf.  Сomplicated range")                                                 <<new Leaf("[01[:alpha:]%]")<<QString("[01[:alpha:]%]");
	QTest::newRow("2.33 Leaf.  Сomplicated range. Shielding screening symbol once._1")             <<new Leaf("[abc\\]]")<<QString("[abc\\]]");
	QTest::newRow("2.34 Leaf.  Сomplicated range. Shielding screening symbol once._2")             <<new Leaf("[abc\\\\]")<<QString("[abc\\\\]");
	QTest::newRow("2.35 Leaf.  Сomplicated range. Shielding screening symbol once._3")             <<new Leaf("[sd\\\\\\]]")<<QString("[sd\\\\\\]]");
}

void TestClass::testCreateTextLeaf()
{
	QFETCH(Leaf*, nodeTree);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(4);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}
	delete nodeTree;
	QVERIFY2(its_ok, message.toUtf8().constData());
}

void TestClass::testCreateTextConcatenation_data()
{
	//input
	QTest::addColumn<ExprNode*>("nodeTree");
	QTest::addColumn<int>("prec");
	//output
	QTest::addColumn<QString>("textTree"); 

	QStringList tmp;
	QStringList tmp1;
	ExprNode* Tree;

	//Номер: 1
	////////////Входное дерево///////////////////
	tmp<< "[A-B]" << "1" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.1 The concatenation with one operand and priority is greater than that of the parent.")<<Tree<< 2 <<QString("[A-B]");

	//Номер: 2
	////////////Входное дерево///////////////////
	tmp<< "[A-C]" << "c" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.2 The concatenation with multiple operands and priority is greater than that of the parent.")<<Tree<< 2 <<QString("(?:[A-C]c)");

	//Номер: 3
	////////////Входное дерево///////////////////
	tmp<< "1" << "empty" << "[:print:]" << "3" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.3 A concatenation with multiple operands (one of which is empty) and a priority is less than that of the parent.")<<Tree<< 4 <<QString("1[:print:]");

	//Номер: 4
	////////////Входное дерево///////////////////
	tmp<< "a" << "b" << "2" << "|" << "[:print:]" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.4 Concatenation with multiple operands, as an argument, is accepted by the operator as an alternative.")<<Tree<< 4 <<QString("(?:a|b)[:print:]");

	//Номер: 5
	////////////Входное дерево///////////////////
	tmp<< "1" << "2" << "2" << "&" << "[:print:]" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.5 Concatenation with multiple operands, as arguments, takes the operator concatenation.")<<Tree<< 4 <<QString("12[:print:]");
	
	//Номер: 6
	////////////Входное дерево///////////////////
	tmp<< "1" << "*" << "[:print:]" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.6 A concatenation with multiple operands, as arguments, is accepted by a quantifier operator without an operand.")<<Tree<< 4 <<QString("1*[:print:]");

	//Номер: 7
	////////////Входное дерево///////////////////
	tmp<< "[:print:]" << "\\w" << "4" << "{}" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.7 A concatenation with several operands, as arguments, is accepted by the quantifier operator \"n times \".")<<Tree<< 4 <<QString("[:print:]\\w{4}");

	//Номер: 8
	////////////Входное дерево///////////////////
	tmp<< "[:print:]" << "\\b" << "4" << "6" << "{,}" << "2" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.8 A concatenation with several operands, as arguments, is accepted by the quantifier operator \"from n to m times\".")<<Tree<< 4 <<QString("[:print:]\\b{4,6}");

	//Номер: 9
	////////////Входное дерево///////////////////
	tmp << "\\+" << "\\(" << "\\?" << ":" << "4" << "&";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("3.9 Concatenation with multiple operands, accepts escaped service characters as arguments.")<<Tree<< 4 <<QString("\\+\\(\\?:");
}

void TestClass::testCreateTextConcatenation()
{
	QFETCH(ExprNode*, nodeTree);
	QFETCH(int, prec);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(prec);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}

	deleteTree(nodeTree);
	QVERIFY2(its_ok, message.toUtf8().constData());

}

void TestClass::testCreateTextAlternative_data()
{
	//input
	QTest::addColumn<ExprNode*>("nodeTree");
	QTest::addColumn<int>("prec");
	//output
	QTest::addColumn<QString>("textTree"); 

	QStringList tmp;
	QStringList tmp1;
	ExprNode* Tree;

	//Номер: 1
	////////////Входное дерево///////////////////
	tmp<< "[A-B]" << "1" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.1 An alternative with one operand and priority is greater than that of the parent.")<<Tree<< 1 <<QString("(?:[A-B]|)");

	//Номер: 2
	////////////Входное дерево///////////////////
	tmp<< "[5-7]" << "c" << "\\\\" << "3" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.2 An alternative with multiple operands and priority is greater than that of the parent.")<<Tree<< 1 <<QString("(?:[5-7]|c|\\\\)");

	//Номер: 3
	////////////Входное дерево///////////////////
	tmp<< "1" << "empty" << "[:print:]" << "3" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.3 An alternative with several operands (one of which is empty) and a priority is less than that of the parent.")<<Tree<< 1 <<QString("(?:1|[:print:]|)");
		
	//Номер: 4
	////////////Входное дерево///////////////////
	tmp<< "3" << "4" << "2" << "&" << "[:print:]" << "2" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.4 An alternative with multiple operands, the operator accepts the concatenation as arguments.")<<Tree<< 4 <<QString("34|[:print:]");

	//Номер: 5
	////////////Входное дерево///////////////////
	tmp<< "1" << "2" << "2" << "|" << "[:print:]" << "2" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.5 An alternative with several operands, the alternative operator takes as arguments.")<<Tree<< 4 <<QString("1|2|[:print:]");

	//Номер: 6
	////////////Входное дерево///////////////////
	tmp<< "1" << "*" << "[:print:]" << "2" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.6 An alternative with multiple operands, as arguments, is accepted by the quantifier operator without an operand")<<Tree<< 4 <<QString("1*|[:print:]");

	//Номер: 7
	////////////Входное дерево///////////////////
	tmp<< "[:print:]" << "\\w" << "4" << "{}" << "2" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.7 An alternative with several operands, as arguments, is accepted by the quantifier operator \"n times\".")<<Tree<< 4 <<QString("[:print:]|\\w{4}");

	//Номер: 8
	////////////Входное дерево///////////////////
	tmp<< "[:print:]" << "\\b" << "4" << "6" << "{,}" << "2" << "|";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("4.8 An alternative with several operands, takes the quantifier operator \"from n to m times\" as arguments.")<<Tree<< 4 <<QString("[:print:]|\\b{4,6}");

}
void TestClass::testCreateTextAlternative()
{
	QFETCH(ExprNode*, nodeTree);
	QFETCH(int, prec);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(prec);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}

	deleteTree(nodeTree);
	QVERIFY2(its_ok, message.toUtf8().constData());

}

void TestClass::testCreateTextQuantNoOper_data()
{
	//input
	QTest::addColumn<ExprNode*>("nodeTree");
	QTest::addColumn<int>("prec");
	//output
	QTest::addColumn<QString>("textTree"); 

	QStringList tmp;
	QStringList tmp1;
	ExprNode* Tree;

	//Номер: 1
	////////////Входное дерево///////////////////
	tmp<< "[A-B]" << "*";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.1 The quantifier is \"0 or more times\".")<<Tree<< 3 <<QString("[A-B]*");

	//Номер: 2
	////////////Входное дерево///////////////////
	tmp<< "\\w" << "+";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.2 The quantifier is \"1 or more times\".")<<Tree<< 3 <<QString("\\w+");

	//Номер: 3
	////////////Входное дерево///////////////////
	tmp<< "[:print:]" << "?";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.3 The quantifier is \"0 or 1 times\".")<<Tree<< 4 <<QString("[:print:]?");

	//Номер: 4
	////////////Входное дерево///////////////////
	tmp<< "a" << "?" << "*";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.4 The quantifier \"0 or more times\" accepts another quantifier as an argument.")<<Tree<< 4 <<QString("a?*");

	//Номер: 5
	////////////Входное дерево///////////////////
	tmp<< "empty" << "*";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.5 The quantifier \"0 or more times\" as an argument takes \"empty\".")<<Tree<< 4 <<QString("");

	//Номер: 6
	////////////Входное дерево///////////////////
	tmp<< "\\w" << "1" << "2" << "&" << "*";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.6 The quantifier \"0 or more times\" as an argument receives a concatenation of several characters.")<<Tree<< 4 <<QString("(?:\\w1)*");

	//Номер: 7
	////////////Входное дерево///////////////////
	tmp<< "\\w" << "1" << "2" << "|" << "*";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.7 The quantifier \"0 or more times\" as an argument receives an alternative with several operators.")<<Tree<< 4 <<QString("(?:\\w|1)*");

	//Номер: 8
	////////////Входное дерево///////////////////
	tmp<< "a" << "*" << "?";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.8 The quantifier \"0 or 1 times\" as an argument receives the quantifier \"0 or more times\".")<<Tree<< 4 <<QString("(?:a*)?");

	//Номер: 9
	////////////Входное дерево///////////////////
	tmp<< "a" << "+" << "?";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.9 The quantifier \"0 or 1 times\" as an argument receives the quantifier \"1 or more times\".")<<Tree<< 4 <<QString("(?:a+)?");

	//Номер: 10
	////////////Входное дерево///////////////////
	tmp<< "a" << "2" << "3" << "{,}" << "?";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.10 The quantifier \"0 or 1 times\" as an argument receives the quantifier \"from n to m times\".")<<Tree<< 4 <<QString("(?:a{2,3})?");

	//Номер: 11
	////////////Входное дерево///////////////////
	tmp<< "a" << "2" << "3" << "{,}" << "+";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.11 The quantifier \"1 or more times\" as an argument receives the quantifier \"from n to m times\".")<<Tree<< 4 <<QString("(?:a{2,3})+");

	//Номер: 12
	////////////Входное дерево///////////////////
	tmp<< "a" << "+" << "+";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.12 The quantifier \"1 or more times\" as an argument receives the quantifier \"1 or more times\".")<<Tree<< 4 <<QString("(?:a+)+");

	//Номер: 13
	////////////Входное дерево///////////////////
	tmp<< "a" << "*" << "+";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.13 The quantifier \"1 or more times\" as an argument receives the quantifier \"0 or more times\".")<<Tree<< 4 <<QString("(?:a*)+");

	//Номер: 14
	////////////Входное дерево///////////////////
	tmp<< "a" << "?" << "+";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("5.14 The quantifier \"1 or more times\" as an argument receives the quantifier \"0 or 1 times\".")<<Tree<< 4 <<QString("(?:a?)+");
}


void TestClass::testCreateTextQuantNoOper()
{
	QFETCH(ExprNode*, nodeTree);
	QFETCH(int, prec);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(prec);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}

	deleteTree(nodeTree);
	QVERIFY2(its_ok, message.toUtf8().constData());

}


void TestClass::testCreateTextQuantN_data()
{
	//input
	QTest::addColumn<ExprNode*>("nodeTree");
	QTest::addColumn<int>("prec");
	//output
	QTest::addColumn<QString>("textTree"); 

	QStringList tmp;
	QStringList tmp1;
	ExprNode* Tree;

	//Номер: 1
	////////////Входное дерево///////////////////
	tmp<< "[A-B]" << "4" << "{}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("6.1 Quantifier \"n times\"")<<Tree<< 3 <<QString("[A-B]{4}");

	//Номер: 2
	////////////Входное дерево///////////////////
	tmp<< "a" << "?" << "4" << "{}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("6.2 The quantifier \"n times\" accepts another quantifier as an argument.")<<Tree<< 4 <<QString("a?{4}");

	//Номер: 3
	////////////Входное дерево///////////////////
	tmp<< "empty" << "3" << "{}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("6.3 The quantifier \"n times\" as an argument takes \"empty\".")<<Tree<< 4 <<QString("");

	//Номер: 4
	////////////Входное дерево///////////////////
	tmp<< "\\w"<< "1" << "2"<< "&" << "4"<< "{}" ;
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("6.4 The quantifier \"n times\" as an argument gets a concatenation of several symbols.")<<Tree<< 4 <<QString("(?:\\w1){4}");

	//Номер: 5
	////////////Входное дерево///////////////////
	tmp<< "\\w"<< "1" << "2"<< "|" << "4"<< "{}" ;
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("6.5 The quantifier \"n times\" as an argument gets an alternative with several operators.")<<Tree<< 4 <<QString("(?:\\w|1){4}");
}

void TestClass::testCreateTextQuantN()
{
	QFETCH(ExprNode*, nodeTree);
	QFETCH(int, prec);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(prec);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}

	deleteTree(nodeTree);
	QVERIFY2(its_ok, message.toUtf8().constData());

}


void TestClass::testCreateTextQuantLR_data()
{
	//input
	QTest::addColumn<ExprNode*>("nodeTree");
	QTest::addColumn<int>("prec");
	//output
	QTest::addColumn<QString>("textTree"); 

	QStringList tmp;
	QStringList tmp1;
	ExprNode* Tree;

	//Номер: 1
	////////////Входное дерево///////////////////
	tmp<< "[A-B]" << "4" << "6" << "{,}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("7.1 Quantifier \"from n to m times\"")<<Tree<< 3 <<QString("[A-B]{4,6}");

	//Номер: 2
	////////////Входное дерево///////////////////
	tmp<< "a" << "?" << "4" << "infinity" << "{,}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("7.2 The quantifier \"from n to m times\" accepts another quantifier as an argument. (where m is infinity)")<<Tree<< 4 <<QString("a?{4,}");

	//Номер: 3
	////////////Входное дерево///////////////////
	tmp<< "empty" << "3" << "5" << "{,}";
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("7.3 The quantifier \"from n to m times\" takes as an argument \"empty\".")<<Tree<< 4 <<QString("");

	//Номер: 4
	////////////Входное дерево///////////////////
	tmp<< "\\w"<< "1" << "2"<< "&" << "zero"<< "5" << "{,}" ;
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("7.4 The quantifier \"from n to m times\" as an argument gets a concatenation of several symbols. (where n is zero)")<<Tree<< 4 <<QString("(?:\\w1){,5}");

	//Номер: 5
	////////////Входное дерево///////////////////
	tmp<< "\\w"<< "1" << "2"<< "|" << "zero"<< "infinity"<< "{,}" ;
	Tree=textRegexpToTree(tmp,tmp1);
	tmp.clear();
	////////////Входное дерево///////////////////
	/////////Заполнить тест//////////////////////
	QTest::newRow("7.5 The quantifier \"from n to m times\" as an argument gets an alternative with several operators.")<<Tree<< 4 <<QString("(?:\\w|1){,}");
}

void TestClass::testCreateTextQuantLR()
{
	QFETCH(ExprNode*, nodeTree);
	QFETCH(int, prec);
	QFETCH(QString, textTree);
	
	bool its_ok = 1;
	QString message = QString("");

	QString tmp = nodeTree->createText(prec);

	if (tmp!=textTree)
	{
		message+="\nError: The text of the node does not match the answer.";
		message+="\nExpected:"+ textTree;
		message+="   Output:"+ tmp;
		its_ok = 0;
	}

	deleteTree(nodeTree);
	QVERIFY2(its_ok, message.toUtf8().constData());

}