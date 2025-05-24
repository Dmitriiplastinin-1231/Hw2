target_sources(long_numbers_lib
    PRIVATE
        long_numbers.cpp
    PUBLIC
        long_numbers.hpp
)


target_include_directories(long_numbers_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
