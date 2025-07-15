list(APPEND QT_POST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorBarDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CutplaneDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IsoSurfaceDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MeridionalPlaneDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConstHeightPlaneDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SelectBoundaryDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkAesReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vtkDisplayWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScaleFactorDialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ConstHeightPlaneDialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ConstSettingDialog.cpp
)

list(APPEND QT_POST_MAIN_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
