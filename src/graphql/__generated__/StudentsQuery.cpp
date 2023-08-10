#include "./StudentsQuery.hpp"

namespace Students::studentsquery {

// Interfaces

// Constructor
Test__studentstest::Test__studentstest(StudentsQuery *operation,
                                       const std::shared_ptr<Test> &inst)
    : m_inst{inst}, ObjectTypeABC ::ObjectTypeABC(operation) {
  m_operation = operation;

  _qtgql_connect_signals();
}

void Test__studentstest::_qtgql_connect_signals() {

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
deserializers::des_Test__studentstest(const QJsonObject &data,
                                      const StudentsQuery *operation) {
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
void updaters::update_Test__studentstest(const std::shared_ptr<Test> &inst,
                                         const QJsonObject &data,
                                         const StudentsQuery *operation) {
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

// Test__studentstest Getters
[[nodiscard]] const QString Test__studentstest::get_subject() const {

  return m_inst->get_subject();
};
[[nodiscard]] const int Test__studentstest::get_grade() const {

  return m_inst->get_grade();
};

void Test__studentstest::qtgql_replace_concrete(
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
Student__students::Student__students(StudentsQuery *operation,
                                     const std::shared_ptr<Student> &inst)
    : m_inst{inst}, ObjectTypeABC ::ObjectTypeABC(operation) {
  m_operation = operation;

  auto init_vec_test = std::vector<Test__studentstest *>();
  for (const auto &node : m_inst->get_test()) {
    init_vec_test.push_back(new Test__studentstest(operation, node));
  }
  m_test = new qtgql::bases::ListModelABC<Test__studentstest *>(
      this, std::move(init_vec_test));

  _qtgql_connect_signals();
}

void Student__students::_qtgql_connect_signals() {

  auto m_inst_ptr = m_inst.get();
  Q_ASSERT_X(m_inst_ptr, __FILE__,
             "Tried to instantiate a proxy object with an empty pointer!");
  connect(m_inst_ptr, &Students::Student::nameChanged, this, [&]() {
    auto operation = m_operation;
    emit nameChanged();
  });
  connect(m_inst_ptr, &Students::Student::testChanged, this, [&]() {
    auto operation = m_operation;
    auto new_data = m_inst->get_test();
    auto new_len = new_data.size();
    auto prev_len = m_test->rowCount();
    if (new_len < prev_len) {
      m_test->removeRows(prev_len - 1, prev_len - new_len);
    }
    for (int i = 0; i < new_len; i++) {
      const auto &concrete = new_data.at(i);
      if (i >= prev_len) {
        m_test->append(new Test__studentstest(operation, concrete));
      } else {
        auto proxy_to_update = m_test->get(i);
        if (proxy_to_update) {
          proxy_to_update->qtgql_replace_concrete(concrete);
        } else {
          m_test->replace(i, new Test__studentstest(operation, concrete));
        }
      }
    }
  });
};

// Deserialzier

std::shared_ptr<Student>
deserializers::des_Student__students(const QJsonObject &data,
                                     const StudentsQuery *operation) {
  if (data.isEmpty()) {
    return {};
  }
  auto inst = Student::shared();

  if (!data.value("name").isNull()) {
    inst->set_name(data.value("name").toString());
  };

  if (!data.value("test").isNull()) {

    std::vector<std::shared_ptr<Test>> test_init_vec;
    for (const auto &node : data.value("test").toArray()) {

      test_init_vec.push_back(
          deserializers::des_Test__studentstest(node.toObject(), operation));
    };
    inst->set_test(test_init_vec);
  };

  return inst;
};

// Updater
void updaters::update_Student__students(const std::shared_ptr<Student> &inst,
                                        const QJsonObject &data,
                                        const StudentsQuery *operation) {
  if (!data.value("name").isNull()) {
    auto new_name = data.value("name").toString();
    if (inst->m_name != new_name) {
      inst->set_name(new_name);
    }
  }

  if (!data.value("test").isNull()) {

    if (!data.value("test").isNull()) {

      std::vector<std::shared_ptr<Test>> test_init_vec;
      for (const auto &node : data.value("test").toArray()) {

        test_init_vec.push_back(
            deserializers::des_Test__studentstest(node.toObject(), operation));
      };
      inst->set_test(test_init_vec);
    };
  }
};

// Student__students Getters
[[nodiscard]] const QString Student__students::get_name() const {

  return m_inst->get_name();
};
[[nodiscard]] const qtgql::bases::ListModelABC<Test__studentstest *> *
Student__students::get_test() const {

  return m_test;
};

void Student__students::qtgql_replace_concrete(
    const std::shared_ptr<Student> &new_inst) {
  if (new_inst == m_inst) {
    return;
  }
  m_inst->disconnect(this);
  if (m_inst->m_name != new_inst->m_name) {
    auto operation = m_operation;
    emit nameChanged();
  };
  if (m_inst->m_test != new_inst->m_test) {
    auto operation = m_operation;
    auto new_data = m_inst->get_test();
    auto new_len = new_data.size();
    auto prev_len = m_test->rowCount();
    if (new_len < prev_len) {
      m_test->removeRows(prev_len - 1, prev_len - new_len);
    }
    for (int i = 0; i < new_len; i++) {
      const auto &concrete = new_data.at(i);
      if (i >= prev_len) {
        m_test->append(new Test__studentstest(operation, concrete));
      } else {
        auto proxy_to_update = m_test->get(i);
        if (proxy_to_update) {
          proxy_to_update->qtgql_replace_concrete(concrete);
        } else {
          m_test->replace(i, new Test__studentstest(operation, concrete));
        }
      }
    }
  };
  m_inst = new_inst;
  _qtgql_connect_signals();
};
// Constructor
Query__::Query__(StudentsQuery *operation)
    : ObjectTypeABC ::ObjectTypeABC(operation) {
  m_inst = Query::instance();
  auto m_inst_ptr = m_inst;
  m_operation = operation;

  auto init_vec_students = std::vector<Student__students *>();
  for (const auto &node : m_inst->get_students()) {
    init_vec_students.push_back(new Student__students(operation, node));
  }
  m_students = new qtgql::bases::ListModelABC<Student__students *>(
      this, std::move(init_vec_students));

  _qtgql_connect_signals();
}

void Query__::_qtgql_connect_signals() {
  auto m_inst_ptr = m_inst;
  Q_ASSERT_X(m_inst_ptr, __FILE__,
             "Tried to instantiate a proxy object with an empty pointer!");
  connect(m_inst_ptr, &Students::Query::studentsChanged, this, [&]() {
    auto operation = m_operation;
    auto new_data = m_inst->get_students();
    auto new_len = new_data.size();
    auto prev_len = m_students->rowCount();
    if (new_len < prev_len) {
      m_students->removeRows(prev_len - 1, prev_len - new_len);
    }
    for (int i = 0; i < new_len; i++) {
      const auto &concrete = new_data.at(i);
      if (i >= prev_len) {
        m_students->append(new Student__students(operation, concrete));
      } else {
        auto proxy_to_update = m_students->get(i);
        if (proxy_to_update) {
          proxy_to_update->qtgql_replace_concrete(concrete);
        } else {
          m_students->replace(i, new Student__students(operation, concrete));
        }
      }
    }
  });
};

// Deserialzier

// Updater
void updaters::update_Query__(Query *inst, const QJsonObject &data,
                              const StudentsQuery *operation) {
  if (!data.value("students").isNull()) {

    if (!data.value("students").isNull()) {

      std::vector<std::shared_ptr<Student>> students_init_vec;
      for (const auto &node : data.value("students").toArray()) {

        students_init_vec.push_back(
            deserializers::des_Student__students(node.toObject(), operation));
      };
      inst->set_students(students_init_vec);
    };
  }
};

// Query__ Getters
[[nodiscard]] const qtgql::bases::ListModelABC<Student__students *> *
Query__::get_students() const {

  return m_students;
};

} // namespace Students::studentsquery
