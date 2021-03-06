/**
* @file
* @author
* @date
* @brief
* @see
*/

#ifndef _KERNEL_SEMAPHORE_H_
#define _KERNEL_SEMAPHORE_H_

/*****************************************************************************
 * Header files
 *****************************************************************************/
/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
#define DEF_SEM_MAX    8


/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Structures
 *****************************************************************************/
/**
* @brief Mutex
* @details
* @see 
*/
typedef struct _kernel_mutex_t {
    uint32_t owner;
    bool lock;
} kernel_mutex_t;


/*****************************************************************************
 * Function prototypes
 *****************************************************************************/
/**
* @brief
* @param[in]
* @param[out]
* @return void
*/
void kernel_sem_init(int32_t max);
bool kernel_sem_lock(void);
void kernel_sem_unlock(void);

void kernel_mutex_init(void);
bool kernel_mutex_lock(uint32_t owner);
bool kernel_mutex_unlock(uint32_t owner);

#endif /* _KERNEL_SEMAPHORE_H_ */
