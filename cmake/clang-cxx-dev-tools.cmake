# Shameless copy-pasta from http://www.labri.fr/perso/fleury/posts/programming/using-clang-tidy-and-clang-format.html

# Additional targets to perform clang-format/clang-tidy
# Get all project files
#file(GLOB_RECURSE
 # ALL_CXX_SOURCE_FILES
  #*.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI]
 # src/*.cpp src/*.cxx src/*.cc src/*.c include/*/*.hpp
 # )

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND /usr/bin/clang-tidy
    -p .
    ${ALL_CXX_SOURCE_FILES}
    )
  endif()
