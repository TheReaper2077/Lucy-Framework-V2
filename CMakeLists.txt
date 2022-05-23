cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE TARGET_SRC "src/*.cpp")

include_directories(C:/Users/krishnadev/vcpkg/installed/x64-windows/include src include)
	if (MSVC_VERSION GREATER_EQUAL "1900")
		include(CheckCXXCompilerFlag)
		CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
		if (_cpp_latest_flag_supported)
		add_compile_options("/std:c++20")
	endif()
endif()

add_executable(main ${TARGET_SRC})
target_compile_features(main PUBLIC cxx_std_20)

find_package(glad CONFIG REQUIRED)
target_link_libraries(main PRIVATE glad::glad)

find_package(implot CONFIG REQUIRED)
target_link_libraries(main PRIVATE implot::implot)

find_path(STB_INCLUDE_DIRS "stb.h")
target_include_directories(main PRIVATE ${STB_INCLUDE_DIRS})

find_package(imgui CONFIG REQUIRED)
target_link_libraries(main PRIVATE imgui::imgui)

find_package(imguizmo CONFIG REQUIRED)
target_link_libraries(main PRIVATE imguizmo::imguizmo)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(main PRIVATE EnTT::EnTT)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(main PRIVATE assimp::assimp)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(main PRIVATE yaml-cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
