project(MLBoard)

get_filename_component(MLBoardDir ${CMAKE_CURRENT_LIST_FILE} PATH)

include(${MLBoardDir}/MLBoard/MLBoardLib.cmake)
include(${MLBoardDir}/MLBoardApp/MLBoardApp.cmake)

if (${ML_TESTS})
    include(${MLBoardDir}/Tests/MLBoardTests.cmake)
endif ()

if (${ML_BENCHMARKS})
    include(${MLBoardDir}/Benchmarks/MLBoardBenchmarks.cmake)
endif ()