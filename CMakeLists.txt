cmake_minimum_required(VERSION 3.27)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3
        Sequence.h
        ArraySequence.h
        LinkedListSequence.h
        LinkedList.h
        DynamicArray.h
        Common.h
        main.cpp
        menu.h
        Stack.h
        Deque.h
        person.h
        CString.h
        Queue.h
        Person.h
        FunctionHolder.h
        Functions.h
        SegmentedDeque.h
)
add_subdirectory(Google_tests)