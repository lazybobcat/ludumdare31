TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -llua -ldl
#QMAKE_CXXFLAGS += -std=c++11 -D DEBUG
QMAKE_CXXFLAGS += -std=c++11
# These lines are for i386 arch executable. It needs lib32 libraries
#QMAKE_CXXFLAGS += -m32
#QMAKE_LFLAGS += -m32
OBJECTS_DIR = .obj

SOURCES += main.cpp \
    controllers/playercontroller.cpp \
    entities/emitternode.cpp \
    entities/entity.cpp \
    entities/particlenode.cpp \
    entities/quadtree.cpp \
    entities/scenenode.cpp \
    entities/soundnode.cpp \
    entities/spritenode.cpp \
    entities/textnode.cpp \
    events/command.cpp \
    events/commandqueue.cpp \
    GUI/button.cpp \
    GUI/container.cpp \
    GUI/label.cpp \
    GUI/lineedit.cpp \
    GUI/widget.cpp \
    lua/luaexposal.cpp \
    lua/SLB.cpp \
    resources/affectors.cpp \
    resources/animation.cpp \
    resources/musicplayer.cpp \
    resources/particle.cpp \
    resources/scriptplayer.cpp \
    resources/soundplayer.cpp \
    states/paralleltask.cpp \
    states/state.cpp \
    states/statestack.cpp \
    states/titlestate.cpp \
    application.cpp \
    datatables.cpp \
    utils.cpp \
    utils.inl \
    world.cpp \
    states/gamestate.cpp \
    entities/playerentity.cpp \
    entities/traplistnode.cpp \
    entities/burgertrap.cpp \
    entities/holetrap.cpp \
    entities/tnttrap.cpp \
    entities/explosion.cpp \
    entities/basickidnode.cpp \
    entities/projectile.cpp \
    entities/ammonode.cpp \
    entities/cameranode.cpp \
    entities/wavegenerator.cpp \
    entities/helpnode.cpp \
    states/gameoverstate.cpp \
    entities/bubblenode.cpp

OTHER_FILES +=

HEADERS += \
    controllers/playercontroller.h \
    entities/emitternode.h \
    entities/entity.h \
    entities/particlenode.h \
    entities/quadtree.h \
    entities/scenenode.h \
    entities/soundnode.h \
    entities/spritenode.h \
    entities/textnode.h \
    events/category.h \
    events/command.h \
    events/commandqueue.h \
    GUI/button.h \
    GUI/container.h \
    GUI/label.h \
    GUI/lineedit.h \
    GUI/widget.h \
    lua/luaexposal.h \
    lua/lunar.h \
    lua/SLB.hpp \
    resources/affectors.h \
    resources/animation.h \
    resources/musicplayer.h \
    resources/particle.h \
    resources/resourceholder.h \
    resources/resourceidentifiers.h \
    resources/scriptplayer.h \
    resources/soundplayer.h \
    states/paralleltask.h \
    states/state.h \
    states/stateidentifiers.h \
    states/statestack.h \
    states/titlestate.h \
    application.h \
    datatables.h \
    utils.h \
    world.h \
    states/gamestate.h \
    entities/playerentity.h \
    entities/traplistnode.h \
    entities/burgertrap.h \
    entities/holetrap.h \
    entities/tnttrap.h \
    entities/explosion.h \
    entities/basickidnode.h \
    entities/projectile.h \
    entities/ammonode.h \
    entities/cameranode.h \
    entities/wavegenerator.h \
    entities/helpnode.h \
    states/gameoverstate.h \
    entities/bubblenode.h

