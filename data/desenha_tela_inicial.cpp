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

//-----------TELA INICIAL-------------
void DesenhaTelaInicial(CursorBola &cursor)
{
    ALLEGRO_BITMAP *imagem = al_load_bitmap("imagens/tela_inicial/fundo/tela_inicial.png");

    ALLEGRO_BITMAP *botao_iniciar_press = al_load_bitmap("imagens/tela_inicial/botoes/botao_iniciar_press.png");
    ALLEGRO_BITMAP *botao_ajustes_press = al_load_bitmap("imagens/tela_inicial/botoes/botao_ajustes_press.png");
    ALLEGRO_BITMAP *botao_ranking_press = al_load_bitmap("imagens/tela_inicial/botoes/botao_ranking_press.png");
    ALLEGRO_BITMAP *botao_sair_press = al_load_bitmap("imagens/tela_inicial/botoes/botao_sair_press.png");

    al_draw_bitmap(imagem, 0, 0, 0);

    if (cursor.x > 245 && cursor.x < 395 && cursor.y > 300 && cursor.y < 350)
        al_draw_bitmap(botao_iniciar_press, 245, 300, 0);
    if (cursor.x > 432 && cursor.x < 582 && cursor.y > 343 && cursor.y < 393)
        al_draw_bitmap(botao_ranking_press, 432, 343, 0);
    if (cursor.x > 58 && cursor.x < 208 && cursor.y > 343 && cursor.y < 393)
        al_draw_bitmap(botao_ajustes_press, 58, 343, 0);
    if (cursor.x > 245 && cursor.x < 395 && cursor.y > 387 && cursor.y < 437)
        al_draw_bitmap(botao_sair_press, 245, 387, 0);

    al_destroy_bitmap(imagem);
    al_destroy_bitmap(botao_iniciar_press);
    al_destroy_bitmap(botao_ajustes_press);
    al_destroy_bitmap(botao_ranking_press);
    al_destroy_bitmap(botao_sair_press);

}
