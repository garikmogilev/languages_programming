cmake_minimum_required(VERSION 3.16)
project(LPLab14)

set(CMAKE_CXX_STANDARD 14)

include_directories(generator_graphs)
include_directories(LPLab13)

add_executable(LPLab14
        generator_graphs/generator_graphs.cpp
        generator_graphs/generator_graphs.h
        generator_graphs/graphs.h
        LPLab13/DP.cpp
        LPLab13/DP.h
        LPLab13/Error.cpp
        LPLab13/Error.h
        LPLab13/FST.cpp
        LPLab13/FST.h
        LPLab13/In.cpp
        LPLab13/In.h
        LPLab13/IT.cpp
        LPLab13/IT.h
        LPLab13/Log.cpp
        LPLab13/Log.h
        LPLab13/LP_14.cpp
        LPLab13/LT.cpp
        LPLab13/LT.h
        LPLab13/Out.cpp
        LPLab13/Out.h
        LPLab13/Parm.cpp
        LPLab13/Parm.h
        LPLab13/stdafx.h)
