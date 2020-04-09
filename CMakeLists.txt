cmake_minimum_required(VERSION 2.9)

project(ImageToPDF)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BINARY_NAME "imagetopdf")

file(GLOB SOURCES src/*.cpp src/*.h src/*.hpp)
set (UIS src/imagetopdf.ui)
set (RESOURCES Images/res.qrc)


#file(GLOB HEADERS include/*.h)

#include_directories(./include)

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

#set(IMAGE_MAGICK "`Magick++-config --cxxflags --cppflags --ldflags --libs`")
#link_directories(${ImageMagick_INCLUDE_DIRS})
#link_directories(${ImageMagick_LIBRARIES})


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++14 -O0 -fpic  -lMagick++-7.Q16 -lMagickCore-7.Q16 ${IMAGE_MAGICK}" )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++14 -O2 ${IMAGE_MAGICK}" )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "Setting build type to 'Debug' as none was specified.")
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

QT5_WRAP_UI( UI_HEADERS ${UIS} )
#qt5_add_resources (RCC_SOURCES ${RESOURCES})

#add_library(archive OBJECT src/imagetopdfdialog.cpp)
#target_link_libraries(archive ${ImageMagick_LIBRARIES} )
#qt5_use_modules(archive Widgets)

find_package(ImageMagick COMPONENTS Magick++ MagickWand MagickCore convert REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})
add_definitions(${ImageMagick_DEFINITIONS})

add_executable(${BINARY_NAME} ${SOURCES} ${UI_HEADERS} ${RESOURCES} )

qt5_use_modules(${BINARY_NAME} Widgets)
target_link_libraries(${BINARY_NAME} ${ImageMagick_LIBRARIES})


#find_package(Threads REQUIRED)
#if(THREADS_HAVE_PTHREAD_ARG)
#        add_definitions(-DHAVE_PTHREAD)
#	target_compile_options(producer_consumer PUBLIC "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#        add_definitions(-DHAVE_PTHREAD=1)
#	target_link_libraries(producer_consumer "${CMAKE_THREAD_LIBS_INIT}")
#endif()

add_definitions(-D_DEBUG_OUTPUT_=1)
add_definitions(-DTESTING_MAGICK=0)
add_definitions(-DTESTING_QT=1)




