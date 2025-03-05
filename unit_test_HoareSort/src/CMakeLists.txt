target_sources(hoare_sort_lib
    PRIVATE
        hoare_sort.cpp
    PUBLIC
        hoare_sort.hpp
)


target_include_directories(hoare_sort_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
