cmake_minimum_required(VERSION 3.16)
project(cpp_tmp)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)
# eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(KNITRO REQUIRED)

# Optizelle
add_subdirectory("ext/Optizelle")
get_property(jsoncpp_h_dirs GLOBAL PROPERTY pjsoncpp_include_dirs)
get_property(optizel_h_dirs GLOBAL PROPERTY poptizelle_include_dirs)

message("--> OPTIZEL INCLUDE: ${optizel_h_dirs}")
message("--> JSONCPP INCLUDE: ${jsoncpp_h_dirs}")


add_executable(main main.cc)
target_include_directories(main PUBLIC ${optizel_h_dirs} ${jsoncpp_h_dirs})
target_link_libraries (main PUBLIC Eigen3::Eigen optizelle_static)

add_executable(rosenbrock rosenbrock.cc)
target_include_directories(rosenbrock PUBLIC ${optizel_h_dirs} ${jsoncpp_h_dirs})
target_link_libraries (rosenbrock PUBLIC Eigen3::Eigen optizelle_static)

add_executable(simple_inequalities_and_constraints simple_inequalities_and_constraints.cc)
target_include_directories(simple_inequalities_and_constraints PUBLIC ${optizel_h_dirs} ${jsoncpp_h_dirs})
target_link_libraries (simple_inequalities_and_constraints PUBLIC Eigen3::Eigen optizelle_static)

add_executable(optizelle_vs_knitro optizelle_vs_knitro.cc)
target_include_directories(optizelle_vs_knitro PUBLIC ${optizel_h_dirs} ${jsoncpp_h_dirs} ${KNITRO_INCLUDE_DIRS})
target_link_libraries (optizelle_vs_knitro PUBLIC Eigen3::Eigen optizelle_static ${KNITRO_LIBRARIES})