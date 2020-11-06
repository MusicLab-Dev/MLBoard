project(MLBoard)

get_filename_component(MLBoardDir ${CMAKE_CURRENT_LIST_FILE} PATH)

add_compile_options(
    -m32
)

include(${MLBoardDir}/MLBoard/MLBoardLib.cmake)
include(${MLBoardDir}/MLBoardApp/MLBoardApp.cmake)

if (${ML_TESTS})
    include(${MLBoardDir}/Tests/MLBoardTests.cmake)
endif ()

if (${ML_BENCHMARKS})
    include(${MLBoardDir}/Benchmarks/MLBoardBenchmarks.cmake)
endif ()