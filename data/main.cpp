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

//-------------VARIÁVEIS GLOBAIS-------------------
const int largura_tela = 640;
const int altura_tela = 480;
const int FPS = 60;
const int NUM_BOLAS = 20;
const int NUM_INIMIGOS = 15;
const int NUM_BONUS = 10;
const int NUM_PLANOS = 3;
const int NUM_ESTRELAS = 100;


//-------------------------------------------------


//-----PROTÓTIPOS DAS FUNÇÕES E PROCEDIMENTOS------
void InitCursor (CursorBola &cursor);
void DesenhaCursor (CursorBola &cursor);

void DesenhaCapturadas (list <Bolas> capturadas, CursorBola &cursor);

void InitBolas (Bolas bolas[], int tamanho);
void DesenhaBolas (Bolas bolas[], int tamanho);
void LiberaBolas (Bolas bolas[], int tamanho);
void AtualizaBolas (Bolas bolas[], int tamanho, CursorBola &cursor);
void ColisaoBolas (Bolas bolas[], int tamanho, CursorBola &cursor, bool &colidiu, int &diferenca_x, int &diferenca_y, list <Bolas> &capturadas, list <Bolas>::iterator &it, bool &som, ALLEGRO_SAMPLE_INSTANCE* &inst_som_bola);

void InitInimigos (vector <Bolas> &bolas, int tamanho);
void DesenhaInimigos (vector <Bolas> &bolas, int tamanho);
void LiberaInimigos (vector <Bolas> &bolas, int tamanho);
void AtualizaInimigos (vector <Bolas> &bolas, int tamanho);
void ColisaoInimigos (vector <Bolas> &bolas, int tamanho, CursorBola &cursor, list <Bolas> &capturadas, list <Bolas>::iterator &it, bool &som, ALLEGRO_SAMPLE_INSTANCE* &inst_som_inimigo);

void InitBonus (Bolas bolas[], int tamanho);
void DesenhaBonus (Bolas bolas[], int tamanho);
void LiberaBonus (Bolas bolas[], int tamanho);
void AtualizaBonus (Bolas bolas[], int tamanho);
void ColisaoBonus (Bolas bolas[], int tamanho, CursorBola &cursor, list <Bolas> &capturadas, list <Bolas>::iterator &it, vector <Bolas> &inimigos, bool &som, ALLEGRO_SAMPLE_INSTANCE* &inst_som_bonus);

void InitBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas);
void AtualizaBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas);
void DesenhaBackground (Estrelas estrelas[][NUM_ESTRELAS], int num_planos, int num_estrelas);

void DesenhaTelaInicial(CursorBola &cursor);
void DesenhaTelaAjustes(CursorBola &cursor, bool &som);
void DesenhaGameOver(CursorBola &cursor);


void DesenhaTelaPreRanking(ALLEGRO_FONT* fonte, bool &digit_ok, CursorBola &cursor);
void DesenhaTelaRanking(CursorBola &cursor, vector <Player> &jogadores, ALLEGRO_FONT *font1);


//--------------------FUNÇÃO PRINCIPAL--------------------------



int main()
{
//-------------VARIÁVEIS DO JOGO-------------------
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font1 = NULL;
    bool fim = false;
    bool desenha = true;
    bool game_over = false;
    bool tela_inicial = true;
    bool tela_ajustes = false;
    bool tela_pre_ranking = false;
    bool tela_ranking = false;
    bool colidiu = false;
    bool som = true;
    int diferenca_x = 0;
    int diferenca_y = 0;

    list <Bolas> capturadas;
    list <Bolas>::iterator it = capturadas.begin();

    vector <Player> jogadores;

    bool digit_ok = false;



//-------------------------------------------------


//-------------INICIALIZAÇÃO DE OBJETOS------------------------
    CursorBola cursor;

    Bolas bolas[NUM_BOLAS];
    vector <Bolas> inimigos(NUM_INIMIGOS);
    Bolas bonus[NUM_BONUS];
    Estrelas estrelas[NUM_PLANOS][NUM_ESTRELAS];


//-------------------------------------------------------------


//-------------INICIALIZAÇÃO DA ALLEGRO E DO DISPLAY-----------
    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init())
    {
        al_show_native_message_box(NULL,"AVISO!","ERRO","ALLEGRO NÃO PÔDE SER INICIALIZADA!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    display = al_create_display(largura_tela,altura_tela);

    if (!display)
    {
        al_show_native_message_box(NULL,"AVISO!","ERRO","O DISPLAY NÃO PÔDE SER CRIADO!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

//-------------------------------------------------------------


//-------------INICIALIZAÇÃO DE ADDONS E INSTALAÇÕES-----------
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);
    al_init_image_addon();


//-------------------------------------------------------------


//-------------CRIAÇÃO DA FILA E DEMAIS DISPOSITIVOS-----------

    al_set_window_title(display, "Space Drifts");
    fila_eventos = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);
    font1 = al_load_font("fontes/Stopd.ttf",20,0);

    al_hide_mouse_cursor(display);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(font1,al_map_rgb(255,255,255),largura_tela/2,altura_tela/2,ALLEGRO_ALIGN_CENTRE, "CARREGANDO...");
    al_draw_text(font1,al_map_rgb(255,255,255),largura_tela/2,altura_tela/2 + 20,ALLEGRO_ALIGN_CENTRE, "POR FAVOR, AGUARDE!");
    al_flip_display();

    ALLEGRO_SAMPLE *som_bola = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_som_bola = NULL;
    som_bola = al_load_sample("audio/som_bola.wav");
    inst_som_bola = al_create_sample_instance(som_bola);
    al_attach_sample_instance_to_mixer(inst_som_bola, al_get_default_mixer());

    ALLEGRO_SAMPLE *som_bonus = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_som_bonus = NULL;
    som_bonus = al_load_sample("audio/som_bonus.wav");
    inst_som_bonus = al_create_sample_instance(som_bonus);
    al_attach_sample_instance_to_mixer(inst_som_bonus, al_get_default_mixer());

    ALLEGRO_SAMPLE *som_inimigo = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_som_inimigo = NULL;
    som_inimigo = al_load_sample("audio/som_inimigo.wav");
    inst_som_inimigo = al_create_sample_instance(som_inimigo);
    al_attach_sample_instance_to_mixer(inst_som_inimigo, al_get_default_mixer());

    ALLEGRO_SAMPLE *som_gameover = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_som_gameover = NULL;
    som_gameover = al_load_sample("audio/som_gameover.ogg");
    inst_som_gameover = al_create_sample_instance(som_gameover);
    al_attach_sample_instance_to_mixer(inst_som_gameover, al_get_default_mixer());

    ALLEGRO_SAMPLE *som_botao = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_som_botao = NULL;
    som_botao = al_load_sample("audio/som_botao.wav");
    inst_som_botao = al_create_sample_instance(som_botao);
    al_attach_sample_instance_to_mixer(inst_som_botao, al_get_default_mixer());
    al_set_sample_instance_gain(inst_som_botao, 0.6);

    ALLEGRO_SAMPLE *trilha_sonora = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_trilha_sonora = NULL;
    trilha_sonora = al_load_sample("audio/trilha_sonora.ogg");
    inst_trilha_sonora = al_create_sample_instance(trilha_sonora);
    al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer());
    al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_trilha_sonora, 0.6);

    ALLEGRO_SAMPLE *gameplay = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_gameplay = NULL;
    gameplay = al_load_sample("audio/gameplay.ogg");
    inst_gameplay = al_create_sample_instance(gameplay);
    al_attach_sample_instance_to_mixer(inst_gameplay, al_get_default_mixer());
    al_set_sample_instance_playmode(inst_gameplay, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_gameplay, 0.8);

//-------------------------------------------------------------


//-------------REGISTRO DE SOURCES-----------------------------
    al_register_event_source(fila_eventos,al_get_display_event_source(display));
    al_register_event_source(fila_eventos,al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos,al_get_mouse_event_source());

//-------------------------------------------------------------


//-------------FUNÇÕES INICIAIS--------------------------------
    srand(time(NULL));

    InitCursor(cursor);
    InitBolas(bolas,NUM_BOLAS);
    InitInimigos(inimigos,NUM_INIMIGOS);
    InitBonus(bonus,NUM_BONUS);

    InitBackground(estrelas,NUM_PLANOS,NUM_ESTRELAS);

//-------------------------------------------------------------


//-------------LOOP PRINCIPAL DO JOGO--------------------------

    al_start_timer(timer);


    bool botao_continue_ativo = false;

    while (!fim)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos,&ev);

    //--------------EVENTOS E LÓGICA DO JOGO-------------------
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            fim = true;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            cursor.x = ev.mouse.x;
            cursor.y = ev.mouse.y;
        }

        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {

            if (tela_inicial)
            {
                if (cursor.x > 245 && cursor.x < 395 && cursor.y > 300 && cursor.y < 350)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_inicial = false;
                    tela_pre_ranking = false;
                }


                if (cursor.x > 432 && cursor.x < 582 && cursor.y > 343 && cursor.y < 393)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_inicial = false;
                    tela_ranking = true;
                }

                if (cursor.x > 58 && cursor.x < 208 && cursor.y > 343 && cursor.y < 393)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_inicial = false;
                    tela_ajustes = true;
                }

                if (cursor.x > 245 && cursor.x < 395 && cursor.y > 387 && cursor.y < 437)
                {
                    fim = true;
                }
            }

            if (tela_ajustes)
            {
                if (cursor.x > 235 && cursor.x < 405 && cursor.y > 184 && cursor.y < 224)
                {
                    som = !som;
                }


                if (cursor.x > 220 && cursor.x < 420 && cursor.y > 395 && cursor.y < 445)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_inicial = true;
                    tela_ajustes = false;
                }

            }

            if (tela_ranking)
            {
                digit_ok = false;
                if (cursor.x > 220 && cursor.x < 420 && cursor.y > 395 && cursor.y < 445)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_ranking = false;
                    tela_inicial = true;
                }
            }

            if (game_over && !tela_inicial && !tela_ajustes && !tela_ranking)
            {
                if (cursor.x > 220 && cursor.x < 420 && cursor.y > 242 && cursor.y < 292)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_pre_ranking = true;
                }

                if (cursor.x > 220 && cursor.x < 420 && cursor.y > 316 && cursor.y < 366)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    botao_continue_ativo = true;
                }
                if (cursor.x > 220 && cursor.x < 420 && cursor.y > 389 && cursor.y < 439)
                {
                    if (som) al_play_sample_instance(inst_som_botao);
                    tela_inicial = true;
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            desenha = true;

            if (tela_inicial)
            {
                al_show_mouse_cursor(display);

                if (som)
                {
                    al_play_sample_instance(inst_gameplay);
                }
                else
                {
                    al_stop_sample_instance(inst_gameplay);
                }
            }
            if (tela_ajustes)
            {
                if (som)
                {
                    al_play_sample_instance(inst_gameplay);
                }
                else
                {
                    al_stop_sample_instance(inst_gameplay);
                }
            }
            if (tela_pre_ranking)
            {
                if (digit_ok)
                {
                    tela_ranking = true;
                }
            }
            if (!game_over && !tela_inicial && !tela_ajustes && !tela_ranking && !tela_pre_ranking)
            {
                if (som)
                {
                    al_stop_sample_instance(inst_gameplay);
                    al_play_sample_instance(inst_trilha_sonora);
                }

                botao_continue_ativo = false;

                AtualizaBackground(estrelas,NUM_PLANOS,NUM_ESTRELAS);

                LiberaBolas (bolas,NUM_BOLAS);
                LiberaInimigos (inimigos,NUM_INIMIGOS);
                LiberaBonus (bonus,NUM_BONUS);

                AtualizaBolas (bolas, NUM_BOLAS, cursor);
                AtualizaInimigos (inimigos,NUM_INIMIGOS);
                AtualizaBonus (bonus,NUM_BONUS);

                ColisaoBolas (bolas, NUM_BOLAS, cursor, colidiu, diferenca_x, diferenca_y, capturadas, it, som, inst_som_bola);
                ColisaoInimigos (inimigos, NUM_INIMIGOS, cursor, capturadas, it, som, inst_som_inimigo);
                ColisaoBonus (bonus,NUM_BONUS,cursor, capturadas, it, inimigos, som, inst_som_bonus);


                if(cursor.vidas <= 0)
                {
                    game_over = true;
                    if (som)
                    {
                        al_play_sample_instance(inst_som_gameover);
                    }
                }

            }
            else if (game_over && !tela_inicial && !tela_ajustes && !tela_ranking && !tela_pre_ranking)
            {
                if (som)
                {
                    al_stop_sample_instance(inst_som_inimigo);
                    al_stop_sample_instance(inst_trilha_sonora);
                }

                if (botao_continue_ativo)
                {
                    InitCursor(cursor);
                    InitBolas(bolas,NUM_BOLAS);
                    InitInimigos(inimigos,NUM_INIMIGOS);
                    InitBonus(bonus,NUM_BONUS);

                    InitBackground(estrelas,NUM_PLANOS,NUM_ESTRELAS);

                    game_over = false;
                }

            }
        }


    //--------------DESENHO------------------------------------
        if (desenha && al_is_event_queue_empty(fila_eventos))
        {
            desenha = false;

            if (tela_inicial)
            {
                DesenhaTelaInicial(cursor);
            }
            else if (tela_ajustes)
            {
                DesenhaTelaAjustes(cursor, som);
            }
            else if (tela_ranking)
            {
                DesenhaTelaRanking(cursor, jogadores, font1);
            }
            else if (tela_pre_ranking)
            {
                DesenhaTelaPreRanking(font1, digit_ok, cursor);
            }
            else if (!game_over && !tela_inicial && !tela_ajustes && !tela_ranking)
            {
                al_hide_mouse_cursor(display);

                DesenhaBackground(estrelas,NUM_PLANOS,NUM_ESTRELAS);

                DesenhaCursor(cursor);
                DesenhaBolas(bolas,NUM_BOLAS);
                DesenhaInimigos(inimigos,NUM_INIMIGOS);
                DesenhaBonus(bonus,NUM_BONUS);
                DesenhaCapturadas(capturadas,cursor);

                al_draw_textf(font1, al_map_rgb(255,255,255), largura_tela - 10, 10, ALLEGRO_ALIGN_RIGHT, "PONTOS: %d", cursor.pontos);
                al_draw_textf(font1, al_map_rgb(255,255,255), largura_tela - 10, 50, ALLEGRO_ALIGN_RIGHT, "NIVEL %d", cursor.nivel);
                al_draw_textf(font1, al_map_rgb(255,255,255), largura_tela - 10, 80, ALLEGRO_ALIGN_RIGHT, "VIDAS: %d", cursor.vidas);

            }
            else if (game_over && !tela_inicial && !tela_ajustes && !tela_ranking)
            {
                al_show_mouse_cursor(display);
                DesenhaGameOver(cursor);
                al_draw_textf(font1, al_map_rgb(255,255,255), largura_tela/2, altura_tela/2 - 50, ALLEGRO_ALIGN_CENTRE, "PONTOS: %d", cursor.pontos);

            }


            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

//-------------------------------------------------------------


//-------------FINALIZAÇÕES DO JOGO----------------------------
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
    al_destroy_timer(timer);
    al_destroy_font(font1);

    al_destroy_sample(trilha_sonora);
    al_destroy_sample_instance(inst_trilha_sonora);
    al_destroy_sample(gameplay);
    al_destroy_sample_instance(inst_gameplay);
    al_destroy_sample(som_botao);
    al_destroy_sample_instance(inst_som_botao);
    al_destroy_sample(som_gameover);
    al_destroy_sample_instance(inst_som_gameover);
    al_destroy_sample(som_bola);
    al_destroy_sample_instance(inst_som_bola);
    al_destroy_sample(som_bonus);
    al_destroy_sample_instance(inst_som_bonus);
    al_destroy_sample(som_inimigo);
    al_destroy_sample_instance(inst_som_inimigo);




return 0;
}
