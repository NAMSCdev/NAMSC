message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(Boost)
find_package(Microsoft.GSL)

set(CONANDEPS_LEGACY  boost::boost  Microsoft.GSL::GSL )