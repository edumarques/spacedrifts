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

//----------INIMIGOS-----------
void InitInimigos (vector <Bolas> &bolas, int tamanho)
{
    for(unsigned int i = 0 ; i < bolas.size() ; i++)
    {
        bolas[i].imagem = al_load_bitmap("imagens/jogo/pink.png");

        bolas[i].ID = INIMIGO;
        bolas[i].velocidade = rand() % 2 + 0.5; // (rand() % x) + n -> de n até n+(x-1)
        bolas[i].ativo = false;
    }
}
void DesenhaInimigos (vector <Bolas> &bolas, int tamanho)
{
    for(unsigned int i = 0 ; i < bolas.size() ; i++)
    {
        if (bolas[i].ativo)
        {
            al_draw_bitmap(bolas[i].imagem, bolas[i].x-10, bolas[i].y-10,0);
            //al_draw_filled_circle(bolas[i].x,bolas[i].y,10,al_map_rgb(255,0,255));
        }
    }
}
void LiberaInimigos (vector <Bolas> &bolas, int tamanho)
{
    for(unsigned int i = 0 ; i < bolas.size() ; i++)
    {
        if (!bolas[i].ativo)
        {
            if (rand()%500 == 0)
            {
                bolas[i].x = 30 + rand() % (largura_tela - 60);
                bolas[i].y = 0;
                bolas[i].ativo = true;
                break;
            }
        }
    }
}
void AtualizaInimigos (vector <Bolas> &bolas, int tamanho)
{
   for(unsigned int i = 0 ; i < bolas.size() ; i++)
    {
        if (bolas[i].ativo)
        {
            bolas[i].y += bolas[i].velocidade;
            if(i % 2 == 0)  bolas[i].x -= bolas[i].velocidade;
            else  if(i % 3 == 0)  bolas[i].x += bolas[i].velocidade;


            if (bolas[i].y > altura_tela)
            {
                bolas[i].ativo = false;
            }

        }
    }
}
void ColisaoInimigos (vector <Bolas> &bolas, int tamanho, CursorBola &cursor, list <Bolas> &capturadas, list <Bolas>::iterator &it, bool &som, ALLEGRO_SAMPLE_INSTANCE* &inst_som_inimigo)
{
    for (unsigned int i = 0; i < bolas.size(); i++)
    {
        if (bolas[i].ativo)
        {
            it = capturadas.begin();
            for (unsigned int j = 0; j < capturadas.size(); j++, it++)
            {
                if( (sqrt(pow(bolas[i].x - (cursor.x + (*it).x), 2) + pow(bolas[i].y - (cursor.y + (*it).y), 2)) <= 20) )
                {
                    if (som)
                    {
                        al_stop_sample_instance(inst_som_inimigo);
                        al_play_sample_instance(inst_som_inimigo);
                    }

                    bolas[i].ativo = false;
                    cursor.vidas--;
                    capturadas.clear();

                }
            }
            if( (sqrt(pow(bolas[i].x - cursor.x, 2) + pow(bolas[i].y - cursor.y, 2)) <= 20) )
            {
                if (som)
                {
                    al_stop_sample_instance(inst_som_inimigo);
                    al_play_sample_instance(inst_som_inimigo);
                }

                bolas[i].ativo = false;
                cursor.vidas--;
                capturadas.clear();
            }

        }
    }
}

