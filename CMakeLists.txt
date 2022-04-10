cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
project(Visualized-AirResistance VERSION 0.1.0)

include_directories(c:/dev/vcpkg/installed/x64-windows/include)
link_directories(c:/dev/vcpkg/installed/x64-windows/lib)

include(CTest)
enable_testing()

find_package(SDL2 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(Visualized-AirResistance ${SOURCES})

target_include_directories(Visualized-AirResistance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Visualized-AirResistance 
                    sqlite3 
                    SDL2::SDL2 SDL2::SDL2main 
                    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
