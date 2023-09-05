/******************************************************************************

    writer: Tal Aharon

    reviewer: Ishai zilberman

    date: 06.03.2023

******************************************************************************/
#include <stdlib.h>     /* malloc, realloc  */
#include <stddef.h>     /* size_t, NULL     */
#include <assert.h>     /* assert           */
#include <math.h>       /* pow              */

#include "wd_vector.h"  /* Internal use     */
/*****************************************************************************/
enum status
{
	SUCCESS = 0, FAILURE
};
/*****************************************************************************/
struct vector
{
	size_t size;
	size_t capacity;
	void **elements;
};
/*****************************************************************************/
#define GROWTH_FACTOR (2)
#define SIZE (vector->size)
#define CAPACITY (vector->capacity)
#define ELEMENTS (vector->elements)
#define ELEMENT_SIZE (sizeof(void *))
static int ReallocateVector(void **, size_t);
/*****************************************************************************/
vector_t *DVectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	if(NULL == vector)
	{
		return (NULL);
	}

	ELEMENTS = (void **)malloc((capacity * ELEMENT_SIZE));
	if(NULL == ELEMENTS)
	{
		free(vector);
		return (NULL);
	}

	SIZE = 0;
	CAPACITY = capacity;
	return (vector);
}
/*****************************************************************************/
void DVectorDestroy(vector_t *vector)
{
	assert(vector);
	free(ELEMENTS);
	free(vector);
	vector = NULL;
}
/*****************************************************************************/
size_t DVectorCapacity(const vector_t *vector)
{
	assert(vector);
	return (CAPACITY);
}
/*****************************************************************************/
size_t DVectorSize(const vector_t *vector)
{
	assert(vector);
	return (SIZE);
}
/*****************************************************************************/
int DVectorIsEmpty(const vector_t *vector)
{
	assert(vector);
	return (SIZE == 0);
}
/*****************************************************************************/
int DVectorPushBack(vector_t *vector, void *element)
{
	int status = SUCCESS;
	assert(vector);

	if(SIZE == CAPACITY)
	{
		CAPACITY *= GROWTH_FACTOR;
		ELEMENTS = (void **)realloc(ELEMENTS,  CAPACITY * ELEMENT_SIZE);
		if(NULL == ELEMENTS)
		{
			free(ELEMENTS);
			return (FAILURE);
		}
	}

	*(ELEMENTS + SIZE++) = element;
	return (status);
}
/*****************************************************************************/
int DVectorPopBack(vector_t *vector)
{
	size_t status = SUCCESS;
	assert(vector);
	--SIZE;

	if((SIZE * pow(GROWTH_FACTOR, 2)) <= CAPACITY)
	{
		CAPACITY = (SIZE * GROWTH_FACTOR) + 2;
		status = ReallocateVector(ELEMENTS, CAPACITY * ELEMENT_SIZE);
	}

	return (status);
}
/*****************************************************************************/
void DVectorSafePop(vector_t *vector)
{
	size_t i = 0;
	void **tmp = NULL;

	assert(vector);
	--SIZE;

	if(SIZE * pow(GROWTH_FACTOR, 2) <= CAPACITY)
	{
		CAPACITY = (SIZE * GROWTH_FACTOR) + 2;
		tmp = (void **)malloc(CAPACITY * ELEMENT_SIZE);
		if(NULL != tmp)
		{
			for(; i < SIZE; ++i)
			{
				*(tmp + i) = *(ELEMENTS + i);
			}

			free(ELEMENTS);
			ELEMENTS = tmp;
			return;
		}

		CAPACITY = (SIZE / GROWTH_FACTOR) - 2;
	}
}
/*****************************************************************************/
void DVectorSetElement(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	if(index <= SIZE)
		*(ELEMENTS + index) = element; 
}
/*****************************************************************************/
void *DVectorGetElement(const vector_t *vector, size_t index)
{
	assert(vector);
	return (SIZE < index ? NULL : *(ELEMENTS + index));
}
/*****************************************************************************/
int DVectorReserve(vector_t *vector, size_t reserve)
{
	int status = SUCCESS;
	assert(vector);
	if(reserve > (CAPACITY - SIZE))
	{
		CAPACITY = reserve + SIZE;
		status = ReallocateVector(ELEMENTS, CAPACITY * ELEMENT_SIZE);
	}

	return (status);
}
/*****************************************************************************/
int DVectorShrinkToFit(vector_t *vector)
{
	int status = SUCCESS;
	assert(vector);
	if(CAPACITY > SIZE)
	{
		CAPACITY = SIZE;
		status = ReallocateVector(ELEMENTS, CAPACITY * ELEMENT_SIZE);
	}

	return (status);
}
/*****************************************************************************/
static int ReallocateVector(void **elements, size_t reallocation_size)
{
	elements = (void **)realloc(elements, reallocation_size);
	if(NULL == elements)
	{
		free(elements);
		return (FAILURE);
	}

	return (SUCCESS);
}
/*****************************************************************************/
