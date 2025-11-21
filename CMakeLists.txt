cmake_minimum_required(VERSION 3.22)

project(c_battleship
    LANGUAGES C CXX Fortran
)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_Fortran_STANDARD 2008)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_Fortran_STANDARD_REQUIRED ON)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_CUDA "Enable CUDA if available" ON)
include(CheckLanguage)

if(ENABLE_CUDA)
  check_language(CUDA)
  if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    set(CMAKE_CUDA_STANDARD 20)
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    message(STATUS "CUDA enabled: ${CMAKE_CUDA_COMPILER}")
    set(USE_CUDA TRUE)
  else()
    message(STATUS "CUDA not found, building without CUDA")
    set(USE_CUDA FALSE)
  endif()
else()
  set(USE_CUDA FALSE)
endif()

# --------------------------
# Source file collection
# --------------------------
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE C_SOURCES       "${SRC_DIR}/*.c")
file(GLOB_RECURSE CXX_SOURCES     "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.cc" "${SRC_DIR}/*.cxx")
file(GLOB_RECURSE FORTRAN_SOURCES "${SRC_DIR}/*.f" "${SRC_DIR}/*.f90" "${SRC_DIR}/*.f95" "${SRC_DIR}/*.F90")

if(USE_CUDA)
  file(GLOB_RECURSE CUDA_SOURCES "${SRC_DIR}/*.cu")
else()
  set(CUDA_SOURCES "")
endif()

# Optional: Go sources
find_program(GO_EXECUTABLE go)
if(GO_EXECUTABLE)
  set(GO_SRC_DIR "${SRC_DIR}/go")
  set(GO_OUTPUT "${CMAKE_BINARY_DIR}/go_mod")

  add_custom_command(
        OUTPUT ${GO_OUTPUT}
        COMMAND ${GO_EXECUTABLE} build -o ${GO_OUTPUT} ${GO_SRC_DIR}
        WORKING_DIRECTORY ${GO_SRC_DIR}
        COMMENT "Building Go module"
        VERBATIM
    )

  add_custom_target(go_build ALL DEPENDS ${GO_OUTPUT})
endif()

# --------------------------
# Create executable
# --------------------------
add_executable(battleship
    ${C_SOURCES}
    ${CXX_SOURCES}
    ${FORTRAN_SOURCES}
    ${CUDA_SOURCES}
)

# Make main executable depend on Go if Go exists
if(TARGET go_build)
  add_dependencies(battleship go_build)
endif()

# --------------------------
# Include directories
# --------------------------
target_include_directories(battleship PRIVATE
    "${SRC_DIR}"
    "${SRC_DIR}/assets"
)

# --------------------------
# CUDA target properties
# --------------------------
if(USE_CUDA)
  set_target_properties(battleship PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
    )

  # Optional: line info for debugging
  target_compile_options(battleship PRIVATE
        $<$<COMPILE_LANGUAGE:CUDA>:--generate-line-info>
    )
endif()
