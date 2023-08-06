//
// Created by almog on 8/6/23.
//

#ifndef MYQTPROJECT_TEST_HPP
#define MYQTPROJECT_TEST_HPP


#include <QString>

class Test {
    Q_PROPERTY(QString subject READ subject WRITE setSubject NOTIFY nameChanged)
    Q_PROPERTY(int grade READ grade WRITE setGrade NOTIFY nameChanged)
public:
    Test(QJsonObject & object);

//------Setters and Getters--------
    const QString &subject() const;

    void setSubject(const QString &mSubject);

    int grade() const;

    void setGrade(int mGrade);
    //---------------------------------

signals:
    void subjectChanged();
    void gradeChange();
private:
    QString m_subject;
    int m_grade;
};


#endif //MYQTPROJECT_TEST_HPP
