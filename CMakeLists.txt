# Establish the project name
PROJECT(vmdgui)

# CMake version check
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0)

# Find and setup Qt4 for this project
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

# Project sources
SET(vmdgui_SRCS
    lib/widgets/CommandLineWidget.cpp
    lib/widgets/OutputWidget.cpp
    lib/widgets/MouseModeWidget.cpp
    lib/widgets/GLShadingWidget.cpp
    lib/widgets/RotationWidget.cpp
    lib/widgets/RotaWidget.cpp
    lib/widgets/ScaleWidget.cpp
    lib/widgets/AnimateWidget.cpp
    lib/widgets/SimWidget.cpp
    lib/widgets/StereoWidget.cpp
    lib/widgets/ResetWidget.cpp
    lib/widgets/PlanesWidget.cpp
    lib/AppHandler.cpp
    lib/CommandProcess.cpp
    lib/OptionBox.cpp
    lib/VmdMainWindow.cpp
    lib/Widgets.cpp
    main.cpp
)

# Project headers requiring MOC processing
SET(vmdgui_MOC_HDRS
    lib/widgets/CommandLineWidget.h
    lib/widgets/OutputWidget.h
    lib/widgets/MouseModeWidget.h
    lib/widgets/GLShadingWidget.h
    lib/widgets/RotationWidget.h
    lib/widgets/RotaWidget.h
    lib/widgets/ScaleWidget.h
    lib/widgets/AnimateWidget.h
    lib/widgets/SimWidget.h
    lib/widgets/StereoWidget.h
    lib/widgets/ResetWidget.h
    lib/widgets/PlanesWidget.h
    lib/CommandProcess.h
    lib/OptionBox.h
    lib/VmdMainWindow.h
)

# Get list of MOC processed files
QT4_WRAP_CPP(vmdgui_MOC_SRCS ${vmdgui_MOC_HDRS})

# UI files requiring uic processing
SET(vmdgui_UIS
	lib/widgets/AnimateWidget.ui
	lib/widgets/CommandLineWidget.ui
	lib/widgets/GLShadingWidget.ui
	lib/widgets/MouseModeWidget.ui
	lib/widgets/OutputWidget.ui
	lib/widgets/PlanesWidget.ui
	lib/widgets/ResetWidget.ui
	lib/widgets/RotationWidget.ui
	lib/widgets/RotaWidget.ui
	lib/widgets/ScaleWidget.ui
	lib/widgets/SimWidget.ui
	lib/widgets/StereoWidget.ui
	lib/VmdMainWindow.ui
)

# Get list of UIC processed files
QT4_WRAP_UI(vmdgui_UIS_H ${vmdgui_UIS})

# Resources included on the project
SET(vmdgui_RCCS
	resource/default.qrc
)

# Process resource files
QT4_ADD_RESOURCES(vmdgui_RCC_SRCS ${vmdgui_RCCS})

# Set include directories
INCLUDE_DIRECTORIES(
	${QT_INCLUDE_DIR}
	${QT_QTXML_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

# Set build target
ADD_EXECUTABLE(vmdgui
	${vmdgui_SRCS}
	${vmdgui_MOC_SRCS}
	${vmdgui_UIS_H}
	${vmdgui_RCC_SRCS}
)

# Linking options
TARGET_LINK_LIBRARIES(vmdgui ${QT_LIBRARIES} ${QT_QTXML_LIBRARY})

FIND_PROGRAM(PO2TS_PATH po2ts DOC "Path of po2ts script")

IF(PO2TS_PATH)

#ADD_CUSTOM_COMMAND(OUTPUT ${TsFile} COMMAND ${PO2TS_PATH} ARGS ${PoFile} > ${TsFile} DEPENDS ${PoFile} COMMENT ${BaseName}.ts)

SET(vmdgui_POS
	i18n/es/vmdgui_es.po
)

ENDIF(PO2TS_PATH)

FIND_PROGRAM(LRELEASE_PATH lrelease DOC "Path of QT Linguist lrelease program")

IF(LRELEASE_PATH)

ENDIF(LRELEASE_PATH)

INSTALL(FILES vmdgui DESTINATION bin/ PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
