cmake_minimum_required(VERSION 3.6)
project(final)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(server server.cpp SeaBattleMap.cpp SeaBattleMap.h RenderMap.cpp RenderMap.h StateSeaBattle.cpp StateSeaBattle.h MPIConfig.h)

add_executable(client client.cpp SeaBattleMap.cpp SeaBattleMap.h RenderMap.cpp RenderMap.h StateSeaBattle.cpp StateSeaBattle.h MPIConfig.h)

add_executable(main main.cpp SeaBattleMap.cpp SeaBattleMap.h RenderMap.cpp RenderMap.h StateSeaBattle.cpp StateSeaBattle.h MPIConfig.h)


target_link_libraries(server ${MPI_LIBRARIES})
target_link_libraries(client ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(server PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")

  set_target_properties(client PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(server PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")

  set_target_properties(client PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()