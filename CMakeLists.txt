cmake_minimum_required (VERSION 3.8)

project(elfPatch)

aux_source_directory(./src EXE_SRCS)
add_executable(elfPatch ${EXE_SRCS})

aux_source_directory(./test TEST_SRCS)
add_executable(testExe ${TEST_SRCS})
