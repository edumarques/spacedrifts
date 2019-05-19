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

#include <fstream>
#include <string>
#include <sstream>

#include "objetos.h"

const int largura_tela = 640;
const int altura_tela = 480;

using namespace std;


int ContaJogadores();
void OrdenaVetor(vector <Player> &jogadores);
void CarregaVetor(vector <Player> &jogadores);
void Recordistas(vector <Player> &jogadores);

//-----------TELA DE RANKING-------------
void DesenhaTelaRanking(CursorBola &cursor, vector <Player> &jogadores, ALLEGRO_FONT *font1)
{
    Recordistas(jogadores);

    ALLEGRO_BITMAP *imagem = al_load_bitmap("imagens/tela_ranking/fundo/tela_ranking.png");
    ALLEGRO_BITMAP *botao_voltar = al_load_bitmap("imagens/tela_ranking/botoes/botao_voltar.png");
    ALLEGRO_BITMAP *botao_voltar_press = al_load_bitmap("imagens/tela_ranking/botoes/botao_voltar_press.png");

    al_draw_bitmap(imagem, 0, 0, 0);

    al_draw_bitmap(botao_voltar, 220, 395, 0);
    if (cursor.x > 220 && cursor.x < 420 && cursor.y > 395 && cursor.y < 445)
        al_draw_bitmap(botao_voltar_press, 220, 395, 0);

    int alt = 320;
    for (unsigned int i = 0; i < 10; i++)
    {
        //cout<<jogadores[i].nome<<", pontuacao de "<<jogadores[i].pontos<<" Pontos!"<<endl;
        al_draw_textf(font1,al_map_rgb(255,255,255),largura_tela/2 - 125,altura_tela - alt,ALLEGRO_ALIGN_CENTRE, jogadores[i].nome.c_str());
        al_draw_textf(font1,al_map_rgb(255,255,255),largura_tela/2 + 125,altura_tela - alt,ALLEGRO_ALIGN_CENTRE, "%d", jogadores[i].pontos);

        alt -= 20;
    }

    al_destroy_bitmap(imagem);
    al_destroy_bitmap(botao_voltar);
    al_destroy_bitmap(botao_voltar_press);
}
