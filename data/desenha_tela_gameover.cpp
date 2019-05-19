#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <list>
#include <vector>

#include "objetos.h"

using namespace std;

//-----------TELA DE GAME OVER-------------
void DesenhaGameOver(CursorBola &cursor)
{
    ALLEGRO_BITMAP *imagem = al_load_bitmap("imagens/game_over/fundo/game_over.png");

    ALLEGRO_BITMAP *botao_gravar_press = al_load_bitmap("imagens/game_over/botoes/botao_gravar_press.png");
    ALLEGRO_BITMAP *botao_jogar_press = al_load_bitmap("imagens/game_over/botoes/botao_jogar_press.png");
    ALLEGRO_BITMAP *botao_voltar_press = al_load_bitmap("imagens/game_over/botoes/botao_voltar_press.png");

    al_draw_bitmap(imagem, 0, 0, 0);

    if (cursor.x > 220 && cursor.x < 420 && cursor.y > 242 && cursor.y < 292)
        al_draw_bitmap(botao_gravar_press, 220, 242, 0);
    if (cursor.x > 220 && cursor.x < 420 && cursor.y > 316 && cursor.y < 366)
        al_draw_bitmap(botao_jogar_press, 220, 316, 0);
    if (cursor.x > 220 && cursor.x < 420 && cursor.y > 389 && cursor.y < 439)
        al_draw_bitmap(botao_voltar_press, 220, 389, 0);

    al_destroy_bitmap(imagem);
    al_destroy_bitmap(botao_gravar_press);
    al_destroy_bitmap(botao_jogar_press);
    al_destroy_bitmap(botao_voltar_press);

}

