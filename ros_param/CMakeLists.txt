cmake_minimum_required(VERSION 3.0.2)
project(ros_param)

find_package(catkin REQUIRED COMPONENTS
  message_generation std_msgs roscpp 
)

add_service_files(FILES SrvTutorial.srv)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  LIBRARIES ros_tutorials_service
  CATKIN_DEPENDS std_msgs roscpp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
###
add_executable(service_server_param src/service_server_param.cpp)
add_dependencies(service_server_param ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_server_param ${catkin_LIBRARIES})

add_executable(service_client_param src/service_client_param.cpp)
add_dependencies(service_client_param ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_client_param ${catkin_LIBRARIES})