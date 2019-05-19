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

//-------------TELA DE AJUSTES---------------------

void DesenhaTelaAjustes(CursorBola &cursor, bool &som)
{
    ALLEGRO_BITMAP *imagem = al_load_bitmap("imagens/tela_ajustes/fundo/tela_ajustes.png");

    ALLEGRO_BITMAP *botao_som_ligado = al_load_bitmap("imagens/tela_ajustes/botoes/botao_som_ligado.png");
    ALLEGRO_BITMAP *botao_som_ligado_press = al_load_bitmap("imagens/tela_ajustes/botoes/botao_som_ligado_press.png");
    ALLEGRO_BITMAP *botao_som_desligado = al_load_bitmap("imagens/tela_ajustes/botoes/botao_som_desligado.png");
    ALLEGRO_BITMAP *botao_som_desligado_press = al_load_bitmap("imagens/tela_ajustes/botoes/botao_som_desligado_press.png");
    ALLEGRO_BITMAP *botao_voltar = al_load_bitmap("imagens/tela_ajustes/botoes/botao_voltar.png");
    ALLEGRO_BITMAP *botao_voltar_press = al_load_bitmap("imagens/tela_ajustes/botoes/botao_voltar_press.png");


    al_draw_bitmap(imagem, 0, 0, 0);

    al_draw_bitmap(botao_voltar, 220, 395, 0);

    if (cursor.x > 220 && cursor.x < 420 && cursor.y > 395 && cursor.y < 445)
        al_draw_bitmap(botao_voltar_press, 220, 395, 0);

    if (som)
    {
        al_draw_bitmap(botao_som_ligado, 235, 184, 0);
        if (cursor.x > 235 && cursor.x < 405 && cursor.y > 184 && cursor.y < 224)
            al_draw_bitmap(botao_som_ligado_press, 235, 184, 0);
    }
    else
    {
        al_draw_bitmap(botao_som_desligado, 235, 184, 0);
        if (cursor.x > 235 && cursor.x < 405 && cursor.y > 184 && cursor.y < 224)
            al_draw_bitmap(botao_som_desligado_press, 235, 184, 0);
    }

    al_destroy_bitmap(imagem);
    al_destroy_bitmap(botao_voltar);
    al_destroy_bitmap(botao_voltar_press);
    al_destroy_bitmap(botao_som_ligado);
    al_destroy_bitmap(botao_som_ligado_press);
    al_destroy_bitmap(botao_som_desligado);
    al_destroy_bitmap(botao_som_desligado_press);

}
