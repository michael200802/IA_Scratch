#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NINPUTS 4
#define NNEURONS NINPUTS

#define MAX_VALUE 9

#define randnum() rand()%(MAX_VALUE+1)

#define condition(num) (num%2 == 0 && num%3 == 0 && num != 0)

//objective: output shall be even
int main(int argc, char ** argv)
{
	int64_t input[NINPUTS];
	int64_t output[NINPUTS] = {};
	int64_t weights[NNEURONS][NINPUTS];
	int64_t biases[NNEURONS];

	//read from CmdLine
	argc--;
	argv++;
	if(argc < NINPUTS)
	{
		printf("Give the correct number of arguments: %d.",NINPUTS);
		return 0;
	}
	for(size_t i = 0; i < NINPUTS; i++)
	{
		sscanf(*argv, "%d", input+i);
		argv++;
	}

	srand(time(NULL));

	bool is_ready;
	do
	{
		is_ready = true;
		for(size_t i = 0; i < NNEURONS; i++)
		{
			if(!condition(output[i]))
			{
				output[i] = 0;
				for(size_t j = 0; j < NINPUTS; j++)
				{
					weights[i][j] = randnum();
					output[i] += input[j]*weights[i][j];
				}
				biases[i] = randnum();
				output[i] += biases[i];

				is_ready = false;
			}
		}

	}
	while(is_ready == false);


	for(size_t i = 0; i < NNEURONS; i++)
	{
		printf("Neuron %zu ---> output: %d\n\tWeights: ",i+1, output[i]);
		for(size_t j = 0; j < NINPUTS; j++)
		{
			printf("%d,",weights[i][j]);
		}
		printf(" bias: %d\n",biases[i]);
	}

	return 0;
}
