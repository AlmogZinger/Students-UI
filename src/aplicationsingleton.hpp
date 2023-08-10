//
// Created by almog on 8/10/23.
//

#ifndef MYQTPROJECT_APLICATIONSINGLETON_HPP
#define MYQTPROJECT_APLICATIONSINGLETON_HPP
#include "graphql/__generated__/AddStudentMutation.hpp"

#include "graphql/__generated__/AddStudentMutation.hpp"
#include "graphql/__generated__/StudentsQuery.hpp"
#include <QObject>
#include <QQmlEngine>
#include <QtQmlIntegration>

class ApplicationSingleton : public QObject {
  Q_OBJECT
  QML_ELEMENT
  std::shared_ptr<Students::addstudentmutation::AddStudentMutation>
      add_student_mut;

public:
  להוסיף גם לקווארי אותו דבר ApplicationSingleton() {
    add_student_mut =
        Students::addstudentmutation::AddStudentMutation::shared();
  }
public slots:
  זה הפונקתייה שהqml שולח void addStudentCpp(const QString &name,
                                             QDate birthday) {
    add_student_mut->set_variables(
        {.g_name = name,
         .g_birthDate = qtgql::customscalars::DateScalar(birthday)});
    add_student_mut->fetch();
  }
};

#endif // MYQTPROJECT_APLICATIONSINGLETON_HPP
