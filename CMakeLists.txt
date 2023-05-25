cmake_minimum_required(VERSION 3.24)
project(lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 main.c structs.h dialog_mngr.c dialog_mngr.h graph_mngr.c graph_mngr.h ../aux_funcs/aux_funcs.c ../aux_funcs/aux_funcs.h)
