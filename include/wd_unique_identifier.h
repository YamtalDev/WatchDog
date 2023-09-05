#ifndef __UNIQUE_IDENTIFIER_H__
#define __UNIQUE_IDENTIFIER_H__

#include <sys/types.h> /* time_t, pid_t */
#include <stdatomic.h> /* atomic_size_t */

typedef struct ilrd_uid
{
	atomic_size_t counter;
	time_t time_stamp;
	pid_t pid;

} ilrd_uid_t;

ilrd_uid_t UIDCreate(void);

ilrd_uid_t UIDGetBad(void);

int UIDIsMatch(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* __UNIQUE_IDENTIFIER_H__ */
