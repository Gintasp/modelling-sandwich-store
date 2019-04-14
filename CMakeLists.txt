cmake_minimum_required(VERSION 3.13)
project(Darbas_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Darbas_3 main.c data_structures/stack/stack.h data_structures/stack/stack.c data_structures/queue/queue.h data_structures/queue/queue.c data_structures/queue/p_queue.h store_stack/store_stack.c store_stack/store_stack.h random.h random.c store_queue/store_queue.c store_queue/store_queue.h)