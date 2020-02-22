###############################################################################
# Warning: This file is not process by qmake, it is solely used as a convenient
# way to work with qt creator IDE.
# Build is handle exclusively with CMake please go to the CMakeLists.txt file
# to change build configuration
###############################################################################

SOURCES += node_deformer_offset.cpp

#-------------------------------------------------------------------------------

HEADERS +=

#-------------------------------------------------------------------------------
# SHADERS
#SOURCES +=

#-------------------------------------------------------------------------------

#OTHER_FILES += CMakeLists.txt

################################################################################

# Some hacks for qt Creator to correctly highlight code
# and activate autocompletion for the librairies used in this project

QT += opengl

INCLUDEPATH += "C:/Program Files/Autodesk/Maya2014/include"

DEPENDPATH += $${INCLUDEPATH}

DEFINES += "PLUGIN_EXPORT="
DEFINES += "FND_EXPORT="
DEFINES += "IMAGE_EXPORT="
DEFINES += "OPENMAYA_EXPORT="
DEFINES += "OPENMAYAUI_EXPORT="
DEFINES += "OPENMAYAANIM_EXPORT="
DEFINES += "OPENMAYAFX_EXPORT="
DEFINES += "OPENMAYARENDER_EXPORT="
