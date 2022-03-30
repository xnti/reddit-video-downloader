cmake_minimum_required(VERSION 3.0.0)
project(reddit-video-downloader VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src/libs)
include_directories(src/include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB INCS "src/include/*.h")
file(GLOB LIBS "src/libs/*.hpp")

add_executable(reddit-video-downloader ${SOURCES} ${LIBS} ${INCS})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 21f42cf882d0b7e5ae9e3434574fc47e187728de) # The commit hash for 1.8.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(reddit-video-downloader PRIVATE cpr::cpr)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
