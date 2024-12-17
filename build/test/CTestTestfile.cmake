# CMake generated Testfile for 
# Source directory: B:/Dysk/Studia - private/Edge Computing/PNAMSC/test
# Build directory: B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[testTest]=] "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/Debug/testTest_Tests.exe")
  set_tests_properties([=[testTest]=] PROPERTIES  _BACKTRACE_TRIPLES "B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;75;add_test;B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[testTest]=] "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/Release/testTest_Tests.exe")
  set_tests_properties([=[testTest]=] PROPERTIES  _BACKTRACE_TRIPLES "B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;75;add_test;B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[testTest]=] "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/MinSizeRel/testTest_Tests.exe")
  set_tests_properties([=[testTest]=] PROPERTIES  _BACKTRACE_TRIPLES "B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;75;add_test;B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[testTest]=] "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/RelWithDebInfo/testTest_Tests.exe")
  set_tests_properties([=[testTest]=] PROPERTIES  _BACKTRACE_TRIPLES "B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;75;add_test;B:/Dysk/Studia - private/Edge Computing/PNAMSC/test/CMakeLists.txt;0;")
else()
  add_test([=[testTest]=] NOT_AVAILABLE)
endif()
