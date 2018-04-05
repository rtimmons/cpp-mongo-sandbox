
set(rates_sources
    main.cpp
    rates.h
)
add_executable(rates ${rates_sources})
target_link_libraries(rates PUBLIC Boost::math)

