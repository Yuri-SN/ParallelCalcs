cmake_minimum_required(VERSION 3.16)

project(ParallelCalcs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ParallelCalcs main.cpp)

include(GNUInstallDirs)
install(TARGETS ParallelCalcs
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
