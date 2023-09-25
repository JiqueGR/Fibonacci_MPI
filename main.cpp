#include <iostream>
#include <time.h>
#include <conio.h>
#include <mpi.h>

using namespace std;

//-- Estruturas e Variáveis Globais ---------------------------------------------

// Vetor auxiliar para produzir a seq. de fibonacci com estratégia de programação dinâmica
long double vet_fibo[100];

//-------------------------------------------------------------------------------
long double fibonacci(int n)
{
	if( n <= 0 ) return 0;
	
	// se a sequência n não estiver calculada, então calcule, senão, não faça nada
	if( vet_fibo[n-1] == -1 )
	{
		if( n == 1 || n == 2)
		{		
			vet_fibo[n-1] = 1;
		}
		else 
		{		
			vet_fibo[n-1] = fibonacci(n-1) + fibonacci(n-2);				
		}
	}
	
	return vet_fibo[n-1];
		
} // fibonacci(int n)

//-------------------------------------------------------------------------------
int main(int argc, char** argv) {

	for(int i=0; i<100; i++) vet_fibo[i]=-1;
	
	// NÃO UTILIZE O VETOR vet_fibo
	
	MPI_Init(&argc, &argv);
    int rank, tamanho;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tamanho);
    int numero;
    int numerorecebido;
    int soma = 0;
    int inicio = 0;
    int fim = 0;
    
	if (rank == 0)
	{
        for(int i=0; i<5; i++){
        	numero = fibonacci(i);
        	std::cout << "Numero " << numero << std::endl;
		}
		for (int i = 1; i < tamanho; i++)
		{
			inicio = rank * 5;
			fim = inicio + 5;
			
        	for(int j=inicio; j<fim; j++){
        	MPI_Recv(&numerorecebido, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	std::cout << "Numero " << numerorecebido << std::endl;
			}
        } 
    } 
	else 
	{
		inicio = rank * 5;
		fim = inicio + 5;
        for(int i=inicio; i<fim; i++){
        	numero = fibonacci(i);
        	MPI_Send(&numero, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
    }
    MPI_Finalize();
	return 0;
	
} // main()
