//
// Created by almog on 8/6/23.
//

#include <QJsonObject>
#include "Test.hpp"


//Json constructor
Test::Test(QJsonObject  & object) {
    qDebug()<<object <<" this is test constructor \n";
    m_grade = object["grade"].toInt();
    m_subject = object["subject"].toString();

}
const QString &Test::subject() const {
    return m_subject;
}

void Test::setSubject(const QString &mSubject) {
    m_subject = mSubject;
  //  emit subjectChanged();
}

int Test::grade() const {
    return m_grade;
}

void Test::setGrade(int mGrade) {
    m_grade = mGrade;
    //emit gradeChange();
}

