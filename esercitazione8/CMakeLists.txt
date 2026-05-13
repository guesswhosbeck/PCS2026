cmake_minimum_required(VERSION 3.20)
project(esercitazione4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")



add_executable(main_grafi main_grafi.cpp)

## Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_grafi test_grafi.cpp)
add_test(NAME test_grafi COMMAND test_grafi)


enable_testing()