project(HoareSort)

file(GLOB SOURCES "./lib/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

