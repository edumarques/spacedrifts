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

//-------------VARI�VEIS GLOBAIS-------------------
const int largura_tela = 640;
const int altura_tela = 480;

//-------------------------------------------------

//----------BOLAS-----------
void InitBolas (Bolas bolas[], int tamanho)
{
    for(int i = 0 ; i < tamanho ; i++)
    {
        bolas[i].imagem = al_load_bitmap("imagens/jogo/green.png");

        bolas[i].ID = BOLAS;
        bolas[i].velocidade = (rand() % 10)/10.0 + 0.1; // (rand() % x) + n -> de n at� n+(x-1)
        bolas[i].ativo = false;
    }
}
void DesenhaBolas (Bolas bolas[], int tamanho)
{
    for(int i = 0 ; i < tamanho ; i++)
    {
        if (bolas[i].ativo)
        {
            al_draw_bitmap(bolas[i].imagem, bolas[i].x-10, bolas[i].y-10,0);
        }
    }
}
void LiberaBolas (Bolas bolas[], int tamanho)
{
    for(int i = 0 ; i < tamanho ; i++)
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
void AtualizaBolas (Bolas bolas[], int tamanho, CursorBola &cursor)
{
    for(int i = 0 ; i < tamanho ; i++)
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
void ColisaoBolas (Bolas bolas[], int tamanho, CursorBola &cursor, bool &colidiu, int &diferenca_x, int &diferenca_y, list <Bolas> &capturadas, list <Bolas>::iterator &it, bool &som, ALLEGRO_SAMPLE_INSTANCE* &inst_som_bola)
{
    for (int i = 0; i < tamanho; i++)
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
                        al_stop_sample_instance(inst_som_bola);
                        al_play_sample_instance(inst_som_bola);
                    }

                    colidiu = true;
                    bolas[i].ativo = false;
                    diferenca_x = bolas[i].x;
                    diferenca_y = bolas[i].y;
                }
            }
            if( (sqrt(pow(bolas[i].x - cursor.x, 2) + pow(bolas[i].y - cursor.y, 2)) <= 20) )
            {
                if (som)
                {
                    al_stop_sample_instance(inst_som_bola);
                    al_play_sample_instance(inst_som_bola);
                }

                colidiu = true;
                bolas[i].ativo = false;
                diferenca_x = bolas[i].x;
                diferenca_y = bolas[i].y;
            }
            if (colidiu)
            {

                Bolas bola;

                bola.x = (diferenca_x-cursor.x);
                bola.y = (diferenca_y-cursor.y);
                bola.imagem = al_load_bitmap("imagens/jogo/green.png");
                capturadas.push_back(bola);

                colidiu = false;

            }
        }
    }
}
