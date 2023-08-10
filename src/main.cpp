#include <QGuiApplication>
#include <QUrl>

#include "aplicationsingleton.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include <qtgql/bases/bases.hpp>
#include <qtgql/gqloverhttp/gqloverhttp.hpp>
#include <string>

int main(int argc, char *argv[]) {
  QGuiApplication gui_app(argc, argv);
  QQmlApplicationEngine engine;
  auto env =
      std::shared_ptr<qtgql::bases::Environment>(new qtgql::bases::Environment(
          "Students", std::unique_ptr<qtgql::bases::NetworkLayerABC>(
                          new qtgql::gqloverhttp::GraphQLOverHttp(
                              {"http://127.0.0.1:8000/graphql/"}))));
  qtgql::bases::Environment::set_gql_env(env);
  auto app = App();
  qmlRegisterSingletonInstance("App", 1, 0, "App", &app);
  const QUrl url(
      QStringLiteral("/home/almog/CLionProjects/Students-UI/src/main.qml"));

  engine.load(url);

  return gui_app.exec();
}
