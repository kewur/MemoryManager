#include "MemoryPoolManager.h"
#include <stdio.h>

typedef struct chunk
{
	chunk* next;
	void* getData()
	{
		return (void*) (((int)this) + (int)sizeof(Chunk));
	}
	
	static void* getChunk(void* ptr)
	{
		return (void*) ((int)ptr - (int)sizeof(Chunk));
	}
}Chunk;

//Enter in bytes. The real pool size is (poolSize + ((poolsize / datasize) * 4) in size.
MemoryPoolManager::MemoryPoolManager(int poolSize, int dataSize)
{
	this->pool_size = poolSize;
	this->data_size = dataSize;

	char* c = new char[(this->pool_size + ((this->pool_size / dataSize) * sizeof(Chunk)))](); //this is the only place new will be called.
	this->head = (void*) c;
	this->pool = c; //used when destroying. Having a handle for the pool isn't a bad thing either if you want to do stuff with it.

	Chunk* currentChunk = (Chunk*)this->head;

	for(int i=(int)this->head; i < (int)this->head + (this->pool_size + ((this->pool_size / dataSize) * sizeof(Chunk))) ; i += sizeof(Chunk) + dataSize)
	{
		currentChunk->next = (Chunk*) i;
		currentChunk = currentChunk->next;		
	}
}

MemoryPoolManager::~MemoryPoolManager()
{
	delete this->pool;
}

void* MemoryPoolManager::allocate()
{
	int address = 0;

	if(this->head != nullptr)
	{
		address = (int)this->head;
		this->head = (void*) ((Chunk*)this->head)->next; //remove the head from the free list
	}
	else
	{
		OutOfMemory();
	}

	return (void*) ((Chunk*)address)->getData();
}

//free an allocated data
void MemoryPoolManager::free(void* ptr)
{
	Chunk* header = (Chunk*)Chunk::getChunk(ptr);
	this->head = header;
}

//Get the remaining space in the pool.
int MemoryPoolManager::remainingSpace()
{
	int freeChunkRemaining = 0;

	Chunk* curChunk = (Chunk*) this->head;
	while(curChunk != nullptr)
	{

		++freeChunkRemaining;
		curChunk = curChunk->next;
	}

	return freeChunkRemaining * this->data_size;
}


//Free and clear all the allocated instances in the pool. 
void MemoryPoolManager::clear()
{
	this->head = (void*)this->pool; //reconstruct all the free nodes.

	Chunk* currentChunk = (Chunk*)this->head;

	for(int i=(int)this->head; i < (int)this->head + (this->pool_size + ((this->pool_size / this->data_size) * sizeof(Chunk))) ; i += sizeof(Chunk) + this->data_size)
	{
		currentChunk->next = (Chunk*) i;
		currentChunk = currentChunk->next;
		
	}


}

void MemoryPoolManager::OutOfMemory()
{
	printf("\nMemory pool out of memory\n");
	getchar();
}