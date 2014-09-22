# Add more folders to ship with the application, here
QT += opengl
folder_01.source = qml/BaseIVL2
#folder_01.source += qml/BaseIVL
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

DEFINES += DESKTOP_LINUX

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
  #  CAN/socketcandevice.cpp \
    CAN/emulationcandevice.cpp \
    CAN/canunitspo.cpp \
    CAN/canunitpower.cpp \
    CAN/canunitmix.cpp \
    CAN/canunitkivl.cpp \
    CAN/canunitcapno2.cpp \
    CAN/canunitcapno1.cpp \
    CAN/canunit.cpp \
    CAN/canmessage.cpp \
    CAN/candevice.cpp \
    CAN/canbuffer.cpp \
    regimemanager.cpp \
    canmanager.cpp \
    ventmode/ventmodemanager.cpp \
    i18n/translationmanager.cpp \
    keyboardSimulator/keyboardsimulator.cpp \
    graphics/graphicmanager.cpp \
    graphics/graphicobject.cpp \
    graphics/graphicline.cpp \
    graphics/graphicloop.cpp \
    events/eventmanager.cpp \
    events/event.cpp \
  #  CAN/socketcanwt.cpp \
   # CAN/socket.cpp \
   # CAN/socketcanrt.cpp \
    options/optionsmanager.cpp \
    types/tunningparameter.cpp \
    types/associatedparameter.cpp \
    types/measureparameter.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

INSTALLS += target

HEADERS += \
   # CAN/socketcandevice.h \
    CAN/emulationcandevice.h \
    CAN/canunitspo.h \
    CAN/canunitpower.h \
    CAN/canunitmix.h \
    CAN/canunitkivl.h \
    CAN/canunitcapno2.h \
    CAN/canunitcapno1.h \
    CAN/canunit.h \
    CAN/canmessage.h \
    CAN/candevice.h \
    CAN/canbuffer.h \
    CAN/can_id.h \
    types/parametersTypes.h \
    regimemanager.h \
    canmanager.h \
    ventmode/ventmodemanager.h \
    i18n/translationmanager.h \
    keyboardSimulator/keyboardsimulator.h \
   # graphics/fb.h \
    graphics/graphicmanager.h \
    ventmode/limitdefines.h \
    graphics/graphicobject.h \
    graphics/graphicline.h \
    graphics/graphicloop.h \
    events/eventmanager.h \
    events/event.h \
    events/eventIDs.h \
   # CAN/socketcanwt.h \
   # CAN/socket.h \
   # CAN/socketcanrt.h \
    options/optionsmanager.h \
    types/tunningparameter.h \
    types/associatedparameter.h \
    types/measureparameter.h

RESOURCES += \
    resources.qrc

TRANSLATIONS += ru.ts en.ts


INSTALLS += target

OTHER_FILES += \
    qml/BaseIVL2/styleTypes/EditedParameterLineBool.qml
