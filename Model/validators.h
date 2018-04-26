#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <QList>
#include <QPlainTextEdit>
#include <QRegExp>
#include <QString>
#include <QPlainTextEdit>
#include <sstream>
#include <string>
#include <QTime>

#include <QDebug>

class InputValidator
{
    InputValidator();

public:
    static QRegExp *userNameExpr;
    static QRegExp *phoneNumberExpr;
    static QRegExp *publicationDateExpr;

    static bool isValidUserName(QString userName);
    static bool isValidPhoneNumber(QString phoneNumber);
    static bool isValidDate(QDate *date);
};

class StringManager {};
#endif // VALIDATORS_H
