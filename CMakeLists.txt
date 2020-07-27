cmake_minimum_required(VERSION 3.13)
project(FinalProject C)

set(CMAKE_C_STANDARD 99)

add_executable(FinalProject file_handling.c file_handling.h linked_list.h linked_list.c token2.c token2.h game.c game.h map_handling.c map_handling.h main.c board.c board.h artificial_opp.c artificial_opp.h board.c board.h player.c player.h score.c score.h utils.c utils.h blocks.c blocks.h tets_gui.c bullet.c bullet.h heap.c heap.h a_star_search.c a_star_search.h stack.c stack.h graphics.c graphics.h sdl_game.c sdl_game.h game_menu.c game_menu.h object.c object.h target.c target.h game_console.c game_console.h syntax_checking.c syntax_checking.h)
