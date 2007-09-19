######################################################################
# Automatically generated by qmake (2.01a) lun sep 10 12:49:25 2007
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . lib resource lib/widgets
INCLUDEPATH += . lib lib/widgets

# Input
HEADERS += lib/AppHandler.h \
           lib/CommandProcess.h \
           lib/OptionBox.h \
           lib/VmdMainWindow.h \
           lib/Widgets.h \
           lib/widgets/CommandLineWidget.h \
           lib/widgets/OutputWidget.h \
           lib/widgets/RotationWidget.h \
           lib/widgets/RotaWidget.h \
           lib/widgets/ScaleWidget.h \
           lib/widgets/MouseModeWidget.h
FORMS += lib/widgets/CommandLineWidget.ui \
         lib/widgets/OutputWidget.ui \
         lib/widgets/RotationWidget.ui \
         lib/widgets/RotaWidget.ui \
         lib/widgets/ScaleWidget.ui \
         lib/widgets/MouseModeWidget.ui
SOURCES += main.cpp \
           lib/AppHandler.cpp \
           lib/CommandProcess.cpp \
           lib/OptionBox.cpp \
           lib/VmdMainWindow.cpp \
           lib/Widgets.cpp \
           lib/widgets/CommandLineWidget.cpp \
           lib/widgets/OutputWidget.cpp \
           lib/widgets/RotationWidget.cpp \
           lib/widgets/RotaWidget.cpp \
           lib/widgets/ScaleWidget.cpp \
           lib/widgets/MouseModeWidget.cpp
RESOURCES += resource/default.qrc

QT += xml
