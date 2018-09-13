/*!
* \file      main.cpp
* \brief     Главная функция
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      24 июня 2018 
* \mainpage Построение текста регулярного выражения по его синтаксическому дереву
* <p>Разработка ведется на основании задания на курсовой проект по дисциплине «Качество и надёжность программного обеспечения», выданного доцентом кафедры ПОАС Сычевым О.А. 13 февраля 2018 г.
* <p>Поддерживаемые операции в регулярных выражениях:
* - квантификаторы;
* - конкатенация;
* - альтернатива.
* <p>Поддерживаемые операнды в регулярных выражениях:
* - последовательность символов, которые не являются операциями;
* - символьные классы;
* - meta-символ точки;
* - escape-символы и последовательности.
*/


#include <QtCore/QCoreApplication>
#include "TestClass.h"
#include "WriteRead.h"
#include <vld.h>
#include <iostream>
#include <iostream>

int main(int argc, char *argv[])
{
	QString key = QString(argv[1]);
	
	if (key=="-t" && argc==2)
	{
		TestClass it;
		QTest::qExec(&it);
	}
	else if (key=="-f" && argc==3)
	{
		QString nameFile= QString(argv[2]);
		QString RegExp;
		QString textTree=readFile(QString(nameFile));
		QStringList error;

		if (textTree==NULL)
		{
			error<< QString::fromStdWString(std::wstring(L"Ошибка! Чтение файла не произошло."));
			writeError(error);
		}
		else 
		{
			QStringList tableLexam = textTree.split(' ');
			ExprNode *Tree=textRegexpToTree(tableLexam,error);
			if(error.size()==0)
			{
				RegExp = Tree->createText(4);
				writeFile(RegExp);
			}else 
				writeError(error);
			deleteTree(Tree);
		}
	}else 
	{
		QStringList error;
		error<< QString::fromStdWString(std::wstring(L"Ошибка! Входные параметры не соответствует ожидаемым."));
		writeError(error);
	}

	//system("pause");
	return 0;
}
