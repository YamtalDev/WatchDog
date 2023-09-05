#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>/*size_t*/

typedef struct vector vector_t;

/*TC: O(1) - memory allocation by capacity. return NULL on fail */
vector_t *DVectorCreate(size_t capacity);

/*TC: O(1) - Clean */
void DVectorDestroy(vector_t *vector);

/*TC: O(1) - returns capacity */
size_t DVectorCapacity(const vector_t *vector);

/*TC: O(1) - returns size */
size_t DVectorSize(const vector_t *vector);

/*TC: O(1) - TRUE if size equals to 0 */
int DVectorIsEmpty(const vector_t *vector);

/*ATC: O(1) - push element to vector, increase capacity if needed, return 0 on success*/
int DVectorPushBack(vector_t *vector, void *element);

/*ATC: O(1) - remove last element , decrease capacity if needed
 keeping growth factor of 2, return 0 on success */
int DVectorPopBack(vector_t *vector);

/*ATC: O(1) - remove last element decrease capacity if needed
 keeping growth factor of 2 can't fail */
void DVectorSafePop(vector_t *vector);

/*TC: O(1) - set element in index*/
void DVectorSetElement(vector_t *vector, size_t index, void *element);

/*TC: O(1) - get indexed element*/
void *DVectorGetElement(const vector_t *vector, size_t index);

/*TC: O(n) - may increase capacity to held reserve, return 0 on success*/
int DVectorReserve(vector_t *vector, size_t reserve);

/*TC: O(n) - decrease capacity to size, returns 0 on success*/
int DVectorShrinkToFit(vector_t *vector);

#endif /* __VECTOR_H__ */
