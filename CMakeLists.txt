cmake_minimum_required(VERSION 3.0)
SET(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_VERBOSE_MAKEFILE TRUE)

ADD_EXECUTABLE(texas
	       main.cpp
	       read_input.cpp
	       rank_collection.cpp
	       check_cases.cpp
	       deck_operations.cpp
	       compare_hands.cpp
	       rank_royal_flush.cpp
	       rank_straight_flush.cpp
	       rank_straight.cpp
	       rank_triplet.cpp
	       rank_pair.cpp
	       rank_high_card.cpp
	       rank_flush.cpp
	       )


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
