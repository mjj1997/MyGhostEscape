include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


include(CheckCXXSourceCompiles)


macro(MyGhostEscape_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    # Check if UndefinedBehaviorSanitizer works at link time
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if (NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      # Check if AddressSanitizer works at link time
      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(MyGhostEscape_setup_options)
  option(MyGhostEscape_ENABLE_HARDENING "Enable hardening" ON)
  option(MyGhostEscape_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    MyGhostEscape_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    MyGhostEscape_ENABLE_HARDENING
    OFF)

  MyGhostEscape_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR MyGhostEscape_PACKAGING_MAINTAINER_MODE)
    option(MyGhostEscape_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(MyGhostEscape_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(MyGhostEscape_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(MyGhostEscape_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(MyGhostEscape_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(MyGhostEscape_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(MyGhostEscape_ENABLE_PCH "Enable precompiled headers" OFF)
    option(MyGhostEscape_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(MyGhostEscape_ENABLE_IPO "Enable IPO/LTO" ON)
    option(MyGhostEscape_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(MyGhostEscape_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(MyGhostEscape_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(MyGhostEscape_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(MyGhostEscape_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(MyGhostEscape_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(MyGhostEscape_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(MyGhostEscape_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(MyGhostEscape_ENABLE_PCH "Enable precompiled headers" OFF)
    option(MyGhostEscape_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      MyGhostEscape_ENABLE_IPO
      MyGhostEscape_WARNINGS_AS_ERRORS
      MyGhostEscape_ENABLE_USER_LINKER
      MyGhostEscape_ENABLE_SANITIZER_ADDRESS
      MyGhostEscape_ENABLE_SANITIZER_LEAK
      MyGhostEscape_ENABLE_SANITIZER_UNDEFINED
      MyGhostEscape_ENABLE_SANITIZER_THREAD
      MyGhostEscape_ENABLE_SANITIZER_MEMORY
      MyGhostEscape_ENABLE_UNITY_BUILD
      MyGhostEscape_ENABLE_CLANG_TIDY
      MyGhostEscape_ENABLE_CPPCHECK
      MyGhostEscape_ENABLE_COVERAGE
      MyGhostEscape_ENABLE_PCH
      MyGhostEscape_ENABLE_CACHE)
  endif()

  MyGhostEscape_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (MyGhostEscape_ENABLE_SANITIZER_ADDRESS OR MyGhostEscape_ENABLE_SANITIZER_THREAD OR MyGhostEscape_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(MyGhostEscape_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(MyGhostEscape_global_options)
  if(MyGhostEscape_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    MyGhostEscape_enable_ipo()
  endif()

  MyGhostEscape_supports_sanitizers()

  if(MyGhostEscape_ENABLE_HARDENING AND MyGhostEscape_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MyGhostEscape_ENABLE_SANITIZER_UNDEFINED
       OR MyGhostEscape_ENABLE_SANITIZER_ADDRESS
       OR MyGhostEscape_ENABLE_SANITIZER_THREAD
       OR MyGhostEscape_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${MyGhostEscape_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${MyGhostEscape_ENABLE_SANITIZER_UNDEFINED}")
    MyGhostEscape_enable_hardening(MyGhostEscape_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(MyGhostEscape_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(MyGhostEscape_warnings INTERFACE)
  add_library(MyGhostEscape_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  MyGhostEscape_set_project_warnings(
    MyGhostEscape_warnings
    ${MyGhostEscape_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(MyGhostEscape_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    MyGhostEscape_configure_linker(MyGhostEscape_options)
  endif()

  include(cmake/Sanitizers.cmake)
  MyGhostEscape_enable_sanitizers(
    MyGhostEscape_options
    ${MyGhostEscape_ENABLE_SANITIZER_ADDRESS}
    ${MyGhostEscape_ENABLE_SANITIZER_LEAK}
    ${MyGhostEscape_ENABLE_SANITIZER_UNDEFINED}
    ${MyGhostEscape_ENABLE_SANITIZER_THREAD}
    ${MyGhostEscape_ENABLE_SANITIZER_MEMORY})

  set_target_properties(MyGhostEscape_options PROPERTIES UNITY_BUILD ${MyGhostEscape_ENABLE_UNITY_BUILD})

  if(MyGhostEscape_ENABLE_PCH)
    target_precompile_headers(
      MyGhostEscape_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(MyGhostEscape_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    MyGhostEscape_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(MyGhostEscape_ENABLE_CLANG_TIDY)
    MyGhostEscape_enable_clang_tidy(MyGhostEscape_options ${MyGhostEscape_WARNINGS_AS_ERRORS})
  endif()

  if(MyGhostEscape_ENABLE_CPPCHECK)
    MyGhostEscape_enable_cppcheck(${MyGhostEscape_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(MyGhostEscape_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    MyGhostEscape_enable_coverage(MyGhostEscape_options)
  endif()

  if(MyGhostEscape_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(MyGhostEscape_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(MyGhostEscape_ENABLE_HARDENING AND NOT MyGhostEscape_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MyGhostEscape_ENABLE_SANITIZER_UNDEFINED
       OR MyGhostEscape_ENABLE_SANITIZER_ADDRESS
       OR MyGhostEscape_ENABLE_SANITIZER_THREAD
       OR MyGhostEscape_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    MyGhostEscape_enable_hardening(MyGhostEscape_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
