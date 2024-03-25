cmake_minimum_required(VERSION 3.24)
project(Parachute C)

set(CMAKE_C_STANDARD 99)

add_executable(Parachute main.c player.c player.h game.h game.c background.c background.h helico.c helico.h platforme.c platforme.h constante.h menu.c menu.h game2.c game2.h)
target_link_libraries(Parachute -lmingw32 -lallegro-5.0.10-monolith-md-debug)
