/*!
* \file      WriteRead.h
* \brief     ������� ������ � �������.
* \author    ������ ��������� ������������ (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      22 ���� 2018 
*/
#ifndef WRITEREAD_H
#define WRITEREAD_H

#include <QTextStream>
#include <QTextCodec>
#include <QDateTime>
#include <qfile.h>
#include <qstring.h>

/*!
* ������� ���������� �� ����� � ������.
* \param[in] filename - �������� �����
* \return ���������� ������ � ������� �� ����� 
*/
QString readFile(QString &filename);

/*!
* ������� ���������� � ���� �� ������.
* \param[in] text - ����� ��� ������ � ����
*/
void writeFile(QString &text);

/*!
* ������� ���������� � ���� �� ����� �����.
* \param[in] text - ����� ��� ������ � ����
*/
void writeError(QStringList &error);

#endif // WRITEREAD_H