cmake_minimum_required (VERSION 3.23)

project (PotatoWars)
set (MY_AUTHORS "Tomer-Mellick_Hod-Vaknin")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME} include/MapVector.h src/MapVector.cpp)

add_subdirectory (include)
add_subdirectory (src)
file(COPY resources DESTINATION .)

include (cmake/Zip.cmake)

# SFML
# =====
set (SFML_LOCATION "C:/SFML/SFML-2.5.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)

include (cmake/SFML.cmake)
# =====