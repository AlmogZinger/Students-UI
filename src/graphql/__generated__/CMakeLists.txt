cmake_minimum_required(VERSION 3.20)
set(EnvTarget "Students")
set(QTGQL_QML_PLUGIN_DIRECTORY ${CMAKE_BINARY_DIR}/qml/GraphQL/${EnvTarget})

project(${EnvTarget} LANGUAGES CXX)

# add import path for Qt-Creator usage.
if (NOT ${CMAKE_BINARY_DIR}/qml IN_LIST QML_DIRS)
    list(APPEND QML_DIRS ${CMAKE_BINARY_DIR}/qml)
    set(QML_IMPORT_PATH "${QML_DIRS}" CACHE PATH "Qt Creator 10.1 extra qml import paths")
endif()

# Configure general compilation
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml)

if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

# see https://doc.qt.io/qt-6/qt-cmake-policy-qtp0001.html
qt_policy(SET QTP0001 NEW)

add_library(${PROJECT_NAME}schema
        schema.hpp
        )
target_link_libraries(${PROJECT_NAME}schema
        PUBLIC
        Qt::Core
        qtgql::qtgql
        )
qt_add_qml_module(${PROJECT_NAME}StudentsQuery
        URI GraphQL.${PROJECT_NAME}.StudentsQuery
        # Using PLUGIN_TARGET in static library compilation will cause link failure
        OUTPUT_DIRECTORY ${QTGQL_QML_PLUGIN_DIRECTORY}/StudentsQuery
        # TYPEINFO "plugins.qmltypes"
        SOURCES
        /home/almog/CLionProjects/Students-UI/src/graphql/__generated__/StudentsQuery.hpp
        /home/almog/CLionProjects/Students-UI/src/graphql/__generated__/StudentsQuery.cpp
        )

target_link_libraries(${PROJECT_NAME}StudentsQuery PUBLIC
        Qt::CorePrivate
        Qt::QuickPrivate
        Qt::QmlPrivate
        ${PROJECT_NAME}schema
        qtgql::qtgql
        )


qt_add_library(${PROJECT_NAME} "")

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    Qt6::Core
    qtgql::qtgql
    ${PROJECT_NAME}schema
    ${PROJECT_NAME}StudentsQuery

)
