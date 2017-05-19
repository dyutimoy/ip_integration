cmake_minimum_required(VERSION 2.8.3)
project(actionlib_tutorials)

find_package(catkin REQUIRED COMPONENTS roscpp actionlib actionlib_msgs)
find_package(Boost REQUIRED COMPONENTS system)



add_action_files(
  DIRECTORY action
  FILES Fibonacci.action Averaging.action buoy.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

add_executable(fibonacci_server src/fibonacci_server.cpp)
add_executable(fibonacci_client src/fibonacci_client.cpp)
add_executable(averaging_server src/averaging_server.cpp)
add_executable(averaging_client src/averaging_client.cpp)
add_executable(buoy_detect_client src/buoy_detect_client.cpp)
add_executable(buoy_server src/buoy_server.cpp)
add_executable(buoy_align_client src/buoy_align_client.cpp)
add_executable(buoy_master src/buoy_master.cpp)

add_dependencies(buoy_server ${actionlib_tutorials_EXPORTED_TARGETS})
add_dependencies(buoy_detect_client ${actionlib_tutorials_EXPORTED_TARGETS})
add_dependencies(buoy_align_client ${actionlib_tutorials_EXPORTED_TARGETS})
add_dependencies(fibonacci_client ${actionlib_tutorials_EXPORTED_TARGETS})
add_dependencies(fibonacci_server ${actionlib_tutorials_EXPORTED_TARGETS})
add_dependencies(buoy_master ${actionlib_tutorials_EXPORTED_TARGETS})


catkin_package(
  CATKIN_DEPENDS actionlib_msgs roscpp
  INCLUDE_DIRS include  # TODO include
)
include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} )

target_link_libraries( buoy_server ${catkin_LIBRARIES} )
target_link_libraries(  buoy_detect_client ${catkin_LIBRARIES})
target_link_libraries(  buoy_master ${catkin_LIBRARIES})
target_link_libraries(  buoy_align_client ${catkin_LIBRARIES})
target_link_libraries( fibonacci_client ${catkin_LIBRARIES})
target_link_libraries(fibonacci_server ${catkin_LIBRARIES})
target_link_libraries(averaging_server ${catkin_LIBRARIES})
target_link_libraries(averaging_client ${catkin_LIBRARIES})
