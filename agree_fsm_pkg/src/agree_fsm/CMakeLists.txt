file(GLOB THIS_APP_SOURCES *.c *.cpp )
file(GLOB THIS_APP_HEADERS *.h)

get_filename_component(THIS_APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "Example application, ${THIS_APP_NAME}, is ready to build")

add_executable(${THIS_APP_NAME} ${THIS_APP_SOURCES} ${THIS_APP_HEADERS})
target_link_libraries(${THIS_APP_NAME} ${catkin_LIBRARIES})

install(TARGETS ${THIS_APP_NAME} DESTINATION ./bin)
