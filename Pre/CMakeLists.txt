
set(qt_components Core Gui Widgets Charts)
list(SORT qt_components)
# We have ui files, so this will also bring in the macro:
#   qt5_wrap_ui or qt_wrap_ui from Widgets.
find_package(Qt5 QUIET
  REQUIRED COMPONENTS ${qt_components}
)

foreach(_qt_comp IN LISTS qt_components)
  list(APPEND qt_modules "Qt5::${_qt_comp}")
endforeach()

message (STATUS "VTK_VERSION: ${VTK_VERSION}, Qt Version: ${Qt${VTK_QT_VERSION}Widgets_VERSION}")

# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${SRC_APPLICATIONS}/include)
include_directories(${SRC_CORE}/include)
include_directories(${SRC_LIBRARY})
include(${CMAKE_CURRENT_SOURCE_DIR}/sources.cmake)

add_library(qt_pre
        PerformanceCurve.cpp
        PerformanceCurve.h)

add_library(qt_pre_no_vtk)

target_sources(qt_pre PRIVATE ${QT_PRE2_VTK_SRC} ${QT_PRE2_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc)
target_sources(qt_pre_no_vtk PRIVATE  ${QT_PRE2_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc)
if (Qt${VTK_QT_VERSION}Widgets_VERSION VERSION_LESS "5.11.0")
  qt5_use_modules(qt_pre ${qt_components})
  qt5_use_modules(qt_pre_no_vtk ${qt_components})
else()
  target_link_libraries(qt_pre ${qt_modules})
  target_link_libraries(qt_pre_no_vtk ${qt_modules})
endif()
target_link_libraries(qt_pre ${VTK_LIBRARIES} ${PRE_BASE_LIB} ${PRE_CORE_LIB} ${PRE_APP_LIB})
target_link_libraries(qt_pre_no_vtk ${PRE_BASE_LIB} ${PRE_CORE_LIB} ${PRE_APP_LIB})
target_compile_definitions(qt_pre_no_vtk PRIVATE "-DNO_VTK_WINDOW")

install(TARGETS qt_pre
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(TARGETS qt_pre_no_vtk
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

#add_executable(qt_pre2_standalone ${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc)
add_executable(qt_pre_standalone)
target_sources(qt_pre_standalone PRIVATE ${QT_PRE2_MAIN_SRC})
target_link_libraries(qt_pre_standalone qt_pre)
add_executable(no_vtk_qt_pre_standalone)
target_sources(no_vtk_qt_pre_standalone PRIVATE ${QT_PRE2_MAIN_SRC})
target_link_libraries(no_vtk_qt_pre_standalone qt_pre_no_vtk)
target_compile_definitions(no_vtk_qt_pre_standalone PRIVATE "-DNO_VTK_WINDOW")

install(TARGETS qt_pre_standalone
        RUNTIME DESTINATION bin
)

install(TARGETS no_vtk_qt_pre_standalone
        RUNTIME DESTINATION bin
)

