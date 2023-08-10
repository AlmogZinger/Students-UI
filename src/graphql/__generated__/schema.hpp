#pragma once
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <memory>

#include <qtgql/bases/bases.hpp>
#include <qtgql/customscalars/customscalars.hpp>


namespace Students{


// ---------- INPUT OBJECTS ----------


// ---------- Interfaces ----------


// ---------- Object Types ----------
class Mutation;
class Query;
class Student;
class Test;


class Mutation :  public qtgql::bases::ObjectTypeABC {
Q_OBJECT
public:
std::map<std::tuple<QString,qtgql::customscalars::DateScalar>, std::shared_ptr<Student>>
 m_addStudent = {};
std::map<std::tuple<int,QString,int>, std::shared_ptr<Student>>
 m_submitTestResults = {};

signals:
void addStudentChanged();
void submitTestResultsChanged();


public:

[[nodiscard]] const std::shared_ptr<Student> &get_addStudent(std::tuple<QString,qtgql::customscalars::DateScalar> args )const{
return m_addStudent.at(args);
}
void set_addStudent(const std::shared_ptr<Student> & v, std::tuple<QString,qtgql::customscalars::DateScalar> args )
{
m_addStudent[args] = v;
emit addStudentChanged();
};

[[nodiscard]] const std::shared_ptr<Student> &get_submitTestResults(std::tuple<int,QString,int> args )const{
return m_submitTestResults.at(args);
}
void set_submitTestResults(const std::shared_ptr<Student> & v, std::tuple<int,QString,int> args )
{
m_submitTestResults[args] = v;
emit submitTestResultsChanged();
};



public:
 
[[nodiscard]] static Mutation* instance(){
static Mutation inst;
return &inst;
}


Mutation()= default;

public:
inline const QString & __typename() const final{
static const QString ret = "Mutation";
return ret;
};
};
class Query :  public qtgql::bases::ObjectTypeABC {
Q_OBJECT
public:
std::vector<std::shared_ptr<Student>>
 m_students = {};

signals:
void studentsChanged();


public:

[[nodiscard]] const std::vector<std::shared_ptr<Student>> &get_students()const{
return m_students;
}
void set_students(const std::vector<std::shared_ptr<Student>> & v)
{
m_students = v;
emit studentsChanged();
};



public:
 
[[nodiscard]] static Query* instance(){
static Query inst;
return &inst;
}


Query()= default;

public:
inline const QString & __typename() const final{
static const QString ret = "Query";
return ret;
};
};
class Student :  public qtgql::bases::ObjectTypeABC {
Q_OBJECT
public:
qtgql::bases::scalars::Id
 m_id = qtgql::bases::DEFAULTS::ID;
QString
 m_name = qtgql::bases::DEFAULTS::STRING;
qtgql::customscalars::DateTimeScalar
 m_birthDate = {};
std::vector<std::shared_ptr<Test>>
 m_test = {};

signals:
void idChanged();
void nameChanged();
void birthDateChanged();
void testChanged();


public:

[[nodiscard]] const qtgql::bases::scalars::Id &get_id()const{
return m_id;
}
void set_id(const qtgql::bases::scalars::Id & v)
{
m_id = v;
emit idChanged();
};

[[nodiscard]] const QString &get_name()const{
return m_name;
}
void set_name(const QString & v)
{
m_name = v;
emit nameChanged();
};

[[nodiscard]] const QString &get_birthDate(){
return m_birthDate.to_qt();
}
void set_birthDate(const qtgql::customscalars::DateTimeScalar & v)
{
m_birthDate = v;
emit birthDateChanged();
};

[[nodiscard]] const std::vector<std::shared_ptr<Test>> &get_test()const{
return m_test;
}
void set_test(const std::vector<std::shared_ptr<Test>> & v)
{
m_test = v;
emit testChanged();
};



public:

QTGQL_STATIC_MAKE_SHARED(Student)


Student()= default;

public:
inline const QString & __typename() const final{
static const QString ret = "Student";
return ret;
};
};
class Test :  public qtgql::bases::ObjectTypeABC {
Q_OBJECT
public:
QString
 m_subject = qtgql::bases::DEFAULTS::STRING;
int
 m_grade = qtgql::bases::DEFAULTS::INT;

signals:
void subjectChanged();
void gradeChanged();


public:

[[nodiscard]] const QString &get_subject()const{
return m_subject;
}
void set_subject(const QString & v)
{
m_subject = v;
emit subjectChanged();
};

[[nodiscard]] const int &get_grade()const{
return m_grade;
}
void set_grade(const int & v)
{
m_grade = v;
emit gradeChanged();
};



public:

QTGQL_STATIC_MAKE_SHARED(Test)


Test()= default;

public:
inline const QString & __typename() const final{
static const QString ret = "Test";
return ret;
};
};


}