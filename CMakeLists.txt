cmake_minimum_required(VERSION 3.5)

project(Askue VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialBus Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialBus Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Askue
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        modbusclient.h modbusclient.cpp
        deviceview.h deviceview.cpp
        devicemodel.h devicemodel.cpp
        deviceaddwindow.h deviceaddwindow.cpp
        device.h device.cpp
        modbusmanager.h modbusmanager.cpp
        valueview.h valueview.cpp
        modbusintervalrequester.h modbusintervalrequester.cpp
        valuemodel.h valuemodel.cpp
        value.h value.cpp
        database.h database.cpp
        buddylineedit.h buddylineedit.cpp
        devicecontextmenu.h devicecontextmenu.cpp
        valueaddwindow.h valueaddwindow.cpp
        valuerequestoptions.h valuerequestoptions.cpp
        devicedelegate.h devicedelegate.cpp
        treeitem.h treeitem.cpp
        deviceitem.h deviceitem.cpp
        valueitem.h valueitem.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Askue APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Askue SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Askue
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Askue PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::SerialBus
    Qt${QT_VERSION_MAJOR}::Sql
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Askue)
endif()
set_target_properties(Askue PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Askue
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Askue)
endif()
