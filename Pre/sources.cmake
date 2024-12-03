list(APPEND QT_PRE2_SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/PreMainWindow.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/PreProcessSettings.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/BCExtra.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/UtilitiesGUIPre.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/SelectFile.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/loadprofile.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/BoundaryMerger.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MergerCore.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/PerformanceCurve.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Perform_Plot.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Residual_Plot.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MonitorPlot.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/DataStructure.h
   ${CMAKE_CURRENT_SOURCE_DIR}/DataStructure.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/bcaddition.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/yamlreader.cpp
)

list(APPEND QT_PRE2_VTK_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/vtkCGNSReader.cpp
)

list(APPEND QT_PRE2_MAIN_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
