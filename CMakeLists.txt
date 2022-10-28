

#file (GLOB THIS_APP_HEADERS "concurrentbtle.h" "stimulator.h" "cadenceblock.h" "pid.h" "globalvariables.h" "chart.h" )
#get_filename_component(THIS_APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#cmake_minimum_required(VERSION 3.14)
#project(btle_fede VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


#find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
#find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

#add_executable(${THIS_APP_NAME} ${THIS_APP_SOURCES} ${THIS_APP_HEADERS})
#target_link_libraries(${THIS_APP_NAME} Qt${QT_VERSION_MAJOR}::Core)
#add_library(libsmpt STATIC IMPORTED)
#set_target_properties(libsmpt PROPERTIES
#    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libsmpt.a)

#target_link_libraries(${THIS_APP_NAME} pthread rt libsmpt wiringPi)
#target_link_libraries(${THIS_APP_NAME} libconfig++.a )

#add_executable(${THIS_APP_NAME}_BLE main main.cpp concurrentbtle.cpp concurrentbtle.h ${THIS_APP_HEADERS})
#target_link_libraries(${THIS_APP_NAME}_BLE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Bluetooth)

#add_executable(${THIS_APP_NAME}_FES main main_fes.cpp stimulator.cpp cadenceblock.cpp pid.cpp globalvariables.cpp stimulator.h cadenceblock.h pid.h globalvariables.h chart.h header.h   ${THIS_APP_HEADERS})
#target_link_libraries(${THIS_APP_NAME}_FES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Bluetooth)
#target_link_libraries(${THIS_APP_NAME}_FES pthread rt libsmpt wiringPi)
#target_link_libraries(${THIS_APP_NAME}_FES libconfig++.a )



get_filename_component(THIS_APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required(VERSION 3.14)

project(btle_fede LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

add_executable(${THIS_APP_NAME}_BLE
   main.cpp
  concurrentbtle.cpp
  concurrentbtle.h
  shared_memory.cpp
  shared_memory.h
  temp.cpp
    temp.h
  )
target_link_libraries(${THIS_APP_NAME}_BLE Qt${QT_VERSION_MAJOR}::Core  Qt${QT_VERSION_MAJOR}::Bluetooth)

# GUI

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

add_executable(${THIS_APP_NAME}_GUI  main_gui.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui input.cpp input.ui input.h cadence.cpp cadence.h cadence.ui stimulation.cpp stimulation.h stimulation.ui
    user.ui user.cpp user.h calibration.h calibration.ui calibration.cpp shared_memory.cpp shared_memory.h temp2.cpp temp2.h report.cpp report.h report.ui
    trainingmodality.cpp trainingmodality.h trainingmodality.ui
    ${THIS_APP_HEADERS})
target_link_libraries(${THIS_APP_NAME}_GUI Qt${QT_VERSION_MAJOR}::Core  Qt${QT_VERSION_MAJOR}::Bluetooth)
target_link_libraries(${THIS_APP_NAME}_GUI  Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${THIS_APP_NAME}_GUI pthread libconfig++.a)




#REHAMOVE

add_executable(${THIS_APP_NAME}_FES  main_fes.cpp
    header.h globalvariables.h chart.cpp chart.h globalvariables.cpp
    pid.h pid.cpp stimulator.cpp stimulator.h cadenceblock.cpp cadenceblock.h shared_memory.cpp shared_memory.h temp2.cpp temp2.h thread_class.cpp thread_class.h thread_app.h thread_app.cpp
    ${REHAMOVE_SOURCES} ${REHAMOVE_HEADERS} ${THIS_APP_HEADERS})


add_library(libsmpt STATIC IMPORTED)
set_target_properties(libsmpt PROPERTIES
    IMPORTED_LOCATION /home/pi/Desktop/btle_fede/libsmpt.a)

target_link_libraries(${THIS_APP_NAME}_FES pthread rt libsmpt   libconfig++.a wiringPi
   # matio
    )




