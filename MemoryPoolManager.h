#pragma once

#ifndef __MEMORY_POOL_MANAGER_H__
#define __MEMORY_POOL_MANAGER_H__

//Memory pool manager with a fixed sized pre-allocated memory. allocation and deallocation is O(1). Can only handle data of the same size.
class MemoryPoolManager
{
private:
	void* head;
	int pool_size;
	int data_size;
	char* pool;

public:
	//The total size of the pool and the size of each data it's going to store. You can't allocate different sized instances with the pool manager.
	MemoryPoolManager(int poolSize, int dataSize);

	~MemoryPoolManager();

	//allocate data of size given while constructing the memory pool.
	void* allocate();

	//free the data.
	void free(void* ptr);

	//free space remeaining in the pool.
	int remainingSpace();

	//clear the memory pool, releasing all allocated instances.
	void clear();
	
private:
	void OutOfMemory();

};

#endif