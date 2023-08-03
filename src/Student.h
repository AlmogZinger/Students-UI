//
// Created by almog on 7/25/23.
//
#pragma once
#ifndef MYQTPROJECT_STUDENT_H
#define MYQTPROJECT_STUDENT_H
#include <string>
#include <list>
#include  <vector>
#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtGui>
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>

inline const QByteArray HTTP_CONTENT_TYPE = "application/json";
inline const QByteArray HTTP_ACCEPT = "application/graphql-response+json";

class Student : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    std::vector<Student> studentsGlobal;

public:
    Student(int id, QString name) {
        m_id = id;
        m_name = name;
    }

    Student(const QJsonObject & data){
        m_name= data["name"].toString();
        m_id = data["id"].toInt();
    };
    Student(QObject *parent = nullptr): QAbstractListModel(parent)
    {

        QNetworkAccessManager * manager;
        QNetworkRequest request;
        manager = new QNetworkAccessManager();
        QObject::connect(manager, &QNetworkAccessManager::finished,
                         this, [=](QNetworkReply *reply) {
                    if (reply->error()) {
                        qDebug() << reply->errorString();
                        return;
                    }

                    QByteArray answer = reply->readAll();
                    QJsonDocument qJsonDocument = QJsonDocument::fromJson(answer);
                    if (qJsonDocument.isNull()) {
                        qDebug() << reply->errorString();
                        return;
                    }
                    if (qJsonDocument.isArray()) {
                        std::vector <Student*> students;

                        for (const QJsonValue &jsonValue: qJsonDocument.array()) {
                            if (jsonValue.isObject()) {
                                QJsonObject data = jsonValue.toObject();
                                students.push_back(Student(data));
                            }
                        }

                    }
                }
        );
        QJsonObject jsonObject
                {
                        {"query", "query{\n  students{\n   id\n   name\n   }\n}"}
                };
        auto doc = QJsonDocument(jsonObject).toJson();
        request.setUrl(QUrl("http://127.0.0.1:8000/graphql/"));
        request.setRawHeader("Accept", HTTP_ACCEPT);
        request.setRawHeader("Content-Type", HTTP_CONTENT_TYPE);
        manager->post(request, doc);

    }




    void setName(const QString &na){
        if( na != m_name) {
            m_name =na;
            emit nameChanged();
        }
    }
    QString name() const {
        return m_name;
    }
    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> names;
        names[Grade] = "grade";
        return names;
    }
    enum Roles
    {
        Grade = Qt::UserRole,
    };

    QVariant data(const QModelIndex &index, int role =0 ) const override
    {
        if (!index.isValid())
            return QVariant();
        return m_grades.at(index.row());
    }
    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        const int newGrade = value.toInt();
        m_grades[index.row()] = newGrade;
        emit dataChanged(index, index);
        return true;
    }
    Q_INVOKABLE int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        return m_grades.size();
    }
    Q_INVOKABLE void append(char* g) {
        m_grades.append(atoi(g));
    }

    Q_INVOKABLE void removeLast() {
        m_grades.removeLast();
    }

    Q_INVOKABLE void clear() {
        m_grades.clear();
    }


signals:
    void nameChanged();
    //void gradesChanged();
private:
    int m_id;
    QString m_name;
    QVector<int> m_grades;
    //static void append_grades(QQmlListProperty<int> *list, int grade);
   // QQmlListProperty<int> m_grades;

};


#endif //MYQTPROJECT_STUDENT_H
