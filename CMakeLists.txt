cmake_minimum_required(VERSION 3.13)
project(Darbas_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Darbas_3 main.c stack/stack.h stack/stack.c queue/queue.h queue/queue.c queue/p_queue.h)