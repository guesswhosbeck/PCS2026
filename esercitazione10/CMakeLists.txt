cmake_minimum_required(VERSION 3.20)
project(esercitazione4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")



add_executable(main_gradiente main_gradiente.cpp)
add_executable(test_grad_con test_grad_con.cpp)
add_test(NAME test_grad_con COMMAND test_grad_con)

enable_testing()

