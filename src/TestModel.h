//
// Created by almog on 8/6/23.
//

#ifndef MYQTPROJECT_TESTMODEL_H
#define MYQTPROJECT_TESTMODEL_H


#include <QAbstractListModel>
#include <QtQmlIntegration>
#include <utility>
#include "Test.hpp"

class TestModel : public QAbstractListModel{
    Q_OBJECT
public:
    explicit TestModel(QObject *parent = nullptr): QAbstractListModel(parent){

    }
    enum Roles
    {
        SUBJECT = Qt::UserRole,
        GRADE,
    };

    void  push_back (const Test& test){
        m_tests.push_back(test);
    }
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> names;
        names[SUBJECT] = "subject";
        names[GRADE] = "grade";
        return names;
    }
    //Return the DATA
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
            return {};
        if (role == Roles::SUBJECT)
            return m_tests.at(index.row()).subject();
        if (role == Roles::GRADE)
            return m_tests.at(index.row()).grade();
    }
    [[nodiscard]] int rowCount(const QModelIndex & index) const override
    {
        return m_tests.size();
    }
private:
    QVector<Test> m_tests;
};


#endif //MYQTPROJECT_TESTMODEL_H
