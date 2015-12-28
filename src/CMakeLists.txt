set(SOURCES
		abstracteducation.cpp
		abstractjob.cpp
		age.cpp
		educationregistry.cpp
		expenses.cpp
		genericeducation.cpp
		genericjob.cpp
		health.cpp
		jobregistry.cpp
		main.cpp
		mainwindow.cpp
		money.cpp
		nulleducation.cpp
		nulljob.cpp
		player.cpp
)

QT4_WRAP_UI(UISrcs mainwindow.ui)
QT4_WRAP_CPP(MOCSrcs
		abstracteducation.h
		abstractjob.h
		age.h
		educationregistry.h
		expenses.h
		health.h
		genericeducation.h
		genericjob.h
		ieducation.h
		ijob.h
		jobregistry.h
		mainwindow.h
		money.h
		nulleducation.h
		nulljob.h
		player.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(MyCareer ${SOURCES} ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(MyCareer ${QT_LIBRARIES})
