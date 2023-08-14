#pragma once
#include "./schema.hpp"
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <qtgql/bases/bases.hpp>

namespace Students::studentsquery {
class StudentsQuery;

namespace deserializers {
std::shared_ptr<Test> des_Test__studentstests(const QJsonObject &data,
                                              const StudentsQuery *operation);
std::shared_ptr<Student> des_Student__students(const QJsonObject &data,
                                               const StudentsQuery *operation);
}; // namespace deserializers

namespace updaters {
void update_Test__studentstests(const std::shared_ptr<Test> &inst,
                                const QJsonObject &data,
                                const StudentsQuery *operation);
void update_Student__students(const std::shared_ptr<Student> &inst,
                              const QJsonObject &data,
                              const StudentsQuery *operation);
void update_Query__(Query *inst, const QJsonObject &data,
                    const StudentsQuery *operation);
}; // namespace updaters

// ------------ Narrowed Interfaces ------------

// ------------ Narrowed Object types ------------

class Test__studentstests : public qtgql::bases::ObjectTypeABC {

  StudentsQuery *m_operation;

  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("QtGql does not supports instantiation via qml")
  Q_PROPERTY(QString __typeName READ __typename CONSTANT)

  Q_PROPERTY(const QString subject READ get_subject NOTIFY subjectChanged);
  Q_PROPERTY(const int grade READ get_grade NOTIFY gradeChanged);

signals:
  void subjectChanged();
  void gradeChanged();

protected:
  std::shared_ptr<Students::Test> m_inst;

public:
  Test__studentstests(StudentsQuery *operation,
                      const std::shared_ptr<Test> &inst);

  void qtgql_replace_concrete(const std::shared_ptr<Test> &new_inst);

protected:
  void _qtgql_connect_signals();

public:
  [[nodiscard]] const QString get_subject() const;
  [[nodiscard]] const int get_grade() const;

public:
  [[nodiscard]] const QString &__typename() const final {
    return m_inst->__typename();
  }
};

class Student__students : public qtgql::bases::ObjectTypeABC {

  StudentsQuery *m_operation;

  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("QtGql does not supports instantiation via qml")
  Q_PROPERTY(QString __typeName READ __typename CONSTANT)

  Q_PROPERTY(const QString name READ get_name NOTIFY nameChanged);
  Q_PROPERTY(const qtgql::bases::ListModelABC<Test__studentstests *> *tests READ
                 get_tests NOTIFY testsChanged);

signals:
  void nameChanged();
  void testsChanged();

protected:
  std::shared_ptr<Students::Student> m_inst;
  qtgql::bases::ListModelABC<Test__studentstests *> *m_tests;

public:
  Student__students(StudentsQuery *operation,
                    const std::shared_ptr<Student> &inst);

  void qtgql_replace_concrete(const std::shared_ptr<Student> &new_inst);

protected:
  void _qtgql_connect_signals();

public:
  [[nodiscard]] const QString get_name() const;
  [[nodiscard]] const qtgql::bases::ListModelABC<Test__studentstests *> *
  get_tests() const;

public:
  [[nodiscard]] const QString &__typename() const final {
    return m_inst->__typename();
  }
};

class Query__ : public qtgql::bases::ObjectTypeABC {

  StudentsQuery *m_operation;

  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("QtGql does not supports instantiation via qml")
  Q_PROPERTY(QString __typeName READ __typename CONSTANT)

  Q_PROPERTY(const qtgql::bases::ListModelABC<Student__students *> *students
                 READ get_students NOTIFY studentsChanged);

signals:
  void studentsChanged();

protected:
  Students::Query *m_inst;
  qtgql::bases::ListModelABC<Student__students *> *m_students;

public:
  Query__(StudentsQuery *operation);

protected:
  void _qtgql_connect_signals();

public:
  [[nodiscard]] const qtgql::bases::ListModelABC<Student__students *> *
  get_students() const;

public:
  [[nodiscard]] const QString &__typename() const final {
    return m_inst->__typename();
  }
};

struct StudentsQueryVariables {
  QJsonObject to_json() const {
    QJsonObject __ret;
    return __ret;
  }
};

class StudentsQuery : public qtgql::bases::OperationHandlerABC {
  Q_OBJECT
  Q_PROPERTY(const Query__ *data READ data NOTIFY dataChanged);
  QML_ELEMENT
  QML_UNCREATABLE("Must be instantiated as shared pointer.")

  std::optional<Query__ *> m_data = {};

  inline const QString &ENV_NAME() final {
    static const auto ret = QString("Students");
    return ret;
  }
signals:
  void dataChanged();

public:
  StudentsQueryVariables vars_inst;

  StudentsQuery()
      : qtgql::bases::OperationHandlerABC(qtgql::bases::GraphQLMessage(
            "query StudentsQuery {"
            "  students {"
            "    ...StudentsFragment"
            "  }"
            "}"
            "fragment StudentsFragment on Student {"
            "  name"
            "  tests {"
            "    subject"
            "    grade"
            "  }"
            "}")){};

  QTGQL_STATIC_MAKE_SHARED(StudentsQuery)

  void on_next(const QJsonObject &data_) override {
    if (!m_data) {
      updaters::update_Query__(Query::instance(), data_, this);
      m_data = new Query__(this);
      emit dataChanged();
    } else {
      updaters::update_Query__(Query::instance(), data_, this);
    }
  }

  inline const Query__ *data() const {
    if (m_data) {
      return m_data.value();
    }
    return nullptr;
  }
};

class UseStudentsQuery : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(const Query__ *data READ data NOTIFY dataChanged);
  Q_PROPERTY(bool completed READ completed NOTIFY completedChanged)
  Q_PROPERTY(bool operationOnFlight READ operation_on_flight NOTIFY
                 operationOnFlightChanged)

public:
  std::shared_ptr<StudentsQuery> m_operation;

  UseStudentsQuery(QObject *parent = nullptr) : QObject(parent) {
    m_operation = StudentsQuery::shared();
    auto op_ptr = m_operation.get();
    connect(op_ptr, &StudentsQuery::dataChanged, this,
            [&] { emit dataChanged(); });
    connect(op_ptr, &StudentsQuery::completedChanged, this,
            [&] { emit completedChanged(); });
    connect(op_ptr, &StudentsQuery::operationOnFlightChanged, this,
            [&] { emit operationOnFlightChanged(); });
  };

  inline const Query__ *data() const { return m_operation->data(); }
  inline bool completed() const { return m_operation->completed(); }
  inline bool operation_on_flight() const {
    return m_operation->operation_on_flight();
  }

public slots:
  void fetch() { m_operation->fetch(); };
  void refetch() { m_operation->refetch(); };

signals:
  void dataChanged();
  void completedChanged();
  void operationOnFlightChanged();
};
}; // namespace Students::studentsquery
