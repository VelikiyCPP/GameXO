cmake_minimum_required(VERSION 3.10)

project(GameXO)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/code/cpp)

add_executable(${PROJECT_NAME}
  ${SOURCE_DIR}/main.cpp
  ${SOURCE_DIR}/AIPlayer.cpp
  ${SOURCE_DIR}/Board.cpp
  ${SOURCE_DIR}/Game.cpp
  ${SOURCE_DIR}/Menu.cpp
  ${SOURCE_DIR}/MenuItem.cpp
  ${SOURCE_DIR}/OutputInformation.cpp
  ${SOURCE_DIR}/Player.cpp
  ${SOURCE_DIR}/Setting.cpp
  ${SOURCE_DIR}/SaveProcess.cpp
)