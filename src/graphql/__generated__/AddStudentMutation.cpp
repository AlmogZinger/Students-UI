#include "./AddStudentMutation.hpp"

namespace Students::addstudentmutation {

// Interfaces

// Constructor
Student__addStudent::Student__addStudent(AddStudentMutation *operation,
                                         const std::shared_ptr<Student> &inst)
    : m_inst{inst}, ObjectTypeABC ::ObjectTypeABC(operation) {
  m_operation = operation;

  _qtgql_connect_signals();
}

void Student__addStudent::_qtgql_connect_signals() {

  auto m_inst_ptr = m_inst.get();
  Q_ASSERT_X(m_inst_ptr, __FILE__,
             "Tried to instantiate a proxy object with an empty pointer!");
  connect(m_inst_ptr, &Students::Student::nameChanged, this, [&]() {
    auto operation = m_operation;
    emit nameChanged();
  });
  connect(m_inst_ptr, &Students::Student::birthDateChanged, this, [&]() {
    auto operation = m_operation;
    emit birthDateChanged();
  });
};

// Deserialzier

std::shared_ptr<Student>
deserializers::des_Student__addStudent(const QJsonObject &data,
                                       const AddStudentMutation *operation) {
  if (data.isEmpty()) {
    return {};
  }
  auto inst = Student::shared();

  if (!data.value("name").isNull()) {
    inst->set_name(data.value("name").toString());
  };

  if (!data.value("birthDate").isNull()) {
    auto new_birthDate = qtgql::customscalars::DateTimeScalar();
    new_birthDate.deserialize(data.value("birthDate"));
    inst->set_birthDate(new_birthDate);
  };

  return inst;
};

// Updater
void updaters::update_Student__addStudent(const std::shared_ptr<Student> &inst,
                                          const QJsonObject &data,
                                          const AddStudentMutation *operation) {
  if (!data.value("name").isNull()) {
    auto new_name = data.value("name").toString();
    if (inst->m_name != new_name) {
      inst->set_name(new_name);
    }
  }

  if (!data.value("birthDate").isNull()) {

    auto new_birthDate = qtgql::customscalars::DateTimeScalar();
    new_birthDate.deserialize(data.value("birthDate"));
    if (inst->m_birthDate != new_birthDate) {
      inst->set_birthDate(new_birthDate);
    }
  }
};

// Student__addStudent Getters
[[nodiscard]] const QString Student__addStudent::get_name() const {

  return m_inst->get_name();
};
[[nodiscard]] const QString Student__addStudent::get_birthDate() const {

  return m_inst->get_birthDate();
};

void Student__addStudent::qtgql_replace_concrete(
    const std::shared_ptr<Student> &new_inst) {
  if (new_inst == m_inst) {
    return;
  }
  m_inst->disconnect(this);
  if (m_inst->m_name != new_inst->m_name) {
    auto operation = m_operation;
    emit nameChanged();
  };
  if (m_inst->m_birthDate != new_inst->m_birthDate) {
    auto operation = m_operation;
    emit birthDateChanged();
  };
  m_inst = new_inst;
  _qtgql_connect_signals();
};
// Constructor
Mutation__::Mutation__(AddStudentMutation *operation)
    : ObjectTypeABC ::ObjectTypeABC(operation) {
  m_inst = Mutation::instance();
  auto m_inst_ptr = m_inst;
  m_operation = operation;
  m_addStudent = new Student__addStudent(
      operation,
      m_inst->get_addStudent({operation->vars_inst.g_name.value(),
                              operation->vars_inst.g_birthDate.value()}));

  _qtgql_connect_signals();
}

void Mutation__::_qtgql_connect_signals() {
  auto m_inst_ptr = m_inst;
  Q_ASSERT_X(m_inst_ptr, __FILE__,
             "Tried to instantiate a proxy object with an empty pointer!");
  connect(m_inst_ptr, &Students::Mutation::addStudentChanged, this, [&]() {
    auto operation = m_operation;
    auto concrete =
        m_inst->get_addStudent({operation->vars_inst.g_name.value(),
                                operation->vars_inst.g_birthDate.value()});
    if (m_addStudent) {
      m_addStudent->qtgql_replace_concrete(concrete);
    } else {
      m_addStudent = new Student__addStudent(operation, concrete);
      emit addStudentChanged();
    }
  });
};

// Deserialzier

// Updater
void updaters::update_Mutation__(Mutation *inst, const QJsonObject &data,
                                 const AddStudentMutation *operation) {
  std::tuple<QString, qtgql::customscalars::DateScalar> m_addStudent_args = {
      operation->vars_inst.g_name.value(),
      operation->vars_inst.g_birthDate.value()};
  if (!inst->m_addStudent.contains(m_addStudent_args))

  {
    if (!data.value("addStudent").isNull()) {
      inst->set_addStudent(deserializers::des_Student__addStudent(
                               data.value("addStudent").toObject(), operation),
                           {operation->vars_inst.g_name.value(),
                            operation->vars_inst.g_birthDate.value()});
    };
  } else if (!data.value("addStudent").isNull()) {

    auto addStudent_data = data.value("addStudent").toObject();

    updaters::update_Student__addStudent(
        inst->m_addStudent.at(m_addStudent_args), addStudent_data, operation);
  }
};

// Mutation__ Getters
[[nodiscard]] const Student__addStudent *Mutation__::get_addStudent() const {

  return m_addStudent;
};

} // namespace Students::addstudentmutation
