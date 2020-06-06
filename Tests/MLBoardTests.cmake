project(MLBoardTests)

set(MLBoardTestsDir ${MLBoardDir}/Tests)

set(MLBoardTestsSources
    ${MLBoardTestsDir}/tests_Board.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${MLBoardTestsSources})

add_test(NAME ${CMAKE_PROJECT_NAME} COMMAND ${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    GTest::GTest GTest::Main
    MLBoardLib
)