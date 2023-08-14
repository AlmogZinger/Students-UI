#pragma once
#include "./schema.hpp"
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <qtgql/bases/bases.hpp>

namespace Students::addstudentmutation {
class AddStudentMutation;

namespace deserializers {
std::shared_ptr<Test>
des_Test__addStudenttests(const QJsonObject &data,
                          const AddStudentMutation *operation);
std::shared_ptr<Student>
des_Student__addStudent(const QJsonObject &data,
                        const AddStudentMutation *operation);
}; // namespace deserializers

namespace updaters {
void update_Test__addStudenttests(const std::shared_ptr<Test> &inst,
                                  const QJsonObject &data,
                                  const AddStudentMutation *operation);
void update_Student__addStudent(const std::shared_ptr<Student> &inst,
                                const QJsonObject &data,
                                const AddStudentMutation *operation);
void update_Mutation__(Mutation *inst, const QJsonObject &data,
                       const AddStudentMutation *operation);
}; // namespace updaters

// ------------ Narrowed Interfaces ------------

// ------------ Narrowed Object types ------------

class Test__addStudenttests : public qtgql::bases::ObjectTypeABC {

  AddStudentMutation *m_operation;

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
  Test__addStudenttests(AddStudentMutation *operation,
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

class Student__addStudent : public qtgql::bases::ObjectTypeABC {

  AddStudentMutation *m_operation;

  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("QtGql does not supports instantiation via qml")
  Q_PROPERTY(QString __typeName READ __typename CONSTANT)

  Q_PROPERTY(const QString name READ get_name NOTIFY nameChanged);
  Q_PROPERTY(const qtgql::bases::ListModelABC<Test__addStudenttests *> *tests
                 READ get_tests NOTIFY testsChanged);

signals:
  void nameChanged();
  void testsChanged();

protected:
  std::shared_ptr<Students::Student> m_inst;
  qtgql::bases::ListModelABC<Test__addStudenttests *> *m_tests;

public:
  Student__addStudent(AddStudentMutation *operation,
                      const std::shared_ptr<Student> &inst);

  void qtgql_replace_concrete(const std::shared_ptr<Student> &new_inst);

protected:
  void _qtgql_connect_signals();

public:
  [[nodiscard]] const QString get_name() const;
  [[nodiscard]] const qtgql::bases::ListModelABC<Test__addStudenttests *> *
  get_tests() const;

public:
  [[nodiscard]] const QString &__typename() const final {
    return m_inst->__typename();
  }
};

class Mutation__ : public qtgql::bases::ObjectTypeABC {

  AddStudentMutation *m_operation;

  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("QtGql does not supports instantiation via qml")
  Q_PROPERTY(QString __typeName READ __typename CONSTANT)

  Q_PROPERTY(const Student__addStudent *addStudent READ get_addStudent NOTIFY
                 addStudentChanged);

signals:
  void addStudentChanged();

protected:
  Students::Mutation *m_inst;
  Student__addStudent *m_addStudent = {};

public:
  Mutation__(AddStudentMutation *operation);

protected:
  void _qtgql_connect_signals();

public:
  [[nodiscard]] const Student__addStudent *get_addStudent() const;

public:
  [[nodiscard]] const QString &__typename() const final {
    return m_inst->__typename();
  }
};

struct AddStudentMutationVariables {
  std::optional<QString> g_name = {};
  std::optional<qtgql::customscalars::DateScalar> g_birthDate = {};
  QJsonObject to_json() const {
    QJsonObject __ret;
    if (g_name.has_value()) {
      __ret.insert("g_name", g_name.value());
    }

    if (g_birthDate.has_value()) {
      __ret.insert("g_birthDate", g_birthDate.value().serialize());
    }

    return __ret;
  }
};

class AddStudentMutation : public qtgql::bases::OperationHandlerABC {
  Q_OBJECT
  Q_PROPERTY(const Mutation__ *data READ data NOTIFY dataChanged);
  QML_ELEMENT
  QML_UNCREATABLE("Must be instantiated as shared pointer.")

  std::optional<Mutation__ *> m_data = {};

  inline const QString &ENV_NAME() final {
    static const auto ret = QString("Students");
    return ret;
  }
signals:
  void dataChanged();

public:
  AddStudentMutationVariables vars_inst;

  AddStudentMutation()
      : qtgql::bases::OperationHandlerABC(qtgql::bases::GraphQLMessage(
            "mutation AddStudentMutation($g_name: String!, $g_birthDate: "
            "Date!) {"
            "  addStudent(name: $g_name, birth: $g_birthDate) {"
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

  QTGQL_STATIC_MAKE_SHARED(AddStudentMutation)

  void on_next(const QJsonObject &data_) override {
    if (!m_data) {
      updaters::update_Mutation__(Mutation::instance(), data_, this);
      m_data = new Mutation__(this);
      emit dataChanged();
    } else {
      updaters::update_Mutation__(Mutation::instance(), data_, this);
    }
  }

  inline const Mutation__ *data() const {
    if (m_data) {
      return m_data.value();
    }
    return nullptr;
  }

  void set_variables(const AddStudentMutationVariables &vars) {
    vars_inst = vars;
    qtgql::bases::OperationHandlerABC::set_vars(vars_inst.to_json());
  }
};

class UseAddStudentMutation : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(const Mutation__ *data READ data NOTIFY dataChanged);
  Q_PROPERTY(bool completed READ completed NOTIFY completedChanged)
  Q_PROPERTY(bool operationOnFlight READ operation_on_flight NOTIFY
                 operationOnFlightChanged)

public:
  std::shared_ptr<AddStudentMutation> m_operation;

  UseAddStudentMutation(QObject *parent = nullptr) : QObject(parent) {
    m_operation = AddStudentMutation::shared();
    auto op_ptr = m_operation.get();
    connect(op_ptr, &AddStudentMutation::dataChanged, this,
            [&] { emit dataChanged(); });
    connect(op_ptr, &AddStudentMutation::completedChanged, this,
            [&] { emit completedChanged(); });
    connect(op_ptr, &AddStudentMutation::operationOnFlightChanged, this,
            [&] { emit operationOnFlightChanged(); });
  };

  inline const Mutation__ *data() const { return m_operation->data(); }
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
}; // namespace Students::addstudentmutation
