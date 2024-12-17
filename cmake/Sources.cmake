file(GLOB_RECURSE EDITOR_SOURCE_FILES
     src/Editor/*.cpp
     src/Editor/*.h
     src/Editor/*.ui)

file(GLOB_RECURSE ENGINE_SOURCE_FILES
     src/Engine/*.cpp
     src/Engine/*.h
     src/Engine/*.ui)

file(GLOB_RECURSE LIBRARY_SOURCE_FILES
     src/pvnlib/*.cpp
     src/pvnlib/*.h
     src/pvnlib/*.ui)

file(GLOB_RECURSE TEST_FILES 
     test/*.cpp)
