cmake_minimum_required(VERSION 3.16...3.21)
project(GRAiNTIA)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.cc)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(GRAiNTIA GRAiNTIA.cc ${sources} ${headers})
target_link_libraries(GRAiNTIA ${Geant4_LIBRARIES})

set(MAC_SCRIPTS
    init_vis.mac
    vis.mac
    run_center_analysis.mac
    run_side_mooving.mac
    run_depth_analysis.mac
)

foreach(_script ${MAC_SCRIPTS})
    configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()