# add new libs/modules here
# add_library (newlib
# )

# add libs names here
set (allLibs
      # "newlib"
)

project(${PROJECT_NAME})
add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${allLibs})

set (allLibs ${allLibs} PARENT_SCOPE)
