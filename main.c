#include "file_handling.h"
#include "map_handling.h"
#include "game.h"
#include "sdl_game.h"
#include "game_console.h"
#include <conio.h>


int main(int argc,char **argv) {
//    struct LinkedList *rule_list, *map_list;
//    struct FileData *rule_file, *map_file;
//    rule_file = read_file("game.txt");
//    map_file = read_file("map.txt");
//    rule_list = get_file_info(rule_file);
//    struct Board *board;
//    board = create_board(rule_list, map_file);
//    show_board(board);
    //while(!game_play("game-pacman.txt","map-pacman.txt"));
    system("vlc -I dummy --dummy-quiet --fullscreen videos\\intro.mkv vlc://quit\n"
           "a.exe");
    game_launcher(atoi(argv[1]),atoi(argv[2]));
//    int ch;
//    ch = getch ();
//    if (ch == 0 || ch == 224)
//    {
//        switch (getch ())
//        {
//            case 72:
//                /* Code for up arrow handling */
//                break;
//
//            case 80:
//                /* Code for down arrow handling */
//                break;
//
//                /* ... etc ... */
//        }
//    }
//    printf("%d",ch);
    return 0;
}

//#include <stdio.h>
//#include "C:\mingw_dev_lib\include\SDL2\SDL.h"
//
//#define PI  3.14159
//#define SCR_WDT  640
//#define SCR_HGT  480
//
//const int SCR_CEN_X = SCR_WDT / 2;
//const int SCR_CEN_Y = SCR_HGT / 2;
//
//int main(int arcg, char *a[]) {
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
//        return EXIT_FAILURE;
//    }
//    SDL_Init ( SDL_INIT_VIDEO );
//    SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle",       SDL_WINDOWPOS_UNDEFINED,
//                                            SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, SDL_WINDOW_OPENGL );
//    SDL_Delay(200000);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
