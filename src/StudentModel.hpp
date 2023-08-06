//
// Created by almog on 8/6/23.
//

#ifndef MYQTPROJECT_STUDENTMODEL_HPP
#define MYQTPROJECT_STUDENTMODEL_HPP
#include <QArgument>
#include <QAbstractListModel>
#include "Student.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <vector>
inline const QByteArray HTTP_CONTENT_TYPE = "application/json";
inline const QByteArray HTTP_ACCEPT = "application/graphql-response+json";
class StudentModel: public QAbstractListModel {


    Q_OBJECT
    QML_ELEMENT
public:

    StudentModel(QObject *parent = nullptr): QAbstractListModel(parent)
            {
                m_className ="First Class";
                QNetworkAccessManager * manager= new QNetworkAccessManager(this);
                QNetworkRequest request;
                QJsonObject jsonObject
                {
                        {"query","query{\n  students{\n    id\n     name\n    test{\n      subject\n      grade\n    }\n  }\n}"}
                };
                QByteArray doc = QJsonDocument(jsonObject).toJson();
                request.setUrl(QUrl("http://127.0.0.1:8000/graphql/"));
                request.setRawHeader("Accept", HTTP_ACCEPT);
                request.setRawHeader("Content-Type", HTTP_CONTENT_TYPE);
                auto reply = manager->post(request, doc);


                QObject::connect(reply, &QNetworkReply::finished,
                this, [=]() {
                    qDebug() << "arrived";
                    if (reply->error()) {
                        qDebug() << reply->errorString();
                        return;
                    }

                    QByteArray answer = reply->readAll();
                    QJsonDocument qJsonDocument = QJsonDocument::fromJson(answer);
                    auto temp =qJsonDocument["data"]["students"];
                    qDebug() << temp.toArray();
                    if (qJsonDocument.isNull()) {
                        qDebug() << reply->errorString();
                        return;
                    }

                        //Convert Jsons to Students objects vector
                    for (const QJsonValue &jsonValue : temp.toArray()) {
                        if (jsonValue.isObject()) {
                            QJsonObject data = jsonValue.toObject();
                            m_students.push_back( std::move(std::make_unique<Student>(data)));
                        }
                    }

                    reply->deleteLater();

            }
            );

         }


    enum Roles
    {
        NAME = Qt::UserRole,
        TESTS,
        FIRST_GRADE,

    };

    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> names;
        names[NAME] = "name";
        names[TESTS] = "tests";
        return names;
    }

    //Return the first tests
    QVariant data(const QModelIndex &index, int role ) const override
    {
        if (!index.isValid())
            return QVariant();
        else if (role == Roles::NAME)
            return m_students.at(index.row())->name();
       else if (role == Roles::TESTS)
            return QVariant::fromValue(
                    qobject_cast<QObject*>(m_students.at(index.row())->tests())
        );

    }


    int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        qDebug() << m_students.size();
        return m_students.size();
    }




private:
    std::vector<std::unique_ptr<Student>> m_students;
    QString m_className;
};


#endif //MYQTPROJECT_STUDENTMODEL_HPP
