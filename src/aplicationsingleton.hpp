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
  Q_PROPERTY(Students::studentsquery::StudentsQuery *studentsQuery READ
                 get_students_query CONSTANT)
  Q_PROPERTY(Students::addstudentmutation::AddStudentMutation
                 *addStudentMutation READ get_add_student CONSTANT)
  std::shared_ptr<Students::addstudentmutation::AddStudentMutation>
      m_add_student_mut;
  std::shared_ptr<Students::studentsquery::StudentsQuery> m_students_query;

public:
  ApplicationSingleton() {
    m_add_student_mut =
        Students::addstudentmutation::AddStudentMutation::shared();
    m_students_query = Students::studentsquery::StudentsQuery::shared();
    m_students_query->fetch();
  }
  auto get_students_query() { return m_students_query.get(); }
  auto get_add_student() { return m_add_student_mut.get(); }

public slots:

  void add_student(const QString &name, const QDate &birthday) {
    m_add_student_mut->set_variables(
        {.g_name = name,
         .g_birthDate = qtgql::customscalars::DateScalar(birthday)});
    if (m_add_student_mut->completed())
      m_add_student_mut->refetch();
    else
      m_add_student_mut->fetch();
  }
};

#endif // MYQTPROJECT_APLICATIONSINGLETON_HPP
