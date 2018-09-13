/*!
* \file      WriteRead.h
* \brief     Функции работы с файлами.
* \author    Зубков Александр Владимирович (zubkov.alexander.v@gmail.com)
* \version   0.01(development)
* \data      22 июня 2018 
*/
#ifndef WRITEREAD_H
#define WRITEREAD_H

#include <QTextStream>
#include <QTextCodec>
#include <QDateTime>
#include <qfile.h>
#include <qstring.h>

/*!
* Функция считывания из файла в строку.
* \param[in] filename - название файла
* \return возвращает строку с данными из файла 
*/
QString readFile(QString &filename);

/*!
* Функция считывания в файл из строки.
* \param[in] text - текст для записи в файл
*/
void writeFile(QString &text);

/*!
* Функция считывания в файл из листа строк.
* \param[in] text - текст для записи в файл
*/
void writeError(QStringList &error);

#endif // WRITEREAD_H