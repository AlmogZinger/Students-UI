#include <QGuiApplication>
#include <QUrl>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Student.hpp"
#include "StudentModel.hpp"
#include <iostream>
#include <string>
using namespace  std;
int main(int argc, char *argv[])
{
    int ID,numOfGrade;
    string name;
    QGuiApplication app(argc, argv);
    qmlRegisterType<StudentModel>("App", 1, 0, "StudentModel");
    qmlRegisterType<Student>("App", 1, 0, "Student");
    qmlRegisterType<Test>("App", 1, 0, "Test");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("/home/almog/CLionProjects/Students-UI/src/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    /*
    Student student ;
    engine.rootContext()->setContextProperty("student", &student);

    qmlRegisterType<Student>("App", 1, 0, "");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);





*/

    return app.exec();
}
/*cout <<"Please enter ID, name, and the amount of tests-  /n";
cin >> ID,name,numOfGrade;Student(ID,name,numOfGrade);*/
/*//Query the database
string msg ="";
for (const auto &item: stu.GetGrade()) {
   msg+="/n "+item;
}*/