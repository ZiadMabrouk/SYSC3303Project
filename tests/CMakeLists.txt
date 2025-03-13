
add_executable(
        unit_tests
        ProjectTest.cpp
)
target_link_libraries(
        unit_tests PRIVATE source Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)