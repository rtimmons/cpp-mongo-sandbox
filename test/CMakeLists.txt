set (Demo_Test
      "demo.cpp"
)

set (ALL_TEST
      ${Demo_Test}
)


project(${TEST_NAME})
add_executable (${TEST_NAME} main-test.cpp ${ALL_TEST})
target_link_libraries(${TEST_NAME} gtest_main gtest)
target_link_libraries(${TEST_NAME} ${allLibs})
