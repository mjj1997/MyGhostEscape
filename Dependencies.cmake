include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(MyGhostEscape_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  find_package(SDL3 CONFIG REQUIRED)
  find_package(SDL3_image CONFIG REQUIRED)

  list(APPEND CMAKE_PREFIX_PATH "G:/src/SDL3_mixer")
  find_package(SDL3_mixer CONFIG REQUIRED)

  find_package(SDL3_ttf CONFIG REQUIRED)
  find_package(glm CONFIG REQUIRED)

endfunction()
