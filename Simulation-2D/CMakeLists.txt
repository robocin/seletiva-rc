cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(robocin2d)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DELOG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++11 -fPIC -lm")


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(ZLIB REQUIRED)
find_package(FLEX REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})


add_library(librcsc SHARED IMPORTED)
include_directories(${SOURCE_DIR})
set(LIBRCSC_INCLUDE_DIR ${/usr/local/include/rcsc})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
include_directories(${SOURCE_DIR} ${SOURCE_DIR}/chain_action)

set(PLAYER_CPP bhv_basic_move.cpp bhv_basic_offensive_kick.cpp
  bhv_basic_tackle.cpp bhv_custom_before_kick_off.cpp
  bhv_go_to_static_ball.cpp
  bhv_goalie_basic_move.cpp bhv_goalie_chase_ball.cpp
  bhv_goalie_free_kick.cpp bhv_prepare_set_play_kick.cpp
  bhv_set_play.cpp bhv_set_play_free_kick.cpp
  bhv_set_play_goal_kick.cpp bhv_set_play_indirect_free_kick.cpp
  bhv_set_play_kick_in.cpp bhv_set_play_kick_off.cpp
  bhv_their_goal_kick_move.cpp bhv_penalty_kick.cpp
  neck_default_intercept_neck.cpp
  neck_goalie_turn_neck.cpp neck_offensive_intercept_neck.cpp
  view_tactical.cpp intention_receive.cpp
  intention_wait_after_set_play_kick.cpp soccer_role.cpp
  role_center_back.cpp role_center_forward.cpp role_defensive_half.cpp
  role_goalie.cpp role_offensive_half.cpp role_sample.cpp
  role_side_back.cpp role_side_forward.cpp role_side_half.cpp
  role_keepaway_keeper.cpp role_keepaway_taker.cpp
  sample_communication.cpp keepaway_communication.cpp
  sample_field_evaluator.cpp sample_player.cpp strategy.cpp)


foreach(src ${PLAYER_CPP})
  list(APPEND PLAYER_SOURCES ${SOURCE_DIR}/${src})
endforeach(src ${PLAYER_CPP})
file(GLOB CHAIN_ACTION_SOURCES ${SOURCE_DIR}/chain_action/*.cpp)

list(APPEND RCSC_LINK_LIBS rcsc_agent rcsc_geom rcsc_param rcsc_ann rcsc_net rcsc_gz rcsc_time rcsc_rcg z)

add_library(player_chain_action STATIC ${PLAYER_SOURCES} ${CHAIN_ACTION_SOURCES})
target_link_libraries(player_chain_action -Wl,--allow-multiple-definition -Wl,--no-whole-archive)
target_link_libraries(player_chain_action ${PYTHON_LIBRARIES})

add_executable(robocin_coach ${SOURCE_DIR}/main_coach.cpp ${SOURCE_DIR}/sample_coach.cpp)
add_dependencies(robocin_coach librcsc)

add_executable(robocin_player ${SOURCE_DIR}/main_player.cpp ${SOURCE_DIR}/sample_player.cpp)
target_link_libraries(robocin_player -Wl,--allow-multiple-definition -Wl,--no-whole-archive)
target_link_libraries(robocin_player ${PYTHON_LIBRARIES})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

add_executable(robocin_trainer ${SOURCE_DIR}/main_trainer.cpp ${SOURCE_DIR}/sample_trainer.cpp)

add_dependencies(player_chain_action librcsc)
add_dependencies(robocin_player librcsc)
add_dependencies(robocin_trainer librcsc)

target_link_libraries(player_chain_action ${RCSC_LINK_LIBS})
target_link_libraries(robocin_coach ${RCSC_LINK_LIBS})
target_link_libraries(robocin_player ${RCSC_LINK_LIBS} player_chain_action ${PYTHON_LIBRARIES})
target_link_libraries(robocin_trainer ${RCSC_LINK_LIBS})
set_property(TARGET robocin_player PROPERTY CXX_STANDARD 11)

set_target_properties(robocin_coach PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SOURCE_DIR})
set_target_properties(robocin_player PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SOURCE_DIR})
set_target_properties(robocin_trainer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SOURCE_DIR})