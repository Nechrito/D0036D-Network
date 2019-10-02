PROJECT(Client)

FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)

SET(files_headers ${headers})
SET(files_sources ${sources})

SOURCE_GROUP("Header Files" FILES ${files_headers})
SOURCE_GROUP("Source Files" FILES ${files_sources})

ADD_EXECUTABLE(Client ${files_headers} ${files_sources})
TARGET_LINK_LIBRARIES(Client core render)
ADD_DEPENDENCIES(Client core render)

SET_PROPERTY (DIRECTORY PROPERTY VS_STARTUP_PROJECT "Client")
SET_TARGET_PROPERTIES(Client PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)