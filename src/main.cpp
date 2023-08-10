#include <QGuiApplication>
#include <QUrl>

#include "graphql/__generated__/StudentsQuery.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include <qtgql/bases/bases.hpp>
#include <qtgql/gqloverhttp/gqloverhttp.hpp>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
  int ID, numOfGrade;
  string name;
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  auto env =
      std::shared_ptr<qtgql::bases::Environment>(new qtgql::bases::Environment(
          "Students", std::unique_ptr<qtgql::bases::NetworkLayerABC>(
                          new qtgql::gqloverhttp::GraphQLOverHttp(
                              {"http://127.0.0.1:8000/graphql/"}))));
  qtgql::bases::Environment::set_gql_env(env);
  auto cont_query = Students::studentsquery::StudentsQuery::shared();
  cont_query->fetch();
  engine.rootContext()->setContextProperty("query", cont_query.get());
  const QUrl url(
      QStringLiteral("/home/almog/CLionProjects/Students-UI/src/main.qml"));

  engine.load(url);

  return app.exec();
}
