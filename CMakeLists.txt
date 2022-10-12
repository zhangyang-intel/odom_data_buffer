cmake_minimum_required(VERSION 3.5)
project(cpp_pubsub)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

############################
#build library
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# include_directories("/usr/include/eigen3")
# SET( EIGEN3_INCLUDE_DIR "/usr/include/eigen3" )
add_library(buffer_lib src/buffer.cpp)
#  target_include_directories(buffer_lib PUBLIC include ${EIGEN3_INCLUDE_DIR})
target_link_libraries (buffer_lib Eigen3::Eigen)


############################
#"hello world"_publisher related
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED )
add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
# target_link_libraries(talker buffer_lib)
install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

############################
#"hello world"_subscriber related
add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs nav_msgs)
target_link_libraries(listener buffer_lib)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})