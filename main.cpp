/*!
* \file      main.cpp
* \brief     ������� �������
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      24 ���� 2018 
* \mainpage ���������� ������ ����������� ��������� �� ��� ��������������� ������
* <p>���������� ������� �� ��������� ������� �� �������� ������ �� ���������� ��������� � ��������� ������������ ������������, ��������� �������� ������� ���� ������� �.�. 13 ������� 2018 �.
* <p>�������������� �������� � ���������� ����������:
* - ��������������;
* - ������������;
* - ������������.
* <p>�������������� �������� � ���������� ����������:
* - ������������������ ��������, ������� �� �������� ����������;
* - ���������� ������;
* - meta-������ �����;
* - escape-������� � ������������������.
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
			error<< QString::fromStdWString(std::wstring(L"������! ������ ����� �� ���������."));
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
		error<< QString::fromStdWString(std::wstring(L"������! ������� ��������� �� ������������� ���������."));
		writeError(error);
	}

	//system("pause");
	return 0;
}
