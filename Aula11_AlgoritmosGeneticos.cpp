// Algoritmos Genéticos - Aula 11
// Integrantes: João Gilberto Soares Oliveira, Vinicius de Brites Bandeira

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

int tam_genes = 12; //Quantidade de genes
int tam_pop = 10; //Quantidade de indivíduos da população
int geracoes = 1000; //Quantidade de gerações
double prob_mut = 0.2; //Probabilidade de mutação

// População
vector<vector<int>> populacao;
vector<vector<int>> filhos;

void inicializaPopulacao()
{
	for(int i = 0; i < tam_pop; i++)
	{
		vector<int> individuo;

		for(int j = 0; j < tam_genes; j++)
		{
			int num = rand() % 2; //Escolhe um número no intervalo [0,1]
			individuo.push_back(num); //Insere no vetor do individuo
		}

		populacao.push_back(individuo); //Insere um individuo no vetor da populacao
	}
}

void mostrarPopulacao()
{
	cout << "Populacao: ";
	for(int i = 0; i < tam_pop; i++)
	{
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[i][j] << " ";
		cout << endl;
	}
}

//Retorna o score do indivíduo
int obterPontuacao(vector<int> individuo)
{
	//O score é o resultado da função proposta no exercício
	int funcao = 0, x = 0, y = 0, w = 0, z = 0;
	
	if(individuo[2] == 1)
	{
		x += 1;
	}
	if(individuo[1] == 1)
	{
		x += 2;
	}
	if(individuo[0] == 1)
	{
		x += 4;
	}
	if(individuo[5] == 1)
	{
		y += 1;
	}
	if(individuo[4] == 1)
	{
		y += 2;
	}
	if(individuo[3] == 1)
	{
		y += 4;
	}
	if(individuo[8] == 1)
	{
		w += 1;
	}
	if(individuo[7] == 1)
	{
		w += 2;
	}
	if(individuo[6] == 1)
	{
		w += 4;
	}
	if(individuo[11] == 1)
	{
		z += 1;
	}
	if(individuo[10] == 1)
	{
		z += 2;
	}
	if(individuo[9] == 1)
	{
		z += 4;
	}
	
	funcao = (5 * x) + pow(y,2) + w + pow(z,3);
	return funcao;
}

//Realiza o cruzamento
void cruzamento(int indice_pai1, int indice_pai2, vector<int>& filho)
{
	//O ponto escolhido é aleatório
	int ponto = rand() % tam_genes;

	for(int i = 0; i <= ponto; i++)
		filho.push_back(populacao[indice_pai1][i]);
	for(int i = ponto + 1; i < tam_genes; i++)
		filho.push_back(populacao[indice_pai2][i]);
}

//Realiza a mutação
void mutacao(vector<int>& individuo)
{
	//Escolhe um gene aleatoriamente no intervalo [0, tam_genes - 1]
	int gene = rand() % tam_genes;

	// Modifica o valor do gene escolhido
	if(individuo[gene] == 0)
		individuo[gene] = 1;
	else
		individuo[gene] = 0;
}

//Retorna o índice do melhor indivíduo da população
vector<int> obterMelhor()
{
	vector<int> indice_melhores;
	int indice_primeiro_menor = 0, indice_segundo_menor = 0, indice_primeiro_maior = 0, indice_segundo_maior = 0;
	int score_primeiro_menor = 0, score_segundo_menor = 0, score_primeiro_maior = 1000, score_segundo_maior = 0;

	for(int i = 1; i < tam_pop; i++)
	{
		int score = obterPontuacao(populacao[i]);
		if(score <= 185)
		{
			if(score > score_primeiro_menor)
			{
				indice_segundo_menor = indice_primeiro_menor;
				score_segundo_menor = score_primeiro_menor;
				indice_primeiro_menor = i;
				score_primeiro_menor = score;
			}
		}
		
		if(score >= 185)
		{
			if(score < score_primeiro_maior)
			{
				indice_segundo_maior = indice_primeiro_maior;
				score_segundo_maior = score_primeiro_maior;
				indice_primeiro_maior = i;
				score_primeiro_maior = score;
			}
		}
	}
	//Insere os quatro melhores no vetor, os dois menores que 185 e os dois maiores que 185
	indice_melhores.push_back(indice_primeiro_menor);
	indice_melhores.push_back(indice_segundo_menor);
	indice_melhores.push_back(indice_primeiro_maior);
	indice_melhores.push_back(indice_segundo_maior);

	return indice_melhores;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	inicializaPopulacao();
	mostrarPopulacao();
	vector<int> indice_melhores = obterMelhor();
	vector<int> filho;
	

	for(int i = 0; i < geracoes; i++)
	{
		for(int j = 0; j < tam_pop; j++)
		{
			
			//Garantindo que o melhor indivíduo dos menores gere 4 filhos
			if(j >= 0 && j <= 3)
			{
				int indice_pai1 = indice_melhores[0];
				int indice_pai2;
				
				// Garante que os índices dos pais não são iguais
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);
				
				
				// Aplica o cruzamento
				cruzamento(indice_pai1, indice_pai2, filho);

				// Calcula a probabilidade de mutação
				double prob = ((double) rand() / ((double)RAND_MAX + 1));
				if(prob < prob_mut)
					mutacao(filho);
					
				// Faz a cópia dos genes do filho para a população de filhos
				for(int k = 0; k < tam_genes; k++)
					populacao[j][k] = filho[k];
				
			}

			//Garantindo que o segundo melhor indivíduo dos menores gere 1 filho
			else if(j == 4)
			{
				int indice_pai1 = indice_melhores[1];
				int indice_pai2;
				
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);
				
				
				cruzamento(indice_pai1, indice_pai2, filho);
				
				double prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mut)
					mutacao(filho);
					
				for(int k = 0; k < tam_genes; k++)
					populacao[j][k] = filho[k];
			}
			
			//Garantindo que o melhor indivíduo dos maiores gere 4 filhos
			else if(j >= 5 && j <= 8)
			{
				int indice_pai1 = indice_melhores[2];
				int indice_pai2;
				
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);
				
				
				cruzamento(indice_pai1, indice_pai2, filho);
				
				double prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mut)
					mutacao(filho);
					
				for(int k = 0; k < tam_genes; k++)
					populacao[j][k] = filho[k];
			}
					
			//Garantindo que o segundo melhor indivíduo dos maiores gere 1 filho
			else if(j == 9)
			{
				int indice_pai1 = indice_melhores[3];
				int indice_pai2;
				
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);
				
				
				cruzamento(indice_pai1, indice_pai2, filho);
				
				double prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mut)
					mutacao(filho);
					
				for(int k = 0; k < tam_genes; k++)
					populacao[j][k] = filho[k];
			}
		}
		
		cout << "Geracao " << i + 1 << endl;
		mostrarPopulacao();
		cout << endl << endl << "Melhores: " << endl << endl;
		
		indice_melhores = obterMelhor();
		int score_melhor_menor = obterPontuacao(populacao[indice_melhores[0]]);
		int score_melhor_maior = obterPontuacao(populacao[indice_melhores[2]]);
		
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[indice_melhores[0]][j] << " ";
		
		cout << "\nPontuacao: " << score_melhor_menor << "\n\n";
		
		for(int j = 0; j < tam_genes; j++)
			cout << populacao[indice_melhores[2]][j] << " ";
			
		cout << "\nPontuacao: " << score_melhor_maior << "\n\n";
		
		//Verifica se encontrou a solução ótima
		if(score_melhor_menor == 185 || score_melhor_maior == 185)
			break;
	}

	return 0;
}