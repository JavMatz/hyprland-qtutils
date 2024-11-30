cmake_minimum_required(VERSION 3.16)

project(dialog VERSION ${VER} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Quick QuickControls2 WaylandClient)
find_package(PkgConfig REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(dialog
    main.cpp
    Dialog.cpp
)

qt_add_qml_module(dialog
    URI org.dialog.dialog
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(dialog PRIVATE
    Qt6::Widgets Qt6::QuickControls2 Qt6::WaylandClientPrivate
)


include(GNUInstallDirs)
install(TARGETS dialog
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
