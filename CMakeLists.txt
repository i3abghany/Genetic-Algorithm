cmake_minimum_required(VERSION 3.14)
project(Genetic_Algorithm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/pi/CLionProjects/Genetic-Algorithm/bin/")

add_executable(Genetic_Algorithm main.cpp GeneticAlgorithm.hpp GeneticAlgorithm.hpp)