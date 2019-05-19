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

//-------------VARIÁVEIS GLOBAIS-------------------
const int largura_tela = 640;
const int altura_tela = 480;

//-------------------------------------------------

//-------CURSOR BOLA--------
void InitCursor (CursorBola &cursor)
{
    cursor.imagem = al_load_bitmap("imagens/jogo/yellow.png");

    cursor.ID = JOGADOR;
    cursor.x = largura_tela / 2;
    cursor.y = altura_tela - 20;
    cursor.vidas = 3;
    cursor.pontos = 0;
    cursor.nivel = 1;

}
void DesenhaCursor (CursorBola &cursor)
{
    al_draw_bitmap(cursor.imagem, cursor.x-10, cursor.y-10, ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL);
}
void DesenhaCapturadas (list <Bolas> capturadas, CursorBola &cursor)
{
    list <Bolas>::iterator it = capturadas.begin();
    for(; it != capturadas.end(); it++){
            al_draw_bitmap((*it).imagem, cursor.x+(*it).x-10, cursor.y+(*it).y-10,0);
    }
}
