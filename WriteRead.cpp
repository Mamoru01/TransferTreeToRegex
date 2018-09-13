/*!
* \file      WriteRead.cpp
* \brief     Функции работы с файлами.
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      22 июня 2018 
*/
#include "WriteRead.h"


QString readFile(QString &filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return NULL;


	QByteArray total;
	QByteArray line;
	while (!file.atEnd()) {
		line = file.read(1024);
		total.append(line);
	}

	file.close();
	return QString(total);
}

void writeFile(QString &text)
{

	QFile file("result" +  QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm_ss_zzz") + ".txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return ;

	QTextStream stream( &file );
	stream.setCodec("Windows-1251");
    stream << text << endl;

	file.close();
}

void writeError(QStringList &error)
{
	QFile file("result" + QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm_ss_zzz") + ".txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return ;

	QTextStream stream( &file );
	
	for(int i=0;i<error.size();i++)
		stream << error.at(i) << endl;
	
	file.close();
}