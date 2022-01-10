cmake_minimum_required(VERSION 3.21)
project(ekzamen)

set(CMAKE_CXX_STANDARD 14)

add_executable(ekzamen safequeue.cpp unique_ptr.cpp unique_lock.cpp lock_guard.cpp safestack.cpp "scoped_ptr.cpp" shared_ptr.cpp optional.cpp stack_lock_free.cpp parallel_sort.cpp find_2_elements.cpp merge_2_arr.cpp string.cpp any.cpp vector.cpp)
