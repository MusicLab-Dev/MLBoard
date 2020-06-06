project(MLBoardApp)

get_filename_component(MLBoardAppDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(MLBoardAppSources
    ${MLBoardAppDir}/Main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${MLBoardAppSources})

target_include_directories(${PROJECT_NAME} PUBLIC ${MLBoardDir})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    MLBoardLib
)
