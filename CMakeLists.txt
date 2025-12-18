cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OgreTest")

# Specify the path to OGREConfig.cmake
set(OGRE_DIR "ogre-sdk-v14.4.1-msvc142-x64/Cmake" CACHE PATH "Path to OGRE")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/ogre-sdk-v14.4.1-msvc142-x64/bin")

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

# Add source to this project's executable.
add_executable (OgreTest "main.cpp"  "FirstPersonController.h" "FirstPersonController.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OgreTest PROPERTY CXX_STANDARD 20)
endif()

# this also sets the includes and pulls third party dependencies
target_link_libraries(OgreTest OgreBites)



# TODO: Add tests and install targets if needed.
