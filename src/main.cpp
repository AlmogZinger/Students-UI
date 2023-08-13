#include <QGuiApplication>
#include <QUrl>

#include "aplicationsingleton.hpp"
#include "graphql/__generated__/AddStudentMutation.hpp"
#include "graphql/__generated__/StudentsQuery.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include <qtgql/bases/bases.hpp>
#include <qtgql/gqloverhttp/gqloverhttp.hpp>
#include <string>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  auto env =
      std::shared_ptr<qtgql::bases::Environment>(new qtgql::bases::Environment(
          "Students", std::unique_ptr<qtgql::bases::NetworkLayerABC>(
                          new qtgql::gqloverhttp::GraphQLOverHttp(
                              {"http://127.0.0.1:8000/graphql/"}))));
  qtgql::bases::Environment::set_gql_env(env);

  ApplicationSingleton pSingleton = ApplicationSingleton();
  engine.rootContext()->setContextProperty("ApplicationSingleton", &pSingleton);
  const QUrl url(
      QStringLiteral("/home/almog/CLionProjects/Students-UI/src/main.qml"));

  engine.load(url);

  return QGuiApplication::exec();
}
