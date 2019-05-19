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

using namespace std;

const int largura_tela = 640;
const int altura_tela = 480;

//-----------TELA DE RANKING-------------
void DesenhaTelaPreRanking(ALLEGRO_FONT* fonte, bool &digit_ok, CursorBola &cursor)
{
    ALLEGRO_BITMAP *imagem = al_load_bitmap("imagens/tela_pre_ranking/fundo/tela_pre_ranking.png");
    al_draw_bitmap(imagem, 0, 0, 0);
    al_flip_display();

    Player jogador;
    cout << "DIGITE SEU NOME AQUI:" << endl;
    cin >> jogador.nome;

    ofstream saves;
    if(!saves.is_open())
    {  //se saves não estiver aberto,

        saves.open("saves.imd",ios::app);  //cria saves.txt, posiciona o cursor np fim do arquivo

        saves << cursor.pontos;
        saves << endl;
        saves << jogador.nome;
        saves << endl;
    }
    saves.close();
    digit_ok = true;

    al_destroy_bitmap(imagem);
}
