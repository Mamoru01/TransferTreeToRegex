/*!
* \file      textRegExpToTree.cpp
* \brief     Ркализация функции создания дерева классов по обратной польской нотации.
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      7 июня 2018 
*/
#include "textRegExpToTree.h"
#include <qstack.h>
#include <qregexp.h>
#include <iostream>
#include <string>

ExprNode *textRegexpToTree(QStringList & table_lexems, QStringList &error)
{	
	QStack<ExprNode*>	stack;
	ExprNode* tmpNode;
	errorQuant errorQ;
	bool flagNumber;
	int number;
	QList<ExprNode*> tmpOperands;


	for (int i=0;i<table_lexems.size() && error.size()==0;i++)
	{

		if ( isAlternative(table_lexems[i]))
		{
			if (stack.size()>1)
			{
				number = table_lexems[i-1].toInt(&flagNumber);
				if (flagNumber && number<stack.size())
				{		
					delete  stack[stack.size()-1];
					stack.pop_back();
					for (int i=0;i<number;i++)
					{
						tmpOperands << stack[stack.size()-1];
						stack.pop_back();
					}
					tmpNode = new Alternative ();
					revers(tmpOperands);
					tmpNode->set_Operands(tmpOperands);
					stack.push_back(tmpNode);
					tmpOperands.clear();
				}else 
				{
					if (flagNumber)
					{
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
					}else
					{
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Лексема \"%1\" не опознана. Номер лексемы: %2."))).arg(table_lexems[i-1]).arg(QString::number(i-1));	
					}
				}
			}else 
			{
				error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
			}
		}else if ( isConcatenation(table_lexems[i]))
		{
			if (stack.size()>1)
			{
				number = table_lexems[i-1].toInt(&flagNumber);
				if (flagNumber && number<stack.size())
				{
					delete  stack[stack.size()-1];
					stack.pop_back();
					for (int i=0;i<number;i++)
					{
						tmpOperands << stack[stack.size()-1];
						stack.pop_back();
					}
					tmpNode = new Concatenation ();
					revers(tmpOperands);
					tmpNode->set_Operands(tmpOperands);
					stack.push_back(tmpNode);
					tmpOperands.clear();
				}else 
				{
					if (flagNumber)
					{
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
					}else
					{
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Лексема \"%1\" не опознана. Номер лексемы: %2."))).arg(table_lexems[i-1]).arg(QString::number(i-1));	
					}
				}
			}else 
			{
				error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
			}
		}
		else if (isQuantifierN(table_lexems[i]))
		{
			if (stack.size()<2)
			{
				error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
			}else
			{
				tmpNode = new QuantifierN (stack[stack.size()-1]->get_node(),errorQ);
				switch(errorQ){
					case (errorQuant::no_mistakes):
						tmpOperands << stack[stack.size()-2];
						tmpNode->set_Operands(tmpOperands);
						delete  stack[stack.size()-1];
						stack.pop_back();
						stack[stack.size()-1]=tmpNode;
						tmpOperands.clear();
					break;
					case (errorQuant::N_does_not_exist):
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Количество повторений не может принимать \"%1\". Номер лексемы: %2."))).arg(table_lexems[i-1]).arg(QString::number(i-1));
						delete tmpNode;
					}
			}
		}
		else if (isQuantifierLR(table_lexems[i]))
		{
			if (stack.size()<3)
			{
				error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
			}else
			{
				tmpNode = new QuantifierLR (stack[stack.size()-2]->get_node(),stack[stack.size()-1]->get_node(),errorQ);
				switch(errorQ){
					case (errorQuant::no_mistakes):
						tmpOperands << stack[stack.size()-3];
						tmpNode->set_Operands(tmpOperands);
						delete  stack[stack.size()-2];
						delete  stack[stack.size()-1];
						stack.pop_back();
						stack.pop_back();
						stack[stack.size()-1]=tmpNode;
						tmpOperands.clear();
					break;
					case (errorQuant::left_argument_does_not_exist):
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Левый диапазон не может принимать \"%1\". Номер лексемы: %2."))).arg(table_lexems[i-2]).arg(QString::number(i-2));
						delete tmpNode;
					break;
					case (errorQuant::right_argument_does_not_exist):
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Правый диапазон не может принимать \"%1\". Номер лексемы: %2."))).arg(table_lexems[i-1]).arg(QString::number(i-1));
						delete tmpNode;
					break;
					case (errorQuant::left_argument_more_right):
						error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Левый аргумент квантификатор не может быть больше правого. Номер лексемы: %1,%2."))).arg(QString::number(i-2)).arg(QString::number(i-1));
						delete tmpNode;
					break;
					}
			}
		}
		else if(isQuantifierNoOper(table_lexems[i]))
		{
			if (stack.size()<1)
			{
				error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Не полное количество операндов для оператора \"%1\".\nНомер лексемы:%2."))).arg(table_lexems[i]).arg(QString::number(i));
			}else
			{
				tmpNode = new QuantifierNoOper(table_lexems[i]);
				tmpOperands << stack[stack.size()-1];
				tmpNode->set_Operands(tmpOperands);
				stack[stack.size()-1]=tmpNode;
				tmpOperands.clear();
			}
		}
		else if(isLeaf(table_lexems[i]))
		{
			stack << new Leaf(table_lexems[i]);
		}
		else 
			error << QString(QString::fromStdWString(std::wstring(L"Ошибка! Лексема \"%1\" не опознана. Номер лексемы: %2."))).arg(table_lexems[i]).arg(QString::number(i));	
	}



	if (error.size())
	{
		for (int i=0;i<stack.size();i++)
			deleteTree(stack.at(i));
		return NULL;
	}
	else 
	{
		for (int i=1;i<stack.size();i++)
			deleteTree(stack.at(i));
		return stack[0];
	}
}

bool isAlternative(QString & lexem)
{
	return (lexem=="|")?true:false;
}

bool isConcatenation(QString & lexem)
{
	return (lexem=="&")?true:false;
}

bool isQuantifierLR(QString & lexem)
{
	return (lexem=="{,}")?true:false;
}

bool isQuantifierN(QString & lexem)
{
	return (lexem=="{}")?true:false;
}

bool isQuantifierNoOper(QString & lexem)
{
	QStringList lexemsOper;
	lexemsOper << "*" << "?" << "+";
	bool quant=false;

	for (int i=0;i<lexemsOper.size();i++)
		if (lexemsOper[i]==lexem)
			quant = true;
	return quant;
}

bool isLeaf(QString & lexem)
{
	bool leaf=false;
	QStringList escapeClass;
	escapeClass <<"empty" << "zero" << "infinity";

	lexem.toInt(&leaf);

	for (int i=0;i<escapeClass.size();i++)
	{
		if (escapeClass[i]==lexem)
			leaf=true;
	}
	
	if (lexem.size()==2 && lexem[0] == '\\')
		leaf=true;

	if (lexem.size()==1 && lexem != "\\")
		leaf=true;

	if (lexem.at(0)=="[" && lexem.at(lexem.size()-1)=="]")
	{
		bool its_ok = true;
		int numberSlashes = 0;
		int index = lexem.indexOf("]");

		while(index !=-1 && its_ok == true && index != lexem.size()-1)
		{
			numberSlashes = 0;
			
			while(lexem[index-numberSlashes-1]=='\\')
				numberSlashes++;

			if (numberSlashes%2==0)
				 its_ok =false;

			index = lexem.indexOf("]",index+1);
		} 

		while(lexem[index-numberSlashes-1]=='\\')
			numberSlashes++;

		if (numberSlashes%2==1)
			its_ok =false;
		
		leaf=its_ok;
	}
	
	return leaf;
}

void deleteTree(ExprNode * Tree)
{
	if (Tree!=NULL){
		for (int i=0;i<Tree->get_Operands()->size();i++)
		{
			deleteTree(Tree->get_Operands()->at(i));
		}
		delete Tree;
	}
}


void revers(QList<ExprNode*> & tmp)
{	
	QList<ExprNode*>  tmp1;
	for (int i=0; i<tmp.size();i++)
	{
		tmp1.push_back(tmp[tmp.size()-1-i]);
	}
	tmp=tmp1;
}