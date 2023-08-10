#pragma once
#include "graphql/__generated__/AddStudentMutation.hpp"
#include "graphql/__generated__/StudentsQuery.hpp"
#include <QObject>
#include <QQmlEngine>
#include <QtQmlIntegration>

class App : public QObject {
  Q_OBJECT
  QML_ELEMENT
  std::shared_ptr<Students::addstudentmutation::AddStudentMutation>
      m_add_student_mut;
  std::shared_ptr<Students::studentsquery::StudentsQuery> m_students_query;
  Q_PROPERTY(const Students::studentsquery::StudentsQuery *students_query READ
                 get_students_query CONSTANT)
  Q_PROPERTY(const Students::addstudentmutation::AddStudentMutation
                 *add_student_mut READ get_add_student_mut CONSTANT)

public:
  App() {
    m_add_student_mut =
        Students::addstudentmutation::AddStudentMutation::shared();
    m_students_query = Students::studentsquery::StudentsQuery::shared();
    m_students_query->fetch();
  }

  const Students::studentsquery::StudentsQuery *get_students_query() {
    return m_students_query.get();
  }
  const Students::addstudentmutation::AddStudentMutation *
  get_add_student_mut() {
    return m_add_student_mut.get();
  }

public slots:
  void addStudentCpp(const QString &name, QDate birthday) {
    m_add_student_mut->set_variables(
        {.g_name = name,
         .g_birthDate = qtgql::customscalars::DateScalar(birthday)});
    m_add_student_mut->fetch();
    m_students_query->refetch();
  }
};
