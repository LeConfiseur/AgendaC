cmake_minimum_required(VERSION 3.24)
project(Agenda C)

set(CMAKE_C_STANDARD 11)

add_executable(Agenda main.c cell.c cell.h list.c list.h timer.h timer.c agenda.h agenda.c)
