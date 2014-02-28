QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = \
    whiteboard.h \
    mainwindow.h
SOURCES       = main.cpp \
                mainwindow.cpp \
    whiteboard.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/scribble
INSTALLS += target
