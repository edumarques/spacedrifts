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

const int NUM_PLANOS = 3;
const int NUM_ESTRELAS = 100;

//--------------BACKGROUND--------------------

void InitBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas)
{
    for(int i = 0; i < num_planos; i++)
    {
        for(int j = 0; j < num_estrelas; j++)
        {
            if (i==0)
            {
                estrelas[i][j].ID = ESTRELA;
                estrelas[i][j].x = 5 + rand() % (largura_tela - 10);
                estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
                estrelas[i][j].velocidade = 1;

            }
            else if (i==1)
            {
                estrelas[i][j].ID = ESTRELA;
                estrelas[i][j].x = 5 + rand() % (largura_tela - 10);
                estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
                estrelas[i][j].velocidade = 1;
            }
            else if (i==2)
            {
                estrelas[i][j].ID = ESTRELA;
                estrelas[i][j].x = 5 + rand() % (largura_tela - 10);
                estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
                estrelas[i][j].velocidade = 1;
            }
        }
    }
}
void AtualizaBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas)
{
    for(int i = 0; i < num_planos; i++)
    {
        for(int j = 0; j < num_estrelas; j++)
        {
            if (i==0)
            {
                estrelas[i][j].y += estrelas[i][j].velocidade;
                if (estrelas[i][j].y > altura_tela) estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
            }
            else if (i==1)
            {
                estrelas[i][j].y += estrelas[i][j].velocidade;
                if (estrelas[i][j].y > altura_tela) estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
            }
            else if (i==2)
            {
                estrelas[i][j].y += estrelas[i][j].velocidade;
                if (estrelas[i][j].y > altura_tela) estrelas[i][j].y = 5 + rand() % (altura_tela - 10);
            }
        }
    }
}
void DesenhaBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas)
{
    for(int i = 0; i < num_planos; i++)
    {
        for(int j = 0; j < num_estrelas; j++)
        {
            if (i==0)
            {
                al_draw_pixel (estrelas[i][j].x,estrelas[i][j].y,al_map_rgb(255,0,0));
            }
            else if (i==1)
            {
                al_draw_pixel (estrelas[i][j].x,estrelas[i][j].y,al_map_rgb(0,0,255));
            }
            else if (i==2)
            {
                al_draw_pixel (estrelas[i][j].x,estrelas[i][j].y,al_map_rgb(255,255,255));
            }
        }
    }
}
