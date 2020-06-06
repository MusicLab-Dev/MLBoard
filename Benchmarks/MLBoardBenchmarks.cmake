project(MLBoardBenchmarks)

set(MLBoardBenchmarksDir ${MLBoardDir}/Benchmarks)

set(MLBoardBenchmarksSources
    ${MLBoardBenchmarksDir}/Main.cpp
    ${MLBoardBenchmarksDir}/bench_Board.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${MLBoardBenchmarksSources})

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    benchmark::benchmark
    MLBoardLib
)