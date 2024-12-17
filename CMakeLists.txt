cmake_minimum_required(VERSION 3.31)
project(TestOG VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(TestOG main.cpp Button.cpp Button.h ShapesField.cpp ShapesField.h )

add_custom_command(TARGET TestOG POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/fonts
                        $<TARGET_FILE_DIR:TestOG>/fonts
                   VERBATIM)
				   
target_link_libraries(TestOG PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_features(TestOG PRIVATE cxx_std_14)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET TestOG POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:TestOG> $<TARGET_FILE_DIR:TestOG> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS TestOG)