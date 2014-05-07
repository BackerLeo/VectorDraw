QT += widgets svg
qtHaveModule(printsupport): QT += printsupport


HEADERS       = \
    whiteboard.h \
    mainwindow.h \
    premadeforms.h
SOURCES       = main.cpp \
                mainwindow.cpp \
    whiteboard.cpp \
    premadeforms.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/scribble
INSTALLS += target

FORMS += \
    mainwindow.ui
