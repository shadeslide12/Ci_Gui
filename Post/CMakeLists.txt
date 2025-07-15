# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${SRC_LIBRARY})
include(${CMAKE_CURRENT_SOURCE_DIR}/sources.cmake)

add_library(qt_post ${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc)

target_sources(qt_post PRIVATE ${QT_POST_SRC})
if (Qt${VTK_QT_VERSION}Widgets_VERSION VERSION_LESS "5.11.0")
  qt5_use_modules(qt_post ${qt_components})
else()
  target_link_libraries(qt_post ${qt_modules})
endif()
target_link_libraries(qt_post ${VTK_LIBRARIES} ${PRE_BASE_LIB})

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS qt_post
  MODULES ${VTK_LIBRARIES}
)

install(TARGETS qt_post
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

add_executable(qt_post_standalone)
target_sources(qt_post_standalone PRIVATE ${QT_POST_MAIN_SRC})
target_link_libraries(qt_post_standalone qt_post)

install(TARGETS qt_post_standalone
        RUNTIME DESTINATION bin
)

vtk_module_autoinit(
        TARGETS qt_post_standalone
        MODULES ${VTK_LIBRARIES}
)
