project(MLBoardLib)

get_filename_component(MLBoardLibDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(MLBoardLibSources
    ${MLBoardLibDir}/Types.hpp
    ${MLBoardLibDir}/Scheduler.hpp
    ${MLBoardLibDir}/Scheduler.ipp
    ${MLBoardLibDir}/Scheduler.cpp
    ${MLBoardLibDir}/HardwareModule.ipp
    ${MLBoardLibDir}/HardwareModule.cpp
    ${MLBoardLibDir}/NetworkModule.hpp
    ${MLBoardLibDir}/NetworkModule.ipp
    ${MLBoardLibDir}/NetworkModule.cpp
)

add_library(${CMAKE_PROJECT_NAME} ${MLBoardLibSources})

target_include_directories(${PROJECT_NAME} PUBLIC ${MLBoardDir})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    MLCoreLib
    MLProtocolLib
)
