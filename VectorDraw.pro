QT += widgets svg
qtHaveModule(printsupport): QT += printsupport


HEADERS       = \
    whiteboard.h \
    mainwindow.h \
    blackboard.h
SOURCES       = main.cpp \
                mainwindow.cpp \
    whiteboard.cpp \
    blackboard.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/scribble
INSTALLS += target

FORMS += \
    mainwindow.ui
