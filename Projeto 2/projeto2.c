/**
 *	      @file: trabalho02.c
 *	    @author: David Fanchic Chatelard 180138863
 *	@disciplina: Algoritmos e Programacao de Computadores
 *	O programa consiste em um labirinto alienígena onde você
 *	possui algumas regras para conseguir escapar e existem
 *	desafios ao longo do labirinto.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void lower(char *string){
	int i;
	for (i = 0; i <= strlen(string); i++){
		string[i] = tolower(string[i]);
	}
}

void mostrar_regras(){
	printf("Você precisa escapar desse labirinto porém existem algumas\n");
	printf("regras para conseguir sair dele. As regras são as seguintes:\n");
	printf("Você vai ter uma quantidade limitada de energia para escapar e\n");
	printf("cada passo que você dá consome uma energia. Você pode conseguir\n");
	printf("mais energias ao completar os desafios que estão no labirinto.\n");
	printf("O labirinto é escuro, então você só consegue ver as paredes mais externas\n");
	printf("e como você tem uma tocha é possível enxergar um quadrado 5x5 em torno\n");
	printf("de onde você está no momento. Ao ganhar os desafios com uma pontuação alta\n");
	printf("você ganha, além das energias, uma tocha que você pode botar no chão e vai\n"); 
	printf("iluminar permanentemente a área onde você deixou ela.\n");
	printf("O labirinto possui somente uma entrada e uma saída.\n");
	printf("ATENÇÃO PARA OS COMANDOS!!!\n");
	printf("Para se mover use as teclas 'w'(cima), 'a'(esquerda), 's'(baixo), 'd'(direita).\n");
	printf("Para voltar para o menu aperte a tecla 'm'.\n");
	printf("Para abrir o seu inventário aperte a tecla 'i'.\n");
	printf("Para sair do programa aperte a tecla 'x'.\n");
}

/*A função abaixo é para colocar a tocha no chão que vai iluminar uma área permanentemente*/
void tocha_parada(int labirinto[30][70], int linha_atual, int coluna_atual, int tam_tocha){
	int linha, coluna;
	for (linha = 0; linha < 30; linha++){
		for (coluna = 0; coluna < 70; coluna++){
			if ((linha >= (linha_atual - tam_tocha)) && (linha <= (linha_atual + tam_tocha)) && (coluna >= (coluna_atual - tam_tocha)) 
				&& (coluna <= (coluna_atual + tam_tocha))){
				if (labirinto[linha][coluna] == 0){
					labirinto[linha][coluna] = 4;
				}
				if (labirinto[linha][coluna] == 1){
					labirinto[linha][coluna] = 5;
				}
				if (labirinto[linha][coluna] == 2){
					labirinto[linha][coluna] = 6;
				}
			}
		}
	}
}

void mostra_labirinto_tocha(int labirinto[30][70], int linha_atual, int coluna_atual){
	const int TOCHA = 2;
	int linha, coluna;
	for (linha = 0; linha < 30; linha++){
		for (coluna = 0; coluna < 70; coluna++){
			if ((labirinto[linha][coluna]) == 4){
					printf(" ");
			}
			else if ((labirinto[linha][coluna]) == 5){
					printf("#");
			}
			else if ((labirinto[linha][coluna]) == 6){
					printf("O");
		    }
			else if (((linha >= (linha_atual - TOCHA)) && (linha <= (linha_atual + TOCHA)) && (coluna >= (coluna_atual - TOCHA)) 
				&& (coluna <= (coluna_atual + TOCHA))) || (linha == 0) || (linha ==29) || (coluna == 0) || (coluna == 69)){
				if ((labirinto[linha][coluna]) == 0){
					printf(" ");
				}
				else if ((labirinto[linha][coluna]) == 1){
					printf("#");
				}
				else if ((labirinto[linha][coluna]) == 2){
					printf("O");
				}
				else if ((labirinto[linha][coluna]) == 3){
					printf("@");
				}
			}
			else{
				printf(" ");
			}
			if (coluna == 69){
				printf("\n");
			}
		}
	}
}

/*A função abaixo verifica se o jogador tentou andar na direção de uma parede.*/
int verifica_parede(int labirinto[30][70], char tecla_digitada, int linha_atual, int coluna_atual){
	if (tecla_digitada == 'w'){
		if ((labirinto[linha_atual - 1][coluna_atual] == 1) || (labirinto[linha_atual - 1][coluna_atual] == 5)){
			printf("Você não pode andar para esta direção!\n");
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}
		else{
			system("clear");
			return 1;
		}
	}
	else if(tecla_digitada == 'a'){
		if ((labirinto[linha_atual][coluna_atual-1] == 1) || (labirinto[linha_atual][coluna_atual-1] == 5) || ((coluna_atual) == 0)){
			printf("Você não pode andar para esta direção!\n");
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}
		else{
			system("clear");
			return 1;
		}
	}
	else if (tecla_digitada == 's'){
		if ((labirinto[linha_atual +1][coluna_atual] == 1) || (labirinto[linha_atual +1][coluna_atual] == 5)){
			printf("Você não pode andar para esta direção!\n");
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}
		else{
			system("clear");
			return 1;
		}
	}
	else if (tecla_digitada == 'd'){
		if ((labirinto[linha_atual][coluna_atual + 1] == 1) || (labirinto[linha_atual][coluna_atual + 1] == 5)){
			printf("Você não pode andar para esta direção!\n");
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}
		else{
			system("clear");
			return 1;
		}
	}
	/*A linha abaixo é para evitar um aviso na hora de compilar o programa*/
	return 0; 
}

/*A função abaixo verifica se o jogador chegou em um desafio.*/
int verifica_desafio(int labirinto[30][70], int linha_atual, int coluna_atual){
	if ((labirinto[linha_atual][coluna_atual] == 2) || (labirinto[linha_atual][coluna_atual] == 6)){
		return 1;
	}
	else{
		return 0;
	}
}

void mostrar_dedos(int mao_jogador[2], int mao_maquina[2]){
	int dedo;
	printf("    SUA MÃO\n");
	for (dedo = 0; dedo < mao_jogador[0]; dedo++){
		if (dedo != (mao_jogador[0] - 1)){
			printf("| ");
		}
		else{
			printf("|");
		}
	}

	printf("\t  ");

	for (dedo = 0; dedo < mao_jogador[1]; dedo++){
		if (dedo != (mao_jogador[1] - 1)){
			printf("| ");
		}
		else{
			printf("|");
		}
	}

	printf("\n\n\n");

	for (dedo = 0; dedo < mao_maquina[0]; dedo++){
		if (dedo != (mao_maquina[0] - 1)){
			printf("| ");
		}
		else{
			printf("|");
		}
	}

	printf("\t  ");

	for (dedo = 0; dedo < mao_maquina[1]; dedo++){
		if (dedo != (mao_maquina[1] - 1)){
			printf("| ");
		}
		else{
			printf("|");
		}
	}
	printf("\n");
	printf("    MÃO DA MÁQUINA\n");
}

/*As duas funções "verifica" são para garantir que a mão que está sendo usada e a mão que está sendo atacada não possuem 0 dedos.*/
int verifica_mao_jogador(int mao_jogador[2], int mao_jogador_jogada){
	if (mao_jogador[mao_jogador_jogada] != 0){
		return 1;
	}
	return 0;
}

int verifica_mao_maquina(int mao_maquina[2], int mao_maquina_jogada){
	if (mao_maquina[mao_maquina_jogada] != 0){
		return 1;
	}
	return 0;
}

int jogo_dos_dedos(int* pontos, int* energia, int* tocha7, int* tocha9, int* tocha13){
	int mao_jogador[2], mao_maquina[2], rodadas = 1, mao_jogador_jogada, mao_maquina_jogada, pontos2 = 0, energia2 = 0, aux_tocha = 0;
	char escolha[5];
	mao_jogador[0] = 1;
	mao_jogador[1] = 1;
	mao_maquina[0] = 1;
	mao_maquina[1] = 1;

	printf("O desafio será o temível jogo dos dedos.\n");
	printf("Para fazer as suas jogadas considere a sua mão\n");
	printf("esquerda como sendo o número 0 e a sua mão\n");
	printf("direita como sendo o número 1 e use essa mesma\n");
	printf("lógica para escolher qual mão da máquina você\n");
	printf("irá atacar.\n");

	/*Verifica se o jogo ja acabou*/
	while (((mao_jogador[0] != 0) || (mao_jogador[1] != 0)) && ((mao_maquina[0] != 0) || (mao_maquina[1] != 0))) {
		mostrar_dedos(mao_jogador, mao_maquina);
		/*As duas linhas abaixo são para fazer com que a verificação de entrada funcione caso sejam digitadas letras em vez de números para essas variáveis.*/
		mao_jogador_jogada = 2;
		mao_maquina_jogada = 2;

		/*A jogada da pessoa começa aqui*/
		/*Verifica se uma das mãos é 0 e se a outra possui um número par de dedos.*/
		if (((mao_jogador[0] == 0) || (mao_jogador[1] == 0)) && (((mao_jogador[0] != 0) && ((mao_jogador[0] % 2) == 0)) || ((mao_jogador[1] != 0) && ((mao_jogador[1] % 2) == 0)))){
			do{
				printf("Você gostaria de dividir os seus dedos de uma mão para a outra?(Sim ou Não) ");
				scanf(" %4[^\n]", escolha);
				lower(escolha);
				while (getchar() != '\n');
				if (!strcmp(escolha, "sim")){
					if (mao_jogador[0] == 0){
						mao_jogador[0] = ((mao_jogador[1])/2);
						mao_jogador[1] = mao_jogador[0];
					}
					else{
						mao_jogador[1] = ((mao_jogador[0])/2);
						mao_jogador[0] = mao_jogador[1];
					}
					mostrar_dedos(mao_jogador, mao_maquina);
					printf("Pressione ENTER para continuar para vez da máquina...");
					while (getchar() != '\n');
					system("clear");
					break;
				}
				else if ((!strcmp(escolha, "nao")) || (!strcmp(escolha, "não"))){
					do{
						printf("Qual mão você quer usar?(esquerda = 0, direita = 1)\n");
						scanf(" %d", &mao_jogador_jogada);
						while (getchar() != '\n');
						if ((mao_jogador_jogada == 0) || (mao_jogador_jogada == 1)){
							if (verifica_mao_jogador(mao_jogador, mao_jogador_jogada)){
								break;
							}
							else{
								printf("Digite uma opção válida!!(a mão que você vai jogar não pode ter 0 dedos)\n");
							}
						}
						else{
							printf("Digite uma opção válida!!(0 ou 1)\n");
						}
					}while(1);
					do{
						printf("Qual mão da máquina você quer atacar?(esquerda = 0, direita = 1)\n");
						scanf(" %d", &mao_maquina_jogada);
						while (getchar() != '\n');
						if ((mao_maquina_jogada == 0) || (mao_maquina_jogada == 1)){
							if (verifica_mao_maquina(mao_maquina, mao_maquina_jogada)){
								break;
							}
							else{
								printf("Digite uma opção válida!!(a mão que você escolheu atacar da máquina não pode ter 0 dedos)\n");
							}
						}
						else{
							printf("Digite uma opção válida!!(0 ou 1)\n");
						}
					}while(1);

					mao_maquina[mao_maquina_jogada] = ((mao_maquina[mao_maquina_jogada] + mao_jogador[mao_jogador_jogada]) % 5);
					mostrar_dedos(mao_jogador, mao_maquina);
					printf("Pressione ENTER para continuar para vez da máquina...");
					while (getchar() != '\n');
					system("clear");
					break;
				}
				else{
					printf("Digite uma opção válida!!(sim ou não)\n");
				}
			} while(1);
		}
		else {
			do{
				printf("Qual mão você quer usar?(esquerda = 0, direita = 1)\n");
				scanf("%d", &mao_jogador_jogada);
				while (getchar() != '\n');
				if ((mao_jogador_jogada == 0) || (mao_jogador_jogada == 1)){
					if (verifica_mao_jogador(mao_jogador, mao_jogador_jogada)){
						break;
					}
					else{
						printf("Digite uma opção válida!!(a mão que você vai jogar não pode ter 0 dedos)\n");
					}
				}
				else{
					printf("Digite uma opção válida!!(0 ou 1)\n");
				}
			}while(1);
			do{
				printf("Qual mão da máquina você quer atacar?(esquerda = 0, direita = 1)\n");
				scanf("%d", &mao_maquina_jogada);
				while (getchar() != '\n');
				if ((mao_maquina_jogada == 0) || (mao_maquina_jogada == 1)){
					if (verifica_mao_maquina(mao_maquina, mao_maquina_jogada)){
						break;
					}
					else{
						printf("Digite uma opção válida!!(a mão que você escolheu atacar da máquina não pode ter 0 dedos)\n");
					}
				}
				else{
					printf("Digite uma opção válida!!(0 ou 1)\n");
				}
			}while(1);

			mao_maquina[mao_maquina_jogada] = ((mao_maquina[mao_maquina_jogada] + mao_jogador[mao_jogador_jogada]) % 5);
			mostrar_dedos(mao_jogador, mao_maquina);
			printf("Pressione ENTER para continuar para vez da máquina...");
			while (getchar() != '\n');
			system("clear");
		} /*A jogada da pessoa vai até aqui*/

		/*O if abaixo verifica se o jogo acabou ou não(no caso se tiver acabado aqui significa que a pessoa ganhou).*/
		if (((mao_jogador[0] != 0) || (mao_jogador[1] != 0)) && ((mao_maquina[0] != 0) || (mao_maquina[1] != 0))){ 
			/*A jogada da máquina começa aqui*/
			printf("A máquina vai jogar agora...\n");
			
			if ((verifica_mao_maquina(mao_maquina, 0)) && (((mao_maquina[0] + mao_jogador[0]) % 5) == 0)){
				mao_jogador[0] = 0;
				printf("A máquina usou a mão esquerda dela para atacar a sua mão esquerda.\n");
			}
			else if ((verifica_mao_maquina(mao_maquina, 0)) && (((mao_maquina[0] + mao_jogador[1]) % 5) == 0)){
				mao_jogador[1] = 0;
				printf("A máquina usou a mão esquerda dela para atacar a sua mão direita.\n");
			}
			else if ((verifica_mao_maquina(mao_maquina, 1)) && (((mao_maquina[1] + mao_jogador[0]) % 5) == 0)){
				mao_jogador[0] = 0;
				printf("A máquina usou a mão direita dela para atacar a sua mão esquerda.\n");
			}
			else if ((verifica_mao_maquina(mao_maquina, 1)) && (((mao_maquina[1] + mao_jogador[1]) % 5) == 0)){
				mao_jogador[1] = 0;
				printf("A máquina usou a mão direita dela para atacar a sua mão direita.\n");
			}

			else if (verifica_mao_maquina(mao_maquina, 0)){
				if ((mao_maquina[1] == 0) && ((mao_maquina[0] % 2) == 0)){
					mao_maquina[1] = (mao_maquina[0] / 2);
					mao_maquina[0] = (mao_maquina[0] / 2);
					printf("A máquina dividiu os dedos.\n");
				}
				else if (verifica_mao_jogador(mao_jogador, 0)){
					mao_jogador[0] = ((mao_jogador[0] + mao_maquina[0]) % 5);
					printf("A máquina usou a mão esquerda dela para atacar a sua mão esquerda.\n");

				}
				else{
					mao_jogador[1] = ((mao_jogador[1] + mao_maquina[0]) % 5);
					printf("A máquina usou a mão esquerda dela para atacar a sua mão direita.\n");

				}
			}
			else if (verifica_mao_maquina(mao_maquina, 1)){
				if ((mao_maquina[0] == 0) && ((mao_maquina[1] % 2) == 0)){
					mao_maquina[0] = (mao_maquina[1] / 2);
					mao_maquina[1] = (mao_maquina[1] / 2);
					printf("A máquina dividiu os dedos.\n");
				}
				else if (verifica_mao_jogador(mao_jogador, 0)){
					mao_jogador[0] = ((mao_jogador[0] + mao_maquina[1]) % 5);
					printf("A máquina usou a mão direita dela para atacar a sua mão esquerda.\n");

				}
				else{
					mao_jogador[1] = ((mao_jogador[1] + mao_maquina[1]) % 5);
					printf("A máquina usou a mão direita dela para atacar a sua mão direita.\n");

				}
			}
			mostrar_dedos(mao_jogador, mao_maquina);
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
		}/*A jogada da máquina vai até aqui*/
		else{
			rodadas++;
			printf("Parabéns você ganhou!!\n");
			printf("Você conseguiu vencer a máquina em %d rodadas.\n", rodadas);
			if (rodadas < 5){
				pontos2 = 30;
				energia2 = 35;
				(*tocha13)++;
				aux_tocha = 13;
			}
			else if (rodadas < 8){
				pontos2 = 25;
				energia2 = 30;
				(*tocha9)++;
				aux_tocha = 9;
			}
			else if (rodadas < 13){
				pontos2 = 20;
				energia2 = 25;
				(*tocha7)++;
				aux_tocha = 7;
			}
			else if (rodadas < 16){
				pontos2 = 15;
				energia2 = 20;
			}
			else if (rodadas < 20){
				pontos2 = 10;
				energia2 = 15;
			}
			else{
				pontos2 = 5;
				energia2 = 5;
			}
			printf("Como você derrotou a máquina em %d rodadas, você irá receber\n", rodadas);
			if (aux_tocha != 0){
				printf("%d energia(s), %d ponto(s)\n", energia2, pontos2);
				printf("e uma tocha que você pode botar no chão e ilumina uma área %dx%d.\n", aux_tocha, aux_tocha); 
			}
			*pontos += pontos2;
			*energia += energia2;
			printf("Pressione ENTER para voltar para o labirinto...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}

		/*O if abaixo verifica se o jogo acabou ou não(no caso se tiver acabado aqui significa que a máquina ganhou).*/
		if (((mao_jogador[0] != 0) || (mao_jogador[1] != 0)) && ((mao_maquina[0] != 0) || (mao_maquina[1] != 0))){
			mostrar_dedos(mao_jogador, mao_maquina);
			printf("Essa foi a %dª rodada.\n", rodadas);
			rodadas++;
			printf("Pressione ENTER para continuar...");
			while (getchar() != '\n');
			system("clear");
		}
		else {
			rodadas++;
			printf("Infelizmente você perdeu.\n");
			printf("A máquina ganhou em %d rodadas.\n", rodadas);
			printf("Como você perdeu o desafio, você não irá ganhar nada.\n");
			printf("Pressione ENTER para voltar para o labirinto...");
			while (getchar() != '\n');
			system("clear");
			return 0;
		}
	}
	/*A linha abaixo é para evitar um aviso na hora de compilar*/
	return 0;
}

void pedra_papel_tesoura(int* pontos, int* energia, int* tocha7, int* tocha9, int* tocha13){
	int vitorias = 0, rodada = 1, jogada_maquina, pontos2 = 0, energia2 = 0, aux_tocha = 0;
	char jogada_usuario[8], *jogada_maquina_escrita;
	printf("O desafio será uma batalha de pedra, papel ou tesoura\n");
	printf("contra a máquina\n");
	while(rodada <= 5){
		printf("%dª rodada:\n", rodada);

		jogada_maquina = rand() % 3;
		if (jogada_maquina == 0){
			jogada_maquina_escrita = "pedra";
		}
		else{
			if (jogada_maquina == 1){
				jogada_maquina_escrita = "papel";
			}
			else{
				jogada_maquina_escrita = "tesoura";
			}
		}
		printf("Você vai jogar pedra, papel ou tesoura? ");
		scanf("%7[^\n]", jogada_usuario);
		while (getchar() != '\n');
		lower(jogada_usuario);
		if (!strcmp(jogada_usuario, "pedra")){
			printf("A máquina jogou %s.\n", jogada_maquina_escrita);
			if (jogada_maquina == 1){
				printf("Você perdeu a  %dª rodada.\n", rodada);
				rodada++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else if (jogada_maquina == 2){
				printf("Você ganhou a %dª rodada.\n", rodada);
				rodada++;
				vitorias++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else{
				printf("A %dª rodada foi um empate, portanto ela será repetida.\n", rodada);
			}
		}else if (!strcmp(jogada_usuario, "papel")){
			printf("A máquina jogou %s.\n", jogada_maquina_escrita);
			if (jogada_maquina == 2){
				printf("Você perdeu a  %dª rodada.\n", rodada);
				rodada++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else if (jogada_maquina == 0){
				printf("Você ganhou a %dª rodada.\n", rodada);
				rodada++;
				vitorias++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else{
				printf("A %dª rodada foi um empate, portanto ela será repetida.\n", rodada);
			}
		}else if (!strcmp(jogada_usuario, "tesoura")){
			printf("A máquina jogou %s.\n", jogada_maquina_escrita);
			if (jogada_maquina == 0){
				printf("Você perdeu a  %dª rodada.\n", rodada);
				rodada++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else if (jogada_maquina == 1){
				printf("Você ganhou a %dª rodada.\n", rodada);
				rodada++;
				vitorias++;
				if (rodada != 6){
					printf("Pressione ENTER para ir para a próxima rodada...");
				}
				else{
					printf("Pressione ENTER para terminar a etapa 2...");
				}
				while (getchar() != '\n');
				system("clear");
			}
			else{
				printf("A %dª rodada foi um empate, portanto ela será repetida.\n", rodada);
			}
		}
		else{
			printf("Digite uma jogada válida!!(pedra, papel ou tesoura)\n");
		}
		jogada_usuario[0] = 0;
	}
	switch (vitorias){
		case 2: pontos2 = 4;energia2 = 10; break;
		case 1: pontos2 = 2;energia2 = 5; break;
		case 0: pontos2 = 0;energia2 = 0; break;
	}
	if (vitorias == 5){
		pontos2 = 10;
		energia2 = 35;
		(*tocha13)++;
		aux_tocha = 13;
	}
	else if (vitorias == 4){
		pontos2 = 8;
		energia2 = 30;
		(*tocha9)++;
		aux_tocha = 9;
	}
	else if (vitorias == 3){
		pontos2 = 6;
		energia2 = 20;
		(*tocha7)++;
		aux_tocha = 7;
	}
	*pontos += pontos2;
	*energia += energia2;
	printf("Você ganhou %d rodadas.\n", vitorias);
	if (aux_tocha != 0){
		printf("Portanto você recebeu %d ponto(s), %d energia(s)\n", pontos2, energia2);
		printf("e uma tocha que você pode botar no chão e ilumina uma área %dx%d.\n", aux_tocha, aux_tocha);
	}
	else{
		printf("Portanto você recebeu %d ponto(s) e %d energia(s).\n", pontos2, energia2);
	}
	printf("Pressione ENTER para voltar para o labirinto...");
	while (getchar() != '\n');
	system("clear");
}

void mostrar_boneco(int erros){
	if (erros == 0){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 1){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 2){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|          |\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 3){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 4){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\\\n");
		printf("|\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 5){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\\\n");
		printf("|          |\n");
		printf("|\n");
		printf("|\n");
	}
	else if (erros == 6){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\\\n");
		printf("|          |\n");
		printf("|          |\n");
		printf("|\n");
	}
	else if (erros == 7){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\\\n");
		printf("|          |\n");
		printf("|         /|\n");
		printf("|\n");
	}
	else if (erros == 8){
		printf(" __________ \n");
		printf("|          |\n");
		printf("|          0\n");
		printf("|         /|\\\n");
		printf("|          |\n");
		printf("|         /|\\\n");
		printf("|\n");
	}
}

void forca(int* pontos, int* energia, int* tocha7, int* tocha9, int* tocha13){
	int escolha_aleatoria, i, cont1, cont2 = 0, cont3, cont4, teste, erros = 0, tentativas = 0, pontos2, energia2, aux_tocha = 0;
	char *palavra_aleatoria, palavra[11], letra_digitada;
	char letras_digitadas[27] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
	printf("O desafio será uma partida de forca.\n");
	printf("Você possui 7 chances de errar, no 8º erro o boneco será enforcado\n");
	printf("e você perderá o desafio.\n");
	printf("Pressione ENTER para ir para começar o desafio da forca...");
	while (getchar() != '\n');
	system("clear");
	escolha_aleatoria = rand() % 10;
	switch (escolha_aleatoria){
		case 0: palavra_aleatoria = "algoritmo"; break;
		case 1: palavra_aleatoria = "labirinto"; break;
		case 2: palavra_aleatoria = "computador"; break;
		case 3: palavra_aleatoria = "ubuntu"; break;		
		case 4: palavra_aleatoria = "windows"; break;
		case 5: palavra_aleatoria = "programa"; break;
		case 6: palavra_aleatoria = "calouro"; break;
		case 7: palavra_aleatoria = "planeta"; break;
		case 8: palavra_aleatoria = "ponteiro"; break;
		case 9: palavra_aleatoria = "professor"; break;
	}
	/*A linha abaixo é para garantir o tamanho do vetor que será completado ao longo da forca.*/
	strcpy(palavra,  palavra_aleatoria);
	/*O laço de repetição abaixo é para preencher o vetor com '_' para ir completando ao longo da forca.*/
	for (i = 0; palavra[i] != '\0'; i++){
		palavra[i] = '_';
	}
	do{
		mostrar_boneco(erros);
		printf("\n\n");
		printf("           %s\n\n", palavra);
		do{
			teste = 0;
			cont1 = 0;
			cont3 = 0;
			cont4 = 0;
			printf("Digite uma letra que vc acha que esta na palavra acima: ");
			scanf(" %c", &letra_digitada);
			while(getchar() != '\n'){
				teste++;
			}
			letra_digitada = tolower(letra_digitada);
			if ((teste != 0)){
				printf("Digite apenas uma letra!!\n");
			}
			else if ((letra_digitada < 'a') || (letra_digitada > 'z')){
				printf("Digite uma letra!!\n");
			}
			else{
				for (i = 0; i < strlen(letras_digitadas); i++){
					if (letras_digitadas[i] != letra_digitada){
						cont1++;
					}
				}
				if (cont1 == strlen(letras_digitadas)){
					letras_digitadas[cont2] = letra_digitada;
					cont2++;
					break;
				}
				else{
					printf("Digite uma letra que você ainda não tentou!!\n");
				}
			}
		} while(1);
		/*O laço de repetição abaixo verifica se a letra digitada está na palavra(primeiro if) e verifica se a palavra foi completada(segundo if).*/
		for (i = 0; i < strlen(palavra_aleatoria); i++){
			if (palavra_aleatoria[i] == letra_digitada){
				palavra[i] = letra_digitada;
				cont3++;
			}
			if (palavra_aleatoria[i] == palavra[i]){
				cont4++;
			}
		}
		if (cont3 == 0){
			printf("A letra que você digitou não está na palavra.\n");
			erros++;
			if (erros != 8){
				printf("O boneco abaixo está sendo enforcado a cada vez que você erra uma letra.\n");
				mostrar_boneco(erros);
			}
		}
		else{
			printf("A letra que você digitou está na palavra.\n");
		}
		if (cont4 == (strlen(palavra_aleatoria))){
			tentativas++;
			system("clear");
			printf("Parabéns você completou a forca!!\n");
			printf("A palavra era: %s.\n", palavra);
			printf("Você conseguiu terminar em %d tentativas.\n", tentativas);
			if (erros == 0){
				pontos2 = 30;
				energia2 = 35;
				(*tocha13)++;
				aux_tocha = 13;
			}
			else if (erros == 1){
				pontos2 = 25;
				energia2 = 30;
				(*tocha9)++;
				aux_tocha = 9;
			}
			else if (erros == 2){
				pontos2 = 20;
				energia2 = 25;
				(*tocha7)++;
				aux_tocha = 7;
			}
			else{
				switch (erros){
					case 3: pontos2 = 15; energia2 = 35; break;
					case 4: pontos2 = 10; energia2 = 25; break;
					case 5: pontos2 = 5; energia2 = 15; break;
					case 6: pontos2 = 3; energia2 = 10; break;
					case 7: pontos2 = 0; energia2 = 5; break;
				}
			}
			*pontos += pontos2;
			*energia += energia2;
			if (aux_tocha != 0){
				printf("Como você teve %d erro(s) você irá receber %d ponto(s), %d energia(s)\n", erros, pontos2, energia2);
				printf("e uma tocha que você pode botar no chão e ilumina uma área %dx%d.\n", aux_tocha, aux_tocha);
			}
			else{
				printf("Como você teve %d erro(s) você irá receber %d ponto(s) e %d energia(s).\n", erros, pontos2, energia2);
			}
			printf("Pressione ENTER para ir para voltar para o labirinto...");
			while (getchar() != '\n');
			system("clear");
			break;
		}
		else{
			if (erros == 8){
				printf("O boneco morreu enforcado e portanto você perdeu.\n");
				printf("Logo, você não irá ganhar recompensas.\n");
				printf("A palavra era: %s.\n", palavra_aleatoria);
				mostrar_boneco(erros);
				printf("Pressione ENTER para ir para voltar para o labirinto...");
				while (getchar() != '\n');
				system("clear");
				break;
			}
			else{
				tentativas++;
				printf("Pressione ENTER para ir para a próxima tentativa...");
				while (getchar() != '\n');
				system("clear");
			}
		}

	} while(1);
}

int main(){
	char tentar_novamente[5];
	char tecla_digitada, opcao_menu, opcao_tocha;
	int pontos, energia, teste, linha_atual, coluna_atual, desafio, tocha7, tocha9, tocha13, linha_aux, coluna_aux;
	/*A constante abaixo serve como molde para atribuir os valores ao labirinto variável a cada vez que a partida começa.*/
	const int LABIRINTO[30][70] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,2,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,0,0,1,2,0,0,0,0,0,0,1,0,2,0,0,0,0,1,1,0,0,0,2,0},
		{1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1},
		{1,0,1,2,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,0,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,0,2,0,0,0,0,0,0,0,0,1,0,2,0,0,1,2,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,1,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,1,0,0,1},
		{1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1},
		{1,0,0,0,0,0,2,1,0,0,0,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1,0,0,0,0,1},
		{1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,1},
		{1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
		{1,0,0,0,0,2,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0,0,1,0,0,2,0,1,0,0,0,2,1,1,0,0,0,0,2,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,2,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,2,1,0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,2,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,2,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1},
		{1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,2,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,2,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,2,1},
		{3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,1,2,0,0,0,0,0,2,0,1,0,0,2,0,1,0,0,0,2,0,0,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	int labirinto[30][70];
	srand(time(NULL));

	do{
		/*Os dois laços de repetição abaixo são para atribuir os valores iniciais para o labirinto a cada vez que uma partida começa.*/
		for (linha_aux = 0; linha_aux < 30; linha_aux++){
			for (coluna_aux = 0; coluna_aux < 70; coluna_aux++){
				labirinto[linha_aux][coluna_aux] = LABIRINTO[linha_aux][coluna_aux];
			}
		}
		/*As 9 linhas abaixo atribuem os valores iniciais para as variáveis a cada partida.*/
		tocha7 = 0;
		tocha9 = 0;
		tocha13 = 0;
		linha_atual = 28;
		coluna_atual = 0;
		pontos = 0;
		energia = 100;
		opcao_menu = ' ';
		opcao_tocha = ' ';

		system("clear");
		printf("Como você foi aprovado no processo seletivo da NASA\n");
		printf("a sua primeira missão é estudar uma nova civilização\n");
		printf("que foi encontrada em Marte. Mas houveram imprevistos e\n");
		printf("a sua nave caiu em um labirinto alienígena!\n");
		mostrar_regras();
		printf("Pressione ENTER para entrar no labirinto...");
		while (getchar() != '\n');
		system("clear");

		do{
			printf("--> Pontos: %d\n", pontos);
			printf("--> Energia: %d\n\n", energia);	
			printf("------------------------------------------------------------------------------------\n\n");
			mostra_labirinto_tocha(labirinto, linha_atual, coluna_atual);
			do{
				printf("Pressione 'm' para voltar ao menu, 'x' para sair do programa,\n");
				printf("'i' para abrir o inventário, 'w' para ir para cima, 'a' para\n");
				printf("ir para a esquerda, 's' para ir para baixo ou 'd' para ir para a direita.\n");
				scanf("%c", &tecla_digitada);
				tecla_digitada = tolower(tecla_digitada);
				teste = 0;
				while (getchar() != '\n'){
					teste++;
				}
				if ((teste != 0) || (((tecla_digitada != 'w') && (tecla_digitada != 'a') && (tecla_digitada != 's') && (tecla_digitada != 'd') && (tecla_digitada != 'x') && tecla_digitada != 'm') && (tecla_digitada != 'i'))){
					printf("Digite somente uma letra que seja válida!!('m' ,'i' ,'x', 'w', 'a', 's' ou 'd')\n");
				}
				else{
					break;
				}	
			} while(1);

			if (tecla_digitada == 'x'){
				return 0;
			}
			else if (tecla_digitada == 'm'){
				system("clear");
				printf("Menu\n");
				do{
					printf("Pressione 'v' para voltar para o labirinto.\n");
					printf("Pressione 'r' para recomeçar o labirinto.\n");
					printf("Pressiona 't' para ler as regras novamente.\n");
					printf("Pressione 'x' para terminar o programa.\n");
					scanf(" %c", &opcao_menu);
					opcao_menu = tolower(opcao_menu);
					teste = 0;
					while (getchar() != '\n'){
						teste++;
					}
					if ((teste != 0) || ((opcao_menu != 'v') && (opcao_menu != 'r') && (opcao_menu != 'x') && (opcao_menu != 't'))){
						printf("Digite uma opção válida!!('v', 'r', 't' ou 'x')\n");
					}
					else{
						if (opcao_menu == 'v'){
							system("clear");
							break;
						}
						else if (opcao_menu == 'r'){
							break;
						}
						else if (opcao_menu == 't'){
							system("clear");
							mostrar_regras();
							printf("Pressione ENTER para voltar para o labirinto...");
							while (getchar() != '\n');
							system("clear");
							break;
						}
						else if (opcao_menu == 'x'){
							return 0;
						}
					}
				} while(1);
			}
			else if (tecla_digitada == 'i'){
				system("clear");
				printf("Inventário\n");
				printf("Você possui %d tocha(s) 7x7.\n", tocha7);
				printf("Você possui %d tocha(s) 9x9.\n", tocha9);
				printf("Você possui %d tocha(s) 13x13.\n", tocha13);
				do{
					printf("Digite '1' para usar uma tocha 7x7, digite '2' para\n");
					printf("usar uma tocha 9x9, digite '3' para usar uma tocha\n");
					printf("13x13 ou digite 'v' para voltar para o labirinto.\n");
					scanf(" %c", &opcao_tocha);
					opcao_tocha = tolower(opcao_tocha);
					teste = 0;
					while (getchar() != '\n'){
						teste++;
					}
					if ((teste != 0) || ((opcao_tocha != '1') && (opcao_tocha != '2') && (opcao_tocha != '3') && (opcao_tocha != 'v'))){
						printf("Digite uma opção válida!!(1, 2 ou 3)\n");
					}
					else if ((opcao_tocha == '1') && (tocha7 == 0)){
						printf("Você não possui tochas 7x7! Escolha outra opção.\n");
					}
					else if ((opcao_tocha == '2') && (tocha9 == 0)){
						printf("Você não possui tochas 9x9! Escolha outra opção.\n");
					}
					else if ((opcao_tocha == '3') && (tocha13 == 0)){
						printf("Você não possui tochas 13x13! Escolha outra opção.\n");
					}
					else if (opcao_tocha == 'v'){
						system("clear");
						break;
					}
					else{
						if (opcao_tocha == '1'){
							tocha7--;
							tocha_parada(labirinto, linha_atual, coluna_atual, (7-1)/2);
						}
						else if (opcao_tocha == '2'){
							tocha9--;
							tocha_parada(labirinto, linha_atual, coluna_atual, (9-1)/2);
						}
						else if (opcao_tocha == '3'){
							tocha13--;
							tocha_parada(labirinto, linha_atual, coluna_atual, (13-1)/2);
						}
						system("clear");
						break;
					}
				} while(1);
			}
			else if (verifica_parede(labirinto, tecla_digitada, linha_atual, coluna_atual)){
				labirinto[linha_atual][coluna_atual] = 0;
				if (tecla_digitada == 'w'){
					linha_atual--;
				}
				else if (tecla_digitada == 'a'){
					coluna_atual--;
				}
				else if (tecla_digitada == 's'){
					linha_atual++;
				}
				else if (tecla_digitada == 'd'){
					coluna_atual++;
				}
				energia--;
				if (verifica_desafio(labirinto, linha_atual, coluna_atual)){
					desafio = rand() % 3;
					printf("Você chegou em um desafio.\n");
					if (desafio == 0){
						jogo_dos_dedos(&pontos, &energia, &tocha7, &tocha9, &tocha13);
					}
					else if (desafio == 1){
						pedra_papel_tesoura(&pontos, &energia, &tocha7, &tocha9, &tocha13);
					}
					else if (desafio == 2){
						forca(&pontos, &energia, &tocha7, &tocha9, &tocha13);
					}
				}
				labirinto[linha_atual][coluna_atual] = 3;
			}
			if (opcao_menu == 'r'){
				break;
			}
			if (energia == 0){
				printf("Suas energias acabaram, logo você não tem como\n");
				printf("continuar andando pelo labirinto e portanto a sua\n");
				printf("missão falhou.\n");
				break;
			}
			if ((linha_atual == 1) && (coluna_atual == 69)){
				system("clear");
				printf("Parabéns você conseguiu escapar do labirinto alienígena!!\n");
				pontos += energia;
				printf("As suas energias restantes foram convertidas para pontos.\n");
				printf("A sua pontuação final foi de %d ponto(s).\n", pontos);
				if (pontos > 150){
					printf("Você ganhou 3 estrelas pelo seu ótimo desempenho no labirinto.\n");
				}
				else if (pontos > 100){
					printf("Você ganhou 2 estrelas pelo seu bom desempenho no labirinto.\n");
				}
				else if (pontos > 50){
					printf("Você ganhou 1 estrela pelo seu desempenho mediano no labirinto.\n");
				}
				else{
					printf("Você ganhou 0 estrelas pelo seu desempenho no labirinto.\n");
				}
				break;
			}
		} while(1);

		do{
			if (opcao_menu == 'r'){
				break;
			}
			printf("Você gostaria de tentar novamente?(Sim ou não) ");
			scanf(" %4[^\n]", tentar_novamente);
			lower(tentar_novamente);
			while (getchar() != '\n');
			if (!strcmp(tentar_novamente, "sim")){
				break;
			}
			else if ((!strcmp(tentar_novamente, "não")) || (!strcmp(tentar_novamente, "nao"))){
				return 0;
			}
			else{
				printf("Digite uma opção válida!!(Sim ou não)\n");
			}
		} while(1);
	} while(1);

	return 0;
}
