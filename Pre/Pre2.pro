QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BoundaryMerger.cpp \
    MergerCore.cpp \
    PreProcessSettings.cpp \
    loadprofile.cpp \
    main.cpp \
    PreMainWindow.cpp \
    BCExtra.cpp \
    SelectFile.cpp \
    # vtkCGNSReader.cpp \
    UtilitiesGUIPre.cpp

HEADERS += \
    BoundaryMerger.h \
    MergerCore.h \
    PreMainWindow.h \
    PreProcessSettings.h \
    BCExtra.h \
    SelectFile.h \
    loadprofile.h \
    # vtkCGNSReader.h \
    UtilitiesGUIPre.h

FORMS += \
    BoundaryMerger.ui \
    PreMainWindow.ui \
    BCExtra.ui \
    SelectFile.ui \
    loadprofile.ui

PKG_PATH = /Users/zhoutengye/packages/aesim_pre_gui
AESIM_PATH = /Users/zhoutengye/aesim_pre

LIBS += \
-L$${PKG_PATH}/lib\
-L$${PKG_PATH}/hdf5-1.12.2/lib \
-L$${PKG_PATH}/cgns-3.4.1/lib \
-L$${PKG_PATH}/OpenBLAS-0.3.21/lib \
-L$${PKG_PATH}/yaml-cpp/lib \
-L$${PKG_PATH}/vtk-9.1.0/lib \
-laesim_base -laesim_pre_core -laesim_pre_app_lib -lhdf5 -lyaml-cpp -lcgns

VTK_FILES=$$files($${PKG_PATH}/vtk-9.1.0/lib/lib*9.1.dylib)
for (FILE, VTK_FILES){
    BASENAME = $$basename(FILE)
    LIBS += $$FILE
}

INCLUDEPATH += \
$${AESIM_PATH}/library \
$${AESIM_PATH}/applications/include \
$${AESIM_PATH}/core/include \
$${PKG_PATH}/cgns-3.4.1/include \
$${PKG_PATH}/hdf5-1.12.2/include \
$${PKG_PATH}/yaml-cpp/include \
$${PKG_PATH}/vtk-9.1.0/include/vtk-9.1 \

# QMAKE_LIBDIR += \
# "/home/anthony/packages/aesim_pre_gui/lib"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../resources/resources.qrc
