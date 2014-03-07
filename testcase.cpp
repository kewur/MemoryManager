

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#include "MemoryPoolManager.h"


	int main(void)
	{
		MemoryPoolManager* particleMemoryManager = new MemoryPoolManager(sizeof(int) * 12, sizeof(int));
		printf("free remaining %d \n", particleMemoryManager->remainingSpace());
		
		int* n1; 
		for(int i=0; i < 12; i++)
		{
			n1 = (int*)particleMemoryManager->allocate();
			*n1 = i;	
		}

		printf("free remaining %d \n", particleMemoryManager->remainingSpace());
		particleMemoryManager->free(n1);
		printf("free remaining %d \n", particleMemoryManager->remainingSpace());
		n1 = (int*)particleMemoryManager->allocate();
		printf("free remaining %d \n", particleMemoryManager->remainingSpace());

		particleMemoryManager->clear();
		printf("free remaining %d \n", particleMemoryManager->remainingSpace());


		delete particleMemoryManager;

		return 0;
	}

