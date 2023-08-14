#include "./AddStudentMutation.hpp"

namespace Students::addstudentmutation {

// Interfaces

// Constructor
Test__addStudenttests::Test__addStudenttests(AddStudentMutation *operation,
                                             const std::shared_ptr<Test> &inst)
    : m_inst{inst}, ObjectTypeABC ::ObjectTypeABC(operation) {
  m_operation = operation;

  _qtgql_connect_signals();
}

void Test__addStudenttests::_qtgql_connect_signals() {

  auto m_inst_ptr = m_inst.get();
  Q_ASSERT_X(m_inst_ptr, __FILE__,
             "Tried to instantiate a proxy object with an empty pointer!");
  connect(m_inst_ptr, &Students::Test::subjectChanged, this, [&]() {
    auto operation = m_operation;
    emit subjectChanged();
  });
  connect(m_inst_ptr, &Students::Test::gradeChanged, this, [&]() {
    auto operation = m_operation;
    emit gradeChanged();
  });
};

// Deserialzier

std::shared_ptr<Test>
deserializers::des_Test__addStudenttests(const QJsonObject &data,
                                         const AddStudentMutation *operation) {
  if (data.isEmpty()) {
    return {};
  }
  auto inst = Test::shared();

  if (!data.value("subject").isNull()) {
    inst->set_subject(data.value("subject").toString());
  };

  if (!data.value("grade").isNull()) {
    inst->set_grade(data.value("grade").toInt());
  };

  return inst;
};

// Updater
void updaters::update_Test__addStudenttests(
    const std::shared_ptr<Test> &inst, const QJsonObject &data,
    const AddStudentMutation *operation) {
  if (!data.value("subject").isNull()) {
    auto new_subject = data.value("subject").toString();
    if (inst->m_subject != new_subject) {
      inst->set_subject(new_subject);
    }
  }

  if (!data.value("grade").isNull()) {
    auto new_grade = data.value("grade").toInt();
    if (inst->m_grade != new_grade) {
      inst->set_grade(new_grade);
    }
  }
};

// Test__addStudenttests Getters
[[nodiscard]] const QString Test__addStudenttests::get_subject() const {

  return m_inst->get_subject();
};
[[nodiscard]] const int Test__addStudenttests::get_grade() const {

  return m_inst->get_grade();
};

void Test__addStudenttests::qtgql_replace_concrete(
    const std::shared_ptr<Test> &new_inst) {
  if (new_inst == m_inst) {
    return;
  }
  m_inst->disconnect(this);
  if (m_inst->m_subject != new_inst->m_subject) {
    auto operation = m_operation;
    emit subjectChanged();
  };
  if (m_inst->m_grade != new_inst->m_grade) {
    auto operation = m_operation;
    emit gradeChanged();
  };
  m_inst = new_inst;
  _qtgql_connect_signals();
};
// Constructor
Student__addStudent::Student__addStudent(AddStudentMutation *operation,
                                         const std::shared_ptr<Student> &inst)
    : m_inst{inst}, ObjectTypeABC ::ObjectTypeABC(operation) {
  m_operation = operation;

  auto init_vec_tests = std::vector<Test__addStudenttests *>();
  for (const auto &node : m_inst->get_tests()) {
    init_vec_tests.push_back(new Test__addStudenttests(operation, node));
  }
  m_tests = new qtgql::bases::ListModelABC<Test__addStudenttests *>(
      this, std::move(init_vec_tests));

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
  connect(m_inst_ptr, &Students::Student::testsChanged, this, [&]() {
    auto operation = m_operation;
    auto new_data = m_inst->get_tests();
    auto new_len = new_data.size();
    auto prev_len = m_tests->rowCount();
    if (new_len < prev_len) {
      m_tests->removeRows(prev_len - 1, prev_len - new_len);
    }
    for (int i = 0; i < new_len; i++) {
      const auto &concrete = new_data.at(i);
      if (i >= prev_len) {
        m_tests->append(new Test__addStudenttests(operation, concrete));
      } else {
        auto proxy_to_update = m_tests->get(i);
        if (proxy_to_update) {
          proxy_to_update->qtgql_replace_concrete(concrete);
        } else {
          m_tests->replace(i, new Test__addStudenttests(operation, concrete));
        }
      }
    }
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

  if (!data.value("tests").isNull()) {

    std::vector<std::shared_ptr<Test>> tests_init_vec;
    for (const auto &node : data.value("tests").toArray()) {

      tests_init_vec.push_back(
          deserializers::des_Test__addStudenttests(node.toObject(), operation));
    };
    inst->set_tests(tests_init_vec);
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

  if (!data.value("tests").isNull()) {

    if (!data.value("tests").isNull()) {

      std::vector<std::shared_ptr<Test>> tests_init_vec;
      for (const auto &node : data.value("tests").toArray()) {

        tests_init_vec.push_back(deserializers::des_Test__addStudenttests(
            node.toObject(), operation));
      };
      inst->set_tests(tests_init_vec);
    };
  }
};

// Student__addStudent Getters
[[nodiscard]] const QString Student__addStudent::get_name() const {

  return m_inst->get_name();
};
[[nodiscard]] const qtgql::bases::ListModelABC<Test__addStudenttests *> *
Student__addStudent::get_tests() const {

  return m_tests;
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
  if (m_inst->m_tests != new_inst->m_tests) {
    auto operation = m_operation;
    auto new_data = m_inst->get_tests();
    auto new_len = new_data.size();
    auto prev_len = m_tests->rowCount();
    if (new_len < prev_len) {
      m_tests->removeRows(prev_len - 1, prev_len - new_len);
    }
    for (int i = 0; i < new_len; i++) {
      const auto &concrete = new_data.at(i);
      if (i >= prev_len) {
        m_tests->append(new Test__addStudenttests(operation, concrete));
      } else {
        auto proxy_to_update = m_tests->get(i);
        if (proxy_to_update) {
          proxy_to_update->qtgql_replace_concrete(concrete);
        } else {
          m_tests->replace(i, new Test__addStudenttests(operation, concrete));
        }
      }
    }
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
