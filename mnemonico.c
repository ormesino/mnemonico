/*Código para o jogo da memória "Mnemônico" feito por Guilherme Cappelli, Júlio Burlamaqui e Pedro Mateus
Trabalho final para a disciplina de Computação I ministrado pela professora doutora Valéria Menezes Bastos
Feito em março de 2022, Universidade Federal do Rio de Janeiro*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#else
    #include <unistd.h>
#endif

//Macros para tamanho
#define TAM_A 900
#define TAM_M 400

//Vetores globais
char animais[TAM_A];
char mensagens_acertou[TAM_M];
char mensagens_errou[TAM_M];    

//Protótipo das funções.
void cabecalho();
void limpa_tela();
void regras();
void historia_do_jogo();
void ordena_cartas(char cartas[]);
void banco_de_dados(char mensagens_acertou[], char mensagens_errou[], char animais[]);
void imprime_animal(char animais[], char animal);
void imprime_mensagem(char mensagens_acertou[], char mensagens_errou[], int mensagem);
int tela_vitoria();
int tela_derrota();
int escolha();

void cabecalho() {
    //Função que imprime o título do jogo
    printf("\n"
    "\t▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬ஜ ۩ ۞ ۩ ஜ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬ \n"
    "\n"
    "\t   ▄▄▄▄███▄▄▄▄   ███▄▄▄▄      ▄████████   ▄▄▄▄███▄▄▄▄    ▄██████▄  ███▄▄▄▄    ▄█   ▄████████  ▄██████▄  \n"
    "\t ▄██▀▀▀███▀▀▀██▄ ███▀▀▀██▄   ███    ███ ▄██▀▀▀███▀▀▀██▄ ███    ███ ███▀▀▀██▄ ███  ███    ███ ███    ███ \n"
    "\t ███   ███   ███ ███   ███   ███    █▀  ███   ███   ███ ███    ███ ███   ███ ███▌ ███    █▀  ███    ███ \n"
    "\t ███   ███   ███ ███   ███  ▄███▄▄▄     ███   ███   ███ ███    ███ ███   ███ ███▌ ███        ███    ███ \n"
    "\t ███   ███   ███ ███   ███ ▀▀███▀▀▀     ███   ███   ███ ███    ███ ███   ███ ███▌ ███        ███    ███ \n"
    "\t ███   ███   ███ ███   ███   ███    █▄  ███   ███   ███ ███    ███ ███   ███ ███  ███    █▄  ███    ███ \n"
    "\t ███   ███   ███ ███   ███   ███    ███ ███   ███   ███ ███    ███ ███   ███ ███  ███    ███ ███    ███ \n"
    "\t  ▀█   ███   █▀   ▀█   █▀    ██████████  ▀█   ███   █▀   ▀██████▀   ▀█   █▀  █▀   ████████▀   ▀██████▀  \n"
    "\n"
    "\t▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬ஜ ۩ ۞ ۩ ஜ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬ \n\n\n");
}

void limpa_tela() { 
    //Função que limpa a tela
    #if defined _WIN32   
        system("cls");
    #endif
    #if defined linux
        system("clear");
    #endif
}

void regras() {
	//Função que imprime as regras e retorna se o usuário quer prosseguir com o jogo
	int selecao, erro = 0;

    while (1) { 
        
        limpa_tela();
        cabecalho();

        if (erro == 1) {
            printf("[ERRO] Digite uma opção válida!\n");
            erro = 0;
        }

        printf("\t\t\t\t\t\t     ┬─┐┌─┐┌─┐┬─┐┌─┐┌─┐\n"
               "\t\t\t\t\t\t     ├┬┘├┤ │ ┬├┬┘├─┤└─┐\n"
               "\t\t\t\t\t\t     ┴└─└─┘└─┘┴└─┴ ┴└─┘\n\n");
        
        printf("\t\t\tQuatro espécies de animais são escolhidas e ocultadas dentre oito cartas,\n"
            "\t\t     estando cada espécie presente em exatamente duas cartas. Estas cartas são então\n"
            "\t\t   apresentadas ao jogador viradas para baixo de forma que o mesmo não identifique onde\n"
            "\t\t     cada animal se encontra. O jogador deve, então, selecionar um número de 1-8 que\n"
            "\t\t  corresponda à carta que deseja tornar, revelando assim o animal contido nela por meio \n"
            "\t\t  de um desenho aliado à legenda. Em seguida, deve escolher outro número de 1-8, sendo \n"
            "\t\teste número diferente do primeiro, para revelar o segundo animal. Ao escolher a segunda\n" 
            "\t      carta, o jogador não pode apertar nada até que o jogo peça para fazê-lo. O objetivo é achar os\n"
            "\t      pares de animais, isto é, os animais de mesma espécie. Caso os animais sejam da mesma espécie,\n"
            "\t\t são libertos e as cartas não poderão ser escolhidas, o jogador deve repetir o processo.\n"
            "\t\tCaso os animais sejam de espécies diferentes, eles retornam às suas respectivas cartas e uma\n"
            "\t      vida é deduzida do montante do jogador, isto posto, poderá escolher mais duas cartas. O jogador\n"
            "\t       tem um total de cinco vidas, dessa forma, podendo perder até quatro vidas sem o jogo encerrar.\n"
            "\t     Ao perder mais uma vez, o jogo acaba e o jogador é derrotado. A vitória surge quando todas as espécies\n"
            "        forem correspondidas aos seus respectivos pares, ou seja, sejam escolhidos simultaneamente em uma rodada apenas.\n\n"
            "\t\t\t\t\t\t Boa sorte, e bom jogo!\n\n");

        printf("\n\n\t\t\t\t\t\t\t\t\t  Pressione Ctrl+C para sair do jogo\n");
            
        printf("Pressione (2) para continuar para a História\n"
            "Pressione (3) para iniciar o Jogo\n");

        if (scanf("%d", &selecao) == 0) {
            while(getchar() != '\n');
            erro = 1;
            continue;
        }

        if (selecao == 2) historia_do_jogo();
        else if (selecao == 3) escolha();
        else erro = 1;
    }
}

void historia_do_jogo() {
	//Função que imprime a história do jogo e retorna se o usuário quer começar a jogar
	int selecao, erro = 0;

    while(1) {

        limpa_tela();
        cabecalho();

        if (erro == 1) {
            printf("[ERRO] Digite uma opção válida!\n");
            erro = 0;
        }

        printf("\t\t\t\t\t\t    ┬ ┬┬┌─┐┌┬┐┌─┐┬─┐┬┌─┐\n"
               "\t\t\t\t\t\t    ├─┤│└─┐ │ │ │├┬┘│├─┤\n"
               "\t\t\t\t\t\t    ┴ ┴┴└─┘ ┴ └─┘┴└─┴┴ ┴\n\n");

        printf("\t\t  O terrível Éon Baxter sequestrou os animais guardiões da floresta e os aprisionou em\n"
                "\t\tgaiolas metálicas estacionárias a fim de sugar-lhes energia vital. Desprotegida, a floresta \n"
                "\t         caiu às trevas, e um reinado da escuridão impera. O verde trepida, as árvores se curvam,\n"
                "\t     as pedras amolecem e a terra torna-se infértil. Com esse poder, Éon almeja expandir sua dominação\n"
                "\t      para outros biomas! Liberte os animais do cárcere achando seus semelhantes: seja o anjo protetor\n"
                "\t       da natureza e ponha fim ao império da vileza antes que seja tarde demais...\n\n\n");

        printf("\n\n\t\t\t\t\t\t\t\t\t  Pressione Ctrl+C para sair do jogo\n");

        printf("Pressione (3) para dar início ao Jogo\n");

        if (scanf("%d", &selecao) == 0) {
            while(getchar() != '\n');
            erro = 1;
            continue;
        }

        if (selecao == 3) escolha();
        else erro = 1;
    }
}

void ordena_cartas(char cartas[]) {
	//Função faz o shuffle de um array
    int i, j, temp;
    char casas[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    srand(time(NULL));
    for (i=0; i < 8; i++){  // Inverte posicoes umas com as outras do vetor casas[8]
        j = (rand() % 7) + 1;
        temp = casas[i];
        casas[i] = casas[j];
        casas[j] = temp;
    }

    for(i = 0; i < 4; i++){  // Seleciona os 4 primeiros indices a partir do zero desse vetor casas[8]
        cartas[i] = casas[i];  // A partir desses 4 ele duplica essas 4 casas para obtermos 8 cartas, com 4 pares de animais
        cartas[i+4] = casas[i];
    }

    for (i=0; i < 8; i++){  // Agora, como já temos o baralho com 8 cartas e 4 animais
        j = (rand() % 7) + 1;  // Podemos embaralhar esse deque novo, para o usuário advinhar as posiçoes dos animais
        temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}

void banco_de_dados(char mensagens_acertou[], char mensagens_errou[], char animais[]) {
	//Função que importa as mensagens que serão apresentadas que estão armazenadas em arquivos .txt externos
    int i;
    char nomearquivo_1[30] = "animais.txt", nomearquivo_2[30] = "mensagens_acertou.txt", nomearquivo_3[30] = "mensagens_errou.txt", c;
    FILE *ponteiro;

    ponteiro = fopen(nomearquivo_1, "r"); //Abre para leitura o arquivo "animais.txt"
    if (ponteiro == NULL){ //Caso não consiga abrir o arquivo
    	printf("Erro ao tentar abrir o arquivo de animais!\n\n");
    	exit(1);
    }
    c = fgetc(ponteiro);
    for (i = 0; c != EOF; i++) { //Laço for até o fim da leitura do arquivo
        animais[i] = c; //Cada posição do animais[] vai receber caractere do arquivo
        c = fgetc(ponteiro); //Pega o próximo caractere
    }
    fclose(ponteiro); //Para ler o próximo arquivo

    // A partir daqui aplica-se o mesmo raciocínio do anterior para diferentes arquivos
    ponteiro = fopen(nomearquivo_2, "r");  
    if (ponteiro == NULL){
    	printf("Erro ao tentar abrir o arquivo de mensagens acertou!\n\n");
    	exit(1);
    }
    c = fgetc(ponteiro);
    for (i = 0; c != EOF; i++) {
        mensagens_acertou[i] = c;
        c = fgetc(ponteiro);
    }
    fclose(ponteiro);

    ponteiro = fopen(nomearquivo_3, "r");  
    if (ponteiro == NULL){
    	printf("Erro ao tentar abrir o arquivo de mensagens errou!\n\n");
    	exit(1);
    }
    c = fgetc(ponteiro);
    for (i = 0; c != EOF; i++) {
        mensagens_errou[i] = c;
        c = fgetc(ponteiro);
    }
    fclose(ponteiro);    
}

void imprime_animal(char animais[], char animal) {
	//Função que imprime os animais 
    int i = 0;
    for (i = 0; animais[i] != animal; i++);
    i++;
    for (; animais[i] != '#'; i++) 
        printf("%c", animais[i]);
    /*Para separar as mensagens, colocamos um caractere que atua de maneira similar ao \0, no 
      qual mandamos o compilador ler até chegar na cerquilha. Essa ideia se repetirá no programa*/
}

void imprime_mensagem(char mensagens_acertou[], char mensagens_errou[], int mensagem) {
	//Função que imprime mensagens de maneira aleatória conforme a necessidade do programa
    int i = 0, j = 0;
    char frases[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    srand(time(NULL));  
    j = (rand() % 10);  //Geração de um número aleatório de 0 a 9

    if (mensagem == 0) {  //Mensagens quando o usuário erra
        printf("Éon Baxter: ");
        for (i = 0; mensagens_errou[i] != frases[j]; i++);  
        i++;
        for (; mensagens_errou[i] != '#'; i++) //Mesma ideia do \0
            printf("%c", mensagens_errou[i]); 

    } else {  //Mensagens de acerto!  
        if(j < 3)  //Mensagens com índice de 0 a 2 são ditas pelos animais resgatados
            printf("Animal Indefeso: "); 
        else  
            printf("Éon Baxter: ");  //Mensagens com índice de 3 a 9 são ditas pelo vilão

        for (i = 0; mensagens_acertou[i] != frases[j]; i++);
        i++;
        for (; mensagens_acertou[i] != '#'; i++) //Mesma ideia do \0
            printf("%c", mensagens_acertou[i]);  
    }
}  

int tela_vitoria() {
	//Função que exibe a tela de vitória, caso o usuário vença. Nela há a possibilidade de rejogar.
    int selecao, erro = 0;

    limpa_tela();

    printf("\t\t                         `oooooooo/            /oooooooo`\n"                        
    "\t\t                    :sss``+++hMMMMNsssss`  -sssNMMMMMMy+``sss:\n"                   
    "\t\t                    .hmMMMhhho .::::::::::   `::::::::::` yhMMMmh.\n"                 
    "\t\t                    mmMMMMMMN..                            mMMMMMMmm\n"                
    "\t\t                    `:NNN/```  `````NNNNNNNNNNNNNNNN`````  ```/NNN:`\n"                
    "\t\t            .......         .+MMMMMMMMMMMMMMMMMMMMMMMMMM+.         .......\n"         
    "\t\t         :/MMMMMMM:-     :/MMMMMMMMNhhhNMMMMNhhhNMMMMMMMM/:     -:MMMMMMM/:\n"       
    "\t\t      :+NMMMMMMMMMd   :+NMMMMMMMMMd   yMMMMy   dMMMMMMMMMN+:   dMMMMMMMMMN+:\n"     
    "\t\t    -omMMNoooooooo/   yMMMMMMMMMMMd   yMMMMy   dMMMMMMMMMMMy   /ooooooooNMMmo-\n"   
    "\t\t    +MMMMNyyyyyyy     yMMMMMMMMMMMd   yMMMMy   dMMMMMMMMMMMy     yyyyyyyNMMMM+\n"   
    "\t\t    +MMMMMMMMMMMMds   yMMMMMMMMMMMd   yMMMMy   dMMMMMMMMMMMy   sdMMMMMMMMMMMM+\n"   
    "\t\t    `...NMMMMMMMMMd   yMMMMMMo.dMMMmmmNMMMMNmmmMMMd.oMMMMMMy   dMMMMMMMMMN...`\n"   
    "\t\t          `mNMMMMMMd.`   mMMMMMM-   ............   -MMMMMMm   `.dMMMMMMNm`\n"        
    "\t\t            :dddddddd+   ydMMMMM+- .dddddddddddd. -+MMMMMdy   +dddddddd:\n"          
    "\t\t                    ./.  `ydMMMMM/:            :/MMMMMdy`  ./.\n"                   
    "\t\t                    ooohM/    .odMMMMmoooooooooooomMMMMdo.    /Mhooo\n"                
    "\t\t                +sMMMMM/      -+++MMMMMMMMMMMMMMMM+++-      /MMMMMs+\n"              
    "\t\t                /hNMMMMh:shhy       ::::::::::::::::       yhhs:hMMMMNh/\n"            
    "\t\t                sMMMMd.+mNMMMmmmmm-                  -mmmmmMMMNm+.dMMMMs\n"            
    "\t\t                sMMMMd`oMMMMMMMMMMNNNNmmmmm``mmmmmNNNNMMMMMMMMMMo`dMMMMs\n"            
    "\t\t                +mmmMMMMMMMMMMNmmmmmmy            ymmmmmmNMMMMMMMMMMmmm+\n"            
    "\t\t                    hhhhhhhhhho                          ohhhhhhhhhh\n"                
    "\t\t                                    -+++`\n"                                        
    "\t\t                                   .ohMMMso\n"                                       
    "\t\t                                    -MMMMMMm\n"                                       
    "\t\t                                    ddMMMMM:-\n"                                       
    "\t\t                                     MMMMM+.\n"                                         
    "\t\t                                     mNMMM+.\n"                                         
    "\t\t                                     -MMMMM/-\n"                                       
    "\t\t                                     .ydMMMMN/-\n"                                     
    "\t\t                                      -omMMMMy\n"                                     
    "\t\t                                        :+NMMms:\n"                                   
    "\t\t                                        mMMMM+\n"                                   
    "\t\t                                        smMMMMMNm-\n"                                 
    "\t\t                                oN-   `+NMMMMMMMMM-  -No\n"                            
    "\t\t                                +m/. -mNMMMMMMMMNm- ./m+\n"                            
    "\t\t                                sh:- :hhhhhhhh: -:hs\n"                              
    "\t\t                                    ss++++++++++++ss\n"                                
    "\t\t                                    `oooooooooooo`'\n\n"
    "\t\t██    ██  ██████   ██████ ███████     ██    ██ ███████ ███    ██  ██████ ███████ ██    ██ ██\n" 
    "\t\t██    ██ ██    ██ ██      ██          ██    ██ ██      ████   ██ ██      ██      ██    ██ ██\n"
    "\t\t██    ██ ██    ██ ██      █████       ██    ██ █████   ██ ██  ██ ██      █████   ██    ██ ██\n"
    "\t\t ██  ██  ██    ██ ██      ██           ██  ██  ██      ██  ██ ██ ██      ██      ██    ██   \n" 
    "\t\t  ████    ██████   ██████ ███████       ████   ███████ ██   ████  ██████ ███████  ██████  ██\n\n\n\n");
    
    sleep(2);
    
    while(1) {

        limpa_tela();

        printf("\t\t\tSem o poder vital dos animais, as máquinas de Éon rufam e estalam, e por fim colapsam, \n"
                "\t\t   seus sistemas exibem falência crítica. Cambaleante e lânguido, Éon desaba na floresta. \n"
                "\t\t  Parabéns! Você completou essa jornada e saiu vitorioso. Foste capaz de libertar os protetores\n"
                "\t\t     da floresta, que lentamente se reestabelece com muita resiliência. As cachoeiras voltam a correr  \n"
                "\t\tao gorjear dos pássaros, enquanto o Sol se ascende aos céus novamente, erguendo a vida com ele.\n\n"

                "Você gostaria participar dessa aventura novamente?\n\n"
                "Pressione (1) para tentar novamente\n"
                "Pressione (2) para sair\n\n");
        
        if (erro == 1) {
            printf("[ERRO] Digite uma opção válida!\n\n");
            erro = 0;
        }
                                                                                                    
        if (scanf("%d", &selecao) == 0) {
            while(getchar() != '\n');
            erro = 1;
            continue;
        }

        if (selecao == 1) return escolha();
        else if (selecao == 2) {
            limpa_tela();
            exit(1);
        }
        else erro = 1;
    }
}

int tela_derrota() {
	//Função que exibe a tela de derrota, de maneira similar a função tela_vitoria()
    int selecao, erro = 0;

    limpa_tela();

    printf("\t\t\t\t\t\t               ...\n"
            "\t\t\t\t\t\t             ;::::;\n"
            "\t\t\t\t\t\t           ;::::; :;\n"
            "\t\t\t\t\t\t         ;:::::'   :;\n"
            "\t\t\t\t\t\t        ;:::::;     ;.\n"
            "\t\t\t\t\t\t       ,:::::'       ;           OOO\n"
            "\t\t\t\t\t\t       ::::::;       ;          OOOOO\n"
            "\t\t\t\t\t\t       ;:::::;       ;         OOOOOOOO\n"
            "\t\t\t\t\t\t      ,;::::::;     ;'         / OOOOOOO\n"
            "\t\t\t\t\t\t    ;:::::::::`. ,,,;.        /  / DOOOOOO\n"
            "\t\t\t\t\t\t  .';:::::::::::::::::;,     /  /     DOOOO\n"
            "\t\t\t\t\t\t ,::::::;::::::;;;;::::;,   /  /        DOOO\n"
            "\t\t\t\t\t\t;`::::::`'::::::;;;::::: ,#/  /          DOOO\n"
            "\t\t\t\t\t\t:`:::::::`;::::::;;::: ;::#  /            DOOO\n"
            "\t\t\t\t\t\t::`:::::::`;:::::::: ;::::# /              DOO\n"
            "\t\t\t\t\t\t`:`:::::::`;:::::: ;::::::#/               DOO\n"
            "\t\t\t\t\t\t :::`:::::::`;; ;:::::::::##                OO\n"
            "\t\t\t\t\t\t ::::`:::::::`;::::::::;:::#                OO\n"
            "\t\t\t\t\t\t `:::::`::::::::::::;'`:;::#                O\n"
            "\t\t\t\t\t\t  `:::::`::::::::;' /  / `:#\n"
            "\t\t\t\t\t\t   ::::::`:::::;'  /  /   `#\n\n\n"
            "\t\t ██▒   █▓ ▒█████   ▄████▄  ▓█████     ███▄ ▄███▓ ▒█████   ██▀███   ██▀███  ▓█████  █    ██\n" 
            "\t\t▓██░   █▒▒██▒  ██▒▒██▀ ▀█  ▓█   ▀    ▓██▒▀█▀ ██▒▒██▒  ██▒▓██ ▒ ██▒▓██ ▒ ██▒▓█   ▀  ██  ▓██▒\n"
            "\t\t ▓██  █▒░▒██░  ██▒▒▓█    ▄ ▒███      ▓██    ▓██░▒██░  ██▒▓██ ░▄█ ▒▓██ ░▄█ ▒▒███   ▓██  ▒██░\n"
            "\t\t  ▒██ █░░▒██   ██░▒▓▓▄ ▄██▒▒▓█  ▄    ▒██    ▒██ ▒██   ██░▒██▀▀█▄  ▒██▀▀█▄  ▒▓█  ▄ ▓▓█  ░██░\n"
            "\t\t   ▒▀█░  ░ ████▓▒░▒ ▓███▀ ░░▒████▒   ▒██▒   ░██▒░ ████▓▒░░██▓ ▒██▒░██▓ ▒██▒░▒████▒▒▒█████▓\n" 
            "\t\t   ░ ▐░  ░ ▒░▒░▒░ ░ ░▒ ▒  ░░░ ▒░ ░   ░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░ ▒▓ ░▒▓░░░ ▒░ ░░▒▓▒ ▒ ▒\n" 
            "\t\t   ░ ░░    ░ ▒ ▒░   ░  ▒    ░ ░  ░   ░  ░      ░  ░ ▒ ▒░   ░▒ ░ ▒░  ░▒ ░ ▒░ ░ ░  ░░░▒░ ░ ░\n" 
            "\t\t     ░░  ░ ░ ░ ▒  ░           ░      ░      ░   ░ ░ ░ ▒    ░░   ░   ░░   ░    ░    ░░░ ░ ░\n" 
            "\t\t      ░      ░ ░  ░ ░         ░  ░          ░       ░ ░     ░        ░        ░  ░   ░     \n\n\n\n");
    sleep(2);
    
    while (1) {
        limpa_tela();

        printf("\t\t\tSentindo cheiro de sangue e estranha sequidão na garganta, você contempla \n"
            "\t\t     os céus pela última vez enquanto mira o Sol, apesar de sentir-se com tanto frio.\n"
            "\t\t  Tu jazes na floresta, e ela é, pois, teu receptáculo. Acostuma-te à lama que te espera.\n"
            "\t\t     Não fostes capaz de libertar os protetores da floresta, que rui a passos largos. \n"
            "\t\tPoderoso, Éon Baxter lança sua investida contra o restante de natureza no mundo, submetendo-a \n"
            "\t\t à obscuridade. A tecnocracia rege sobre o globo.\n\n"
            
            "Você gostaria de tentar mais uma vez e mudar o destino do mundo?\n\n"
            "Pressione (1) para tentar novamente\n"
            "Pressione (2) para desistir\n\n");
        
        if (erro == 1) {
            printf("[ERRO] Digite uma opção válida!\n\n");
            erro = 0;
        }
                                                                                                        
        if (scanf("%d", &selecao) == 0) {
            while(getchar() != '\n');
            erro = 1;
            continue;
        }

        if (selecao == 1) return escolha();
        else if (selecao == 2) {
            limpa_tela();
            exit(1);
        }
        else erro = 1;
    }
}

int escolha() {
	// Função principal que rege o funcionamento do jogo em si, ela própria é composta de várias outras funções
    char cartas[8], layout[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char prim, seg;
    int pos1, pos2, mensagem, acertos, vidas = 5, erro = 0, i;

    ordena_cartas(cartas);

    while (1){
        acertos = 0, mensagem = 0;

        limpa_tela();
        cabecalho();
        
		//Switch que monitora os erros. Significado dos erros na linha 483
        switch(erro) {
            case 1:
                printf("[ERRO] Você não pode escolher a mesma carta, ser ludibrioso!\n"
                        "Perderá 1 vida pela tentativa de me enganar!\n\n");
                vidas--;  //Reduz uma vida
                erro = 0;  //Retorna a variável ao estado inicial     
                break;
            case 2:
                printf("[ERRO] Você não pode escolher uma carta que já libertou.\n"
                        "Perderá 1 vida pela possível tentativa de me enganar...\n\n");
                vidas--;
                erro = 0;  
                break;
            case 3:
                printf("[ERRO] Você não pode escolher uma carta que não está na mesa, membro pernicioso!\n"
                        "Perderá 1 vida pelo insulto.\n\n");
                vidas--;  
                erro = 0;  
                break;
            default:
                break;
        }

        if (vidas < 1) tela_derrota(); //Verificação se o jogador morreu

        printf("\t\t\t\t   .------.       .------.       .------.       .------.\n"    
                "\t\t\t\t   |%c.--. |       |%c.--. |       |%c.--. |       |%c.--. |\n"
                "\t\t\t\t   | :/\\: |       | (\\/) |       | :(): |       | :/\\: |\n"
                "\t\t\t\t   | (__) |       | :\\/: |       | ()() |       | :\\/: |\n" 
                "\t\t\t\t   | '--'%c|       | '--'%c|       | '--'%c|       | '--'%c|\n"  
                "\t\t\t\t   .------.       .------.       .------.       .------.\n\n"   
                "\t\t\t\t   .------.       .------.       .------.       .------.\n"
                "\t\t\t\t   |%c.--. |       |%c.--. |       |%c.--. |       |%c.--. |\n"
                "\t\t\t\t   | :/\\: |       | (\\/) |       | :(): |       | :/\\: |\n"
                "\t\t\t\t   | (__) |       | :\\/: |       | ()() |       | :\\/: |\n"
                "\t\t\t\t   | '--'%c|       | '--'%c|       | '--'%c|       | '--'%c|\n"
                "\t\t\t\t   .------.       .------.       .------.       .------.\n\n\n", layout[0], layout[1], layout[2], layout[3], layout[0], layout[1], layout[2], layout[3], layout[4], layout[5], layout[6], layout[7], layout[4], layout[5], layout[6], layout[7]);
        printf("\t\t\t\t\t\t\t\t\t\t\t   Vidas restantes: %d\n\n"
                "\t\t\t\t\t\t\t\t\t   Pressione Ctrl+C para sair do jogo\n", vidas);

        printf("Escolha a primeira carta: ");
        
        /*Significado dos erros
        Erro 1: Valor designado para carta não pertecem ao intervalo 1-8. Vida é deduzida
        Erro 2: A carta selecionada já foi liberta, você não pode a escolher novamente. Deduz vida!
        Erro 3: Ambas primeira e segunda cartas são a mesma carta. Deduz ponto!*/
        
        //Entrada da primeira carta e blindagem da entrada
        if (scanf("%d", &pos1) == 0) {
            while(getchar() != '\n');
            erro = 3;
            continue;
        }
        if (!(pos1 <= 8 && pos1 > 0)) {
            erro = 3;
            continue;
        }
        while(getchar() != '\n');
        pos1--;
        prim = cartas[pos1];
        imprime_animal(animais, prim); //Impressão do animal de acordo com a entrada
        
        if (layout[pos1] == ' ') { //Verificação de carta já acertada
            erro = 2;
            continue;
        }
        
        //Entrada da segunda carta e blindagem da entrada
        printf("Escolha a segunda carta: ");
        if (scanf("%d", &pos2) == 0) {
            while(getchar() != '\n');
            erro = 3;
            continue;
        }
        if (!(pos2 <= 8 && pos2 > 0)) {
            erro = 3;
            continue;
        }
        while(getchar() != '\n');
        pos2--;
        seg = cartas[pos2];
        imprime_animal(animais, seg); //Impressão do animal de acordo com a entrada

        if (pos1 == pos2) { //Verificação da escolha de mesma carta
            erro = 1;
            continue;
        }

        if (layout[pos2] == ' ') { //Verificação de carta já acertada
            erro = 2;
            continue;
        }

        if (prim == seg) {  //Caso as cartas formem um par:
            layout[pos1] = ' ';  //Tira-se a numeração das cartas, indicando que ela já foram liberadas
            layout[pos2] = ' ';
            mensagem = 1;  //Imprime mensagem = 1: de acerto!
            imprime_mensagem(mensagens_acertou, mensagens_errou, mensagem);  
        } else {  //Caso as cartas não formem um par:
            imprime_mensagem(mensagens_acertou, mensagens_errou, mensagem);
            vidas--;  //Reduz uma vida
        }
        sleep(2);

        for (i = 0; i < 8; i++){  //A cada carta removida, adicione uma pontuação em acertos
            if (layout[i] != ' ') continue;
            else acertos++;
        }

        if (acertos == 8) tela_vitoria();  //Chegado em oito acertos, declara-se vitória
    }
}

int main() {
	setlocale(LC_ALL, "");  //Para importar caracteres do UTF-8, como acentuações.
    int erro = 0, selecao;

    banco_de_dados(mensagens_acertou, mensagens_errou, animais);    //Gera todos os bancos de dados.

    while(1) {  //While infinito!

        limpa_tela();   
        cabecalho();

        if (erro == 1) {
            printf("[ERRO] Digite uma opção válida!\n");
            erro = 0;
        }

        printf("\t\t\t\t\t      Bem vindo(a) ao Jogo da Memória!\n\n\n");
        printf("\n\t\t\t\t\t\t\t\t\t  Pressione Ctrl+C para sair do jogo\n");
        
        printf("Pressione (1) para ler as regras\n"
               "Pressione (2) para prosseguir para a História\n");
        
        if (scanf("%d", &selecao) == 0) {
            while(getchar() != '\n');
            erro = 1;
            continue;
        }

        switch (selecao){
            case 1:
                regras();               
                break; 
            case 2:
                historia_do_jogo();               
                break;
            default:
                erro = 1;
                break;
        }
    }
    return 0;
}