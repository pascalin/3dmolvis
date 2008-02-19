# Establish the project name
PROJECT(vmdgui)

# CMake version check
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0)

# Find and setup Qt4 for this project
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

# Project sources
SET(vmdgui_SRCS
    lib/widgets/GenericWidget.cpp
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
    lib/widgets/GenericWidget.h
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

# Set actual translations to process
SET(vmdgui_TRANS
	es
)

FIND_PROGRAM(PO2TS_PATH po2ts DOC "Path of po2ts script")

IF(PO2TS_PATH)
FOREACH(lang ${vmdgui_TRANS})

ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/vmdgui_${lang}.ts
			   COMMAND ${PO2TS_PATH} ARGS ${CMAKE_CURRENT_SOURCE_DIR}/i18n/${lang}/vmdgui_${lang}.po > ${CMAKE_CURRENT_BINARY_DIR}/vmdgui_${lang}.ts
			   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/i18n/${lang}/vmdgui_${lang}.po
			   COMMENT vmdgui_${lang}.ts
)

ENDFOREACH(lang)
FIND_PROGRAM(LRELEASE_PATH lrelease DOC "Path of QT Linguist lrelease program")

IF(LRELEASE_PATH)
FOREACH(lang ${vmdgui_TRANS})

ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/i18n/${lang}/vmdgui_${lang}.qm
			  COMMAND ${LRELEASE_PATH} ARGS ${CMAKE_CURRENT_BINARY_DIR}/vmdgui_${lang}.ts -qm ${CMAKE_CURRENT_BINARY_DIR}/i18n/${lang}/vmdgui_${lang}.qm
			  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vmdgui_${lang}.ts
			  COMMENT vmdgui_${lang}.qm
)
ADD_CUSTOM_TARGET(vmdgui_${lang}.qm)
ADD_DEPENDENCIES(vmdgui vmdgui_${lang}.qm)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/i18n/${lang}/vmdgui_${lang}.qm DESTINATION i18n/${lang}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

ENDFOREACH(lang)
ENDIF(LRELEASE_PATH)
ENDIF(PO2TS_PATH)

INSTALL(FILES vmdgui DESTINATION bin/ PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)



INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "3DMolvis: Molecular visualization for everyone")
SET(CPACK_PACKAGE_VENDOR "Laboratorio de Visualizacion Ixtli, Universidad Nacional Autonoma de Mexico")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "b1")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} 3DMolvis")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\tdmolvis.sourceforge.net")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.molviz.pascal-in.net")
  SET(CPACK_NSIS_CONTACT "vmdgui@groups.google.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/MyExecutable")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")
INCLUDE(CPack)
