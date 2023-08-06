//
// Created by almog on 7/25/23.
//
#pragma once
#ifndef MYQTPROJECT_STUDENT_HPP
#define MYQTPROJECT_STUDENT_HPP
#include <string>
#include <list>
#include <utility>
#include  <vector>
#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtGui>
#include <iostream>
#include "Test.hpp"
#include "TestModel.h"

struct Student
{

public:


    //Json constructor
    explicit Student(const QJsonObject & data){
        m_name= data["name"].toString();
        m_id = data["id"].toInt();
        m_test = std::make_unique<TestModel>();
        for (const auto &jsonValue : data["test"].toArray()){
            QJsonObject temp = jsonValue.toObject();
            m_test->push_back(Test(temp));
        }
    }


    [[nodiscard]] QString name() const {
        return m_name;
    }


    [[nodiscard]] TestModel* tests() const {
        return   m_test.get() ;
    }
    [[nodiscard]] int id() const {
        return m_id;
    }



//---------------------------------


private:
    int m_id{};
    QString m_name;
    std::unique_ptr<TestModel> m_test;


};


#endif //MYQTPROJECT_STUDENT_HPP
