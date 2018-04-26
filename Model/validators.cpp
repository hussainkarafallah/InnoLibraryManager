#include "Model/validators.h"

InputValidator::InputValidator() {}

QRegExp *InputValidator::userNameExpr =
    new QRegExp("[A-Z][a-z]{1,9} [A-Z][a-z]{1,9}");

QRegExp *InputValidator::phoneNumberExpr = new QRegExp("\\d{11}");

bool InputValidator::isValidPhoneNumber(QString phonenumber) {
    return phoneNumberExpr->exactMatch(phonenumber);
}

bool InputValidator::isValidUserName(QString userName) {
    return userNameExpr->exactMatch(userName);
}

bool InputValidator::isValidDate(QDate *date)
{
    return date->isValid();
}


