add_executable(manager tst_manager.cpp)
target_link_libraries(manager PUBLIC QDmxLib Qt5::Test)
add_test(NAME manager COMMAND manager)

add_executable(artnet tst_artnet.cpp)
target_link_libraries(artnet PUBLIC QDmxLib Qt5::Test)
add_test(NAME artnet COMMAND artnet)
