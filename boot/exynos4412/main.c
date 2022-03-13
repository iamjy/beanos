/**
 * @file
 * @author
 * @date
 * @brief
 * @see
 */

/*****************************************************************************
 * Header files
 *****************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "memio.h"
#include "task.h"
#include "event.h"
#include "kernel.h"
#include "synch.h"
#include "interrupt_table.h"    //< T.B.D - Temp
#include "hal_interrupt.h"      //< T.B.D - Temp
#include "hal_wdt.h"            //< T.B.D - Temp
#include "hal_timer.h"          //< T.B.D - Temp
#include "hal_uart.h"           //< T.B.D - Temp
#include "hal_i2c.h"            //< T.B.D - Temp


/*****************************************************************************
 * Macro definitions
 *****************************************************************************/
/*****************************************************************************
 * Type definitions
 *****************************************************************************/
/*****************************************************************************
 * Enumerations
 *****************************************************************************/
/*****************************************************************************
 * Global variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Test
 --------------------------------------------------------------------------- */
uint32_t TEST_I2C_ID = 6;   //< Test - I2C_6


/*****************************************************************************
 * Static variables
 *****************************************************************************/
/* ---------------------------------------------------------------------------
   - Variables
 --------------------------------------------------------------------------- */
static uint32_t test_shared_value;  //< Test

/* ---------------------------------------------------------------------------
   - Functions
 --------------------------------------------------------------------------- */
static void hw_init(void);
static void kernel_init(void);

static void test_user_task0(void);
static void test_user_task1(void);
static void test_user_task2(void);
static void test_critical_section(uint32_t p, uint32_t task_id);
static void test_i2c_master_write();
static void test_i2c_master_read();
static void test_i2c_slave_write();
static void test_i2c_slave_read();


/*****************************************************************************
 * Extern variables
 *****************************************************************************/
 /*****************************************************************************
 * Function definitions
 *****************************************************************************/
int main(void)
{
    // __asm__("swi 77"); //< Interrupt vector table test...
    __asm__("mov r1, #0x40000000");
    __asm__("mov r2, #0x2");
    __asm__("mov r3, #0x3");
    __asm__("mov r4, #0x4");
    __asm__("mov r5, #0x5");
    __asm__("str r1, [r0]!");
    __asm__("str r1, [r0, #4]");
    __asm__("str r1, [r0], #4");
    __asm__("str r1, [r0, #4]!");    

    hw_init();

    while (1) {
        test_i2c_master_write();
        test_i2c_master_read();
    }

    // kernel_init();

    while(true);

    return 0;
}

void test_user_task0(void)
{
    uint32_t local = 0;

    debug_printf("[TASK] #0 SP = 0x%x\n", &local);

    /// Sync Test (Semaphore)
    uint8_t cmd_buf[16];
    uint32_t cmd_buf_idx = 0;
    uint8_t uartch = 0;

    while (true) {
        uint32_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

        evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_UART_IN
                                    | KERNEL_EVENT_FLAG_CMD_OUT);

        switch(evt_hdl) {
        case KERNEL_EVENT_FLAG_UART_IN:
            kernel_recv_msg(KERNEL_MSGQ_TASK_0, &uartch, 1);
            if (uartch == '\r') {
                cmd_buf[cmd_buf_idx] = '\0';

                kernel_send_events(KERNEL_EVENT_FLAG_CMD_IN);

                if (false == kernel_send_msg(KERNEL_MSGQ_TASK_1, &cmd_buf_idx, 1)) {
                    kernel_yield();
                }
                else if (false == kernel_send_msg(KERNEL_MSGQ_TASK_1, cmd_buf, cmd_buf_idx)) {
                    uint8_t rollback;
                    
                    kernel_recv_msg(KERNEL_MSGQ_TASK_1, &rollback, 1);

                    kernel_yield();
                }
                else
                    break;                
            }
            else {
                cmd_buf[cmd_buf_idx] = uartch;
                cmd_buf_idx++;
                cmd_buf_idx %= 16;
            }

            break;
        case KERNEL_EVENT_FLAG_CMD_OUT:
            test_critical_section(5, 0);

            break;
        case KERNEL_EVENT_FLAG_EMPTY:
            
            break;
        default:
            debug_printf("\n[TASK_1] Unknown event!\n");
            
            break;
        }

        kernel_yield();
    }

    /// Message Queue Test
    /*
    uint8_t cmd_buf[16];
    uint32_t cmd_buf_idx = 0;
    uint8_t uartch = 0;

    while (true) {
        kernel_event_flag_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

        evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_UART_IN
                                    | KERNEL_EVENT_FLAG_CMD_OUT);

        switch(evt_hdl) {
        case KERNEL_EVENT_FLAG_UART_IN:
            kernel_recv_msg(KERNEL_MSGQ_TASK_0, &uartch, 1);
            if (uartch == '\r') {
                cmd_buf[cmd_buf_idx] = '\0';

                kernel_send_events(KERNEL_EVENT_FLAG_CMD_IN);

                if (false == kernel_send_msg(KERNEL_MSGQ_TASK_1, &cmd_buf_idx, 1)) {
                    kernel_yield();
                }
                else if (false == kernel_send_msg(KERNEL_MSGQ_TASK_1, cmd_buf, cmd_buf_idx)) {
                    uint8_t rollback;
                    
                    kernel_recv_msg(KERNEL_MSGQ_TASK_1, &rollback, 1);

                    kernel_yield();
                }
                else
                    break;                
            }
            else {
                cmd_buf[cmd_buf_idx] = uartch;
                debug_printf("[EN-QUEUE] %s", cmd_buf);
                cmd_buf_idx++;
                cmd_buf_idx %= 16;
            }

            break;
        case KERNEL_EVENT_FLAG_CMD_OUT:
            debug_printf("\n[TASK_0] CmdOut Event by Task0..\n");

            break;
        case KERNEL_EVENT_FLAG_EMPTY:
            
            break;
        default:
            debug_printf("\n[TASK_1] Unknown event!\n");
            
            break;
        }

        kernel_yield();
    }
    */

    /// Event Test
    /*
    while (true) {
        bool pending_evt = true;

        while (pending_evt) {
            kernel_event_flag_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

            evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_UART_IN
                                        | KERNEL_EVENT_FLAG_CMD_OUT);
            
            switch(evt_hdl) {
            case KERNEL_EVENT_FLAG_UART_IN:
                debug_printf("\n[TASK_0] Event handled..\n");

                break;
            case KERNEL_EVENT_FLAG_CMD_OUT:
                debug_printf("\n[TASK_0] CmdOut Event by Task0..\n");

                break;
            case KERNEL_EVENT_FLAG_EMPTY:
                pending_evt = false;

                break;
            default:
                debug_printf("\n[TASK_1] Unknown event!\n");
                
                break;
            }
        }

        kernel_yield();
    }
    */
}

void test_user_task1(void)
{
    uint32_t local = 0;

    debug_printf("[TASK] #1 SP = 0x%x\n", &local);

    /// Sync Test (Mutex)
    uint8_t cmd_len = 0;
    uint8_t cmd[16] = {0,};

    while (true) {
        uint32_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

        evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_CMD_IN
                                     | KERNEL_EVENT_FLAG_UNLOCK);

        switch(evt_hdl) {
        case KERNEL_EVENT_FLAG_CMD_IN:
            memclr(cmd, 16);

            kernel_recv_msg(KERNEL_MSGQ_TASK_1, &cmd_len, 1);
            kernel_recv_msg(KERNEL_MSGQ_TASK_1, cmd, cmd_len);

            debug_printf("\nRecv Cmd: %s\n", cmd);

            break;
        case KERNEL_EVENT_FLAG_UNLOCK:
            // kernel_unlock_mutex();
            // kernel_unlock_sem();
        
            break;
        case KERNEL_EVENT_FLAG_EMPTY:
        
            break;
        default:
            debug_printf("\n[TASK_1] Unknown event!\n");

            break;
        }
        
        kernel_yield();
    }

    /// Message Queue Test
    /*
    uint8_t cmd_len = 0;
    uint8_t cmd[16] = {0,};

    while (true) {
        kernel_event_flag_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

        evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_CMD_IN);

        switch(evt_hdl) {
        case KERNEL_EVENT_FLAG_CMD_IN:
            memclr(cmd, 16);

            kernel_recv_msg(KERNEL_MSGQ_TASK_1, &cmd_len, 1);
            kernel_recv_msg(KERNEL_MSGQ_TASK_1, cmd, cmd_len);

            debug_printf("\nRecv Cmd: %s\n", cmd);

            break;
        case KERNEL_EVENT_FLAG_EMPTY:
        
            break;
        default:
            debug_printf("\n[TASK_1] Unknown event!\n");

            break;
        }
        
        kernel_yield();
    }
    */

    /// Event Test
    /*
    while (true) {
        kernel_event_flag_t evt_hdl = KERNEL_EVENT_FLAG_EMPTY;

        evt_hdl = kernel_wait_events(KERNEL_EVENT_FLAG_CMD_IN);

        switch(evt_hdl) {
        case KERNEL_EVENT_FLAG_CMD_IN:
            debug_printf("\n[TASK_1] Event handled..\n");

            break;
        case KERNEL_EVENT_FLAG_EMPTY:
        
            break;
        default:
            debug_printf("\n[TASK_1] Unknown event!\n");

            break;
        }
        
        kernel_yield();
    }
    */
}

void test_user_task2(void)
{
    uint32_t local = 0;

    debug_printf("[TASK] #2 SP = 0x%x\n", &local);

    /// Sync Test (Semaphore and Mutex)
    while (true) {
        test_critical_section(3, 2);

        kernel_yield();
    }

    /*
    while (true) {
        
        kernel_yield();
    }
    */
}

static void hw_init(void)
{
    uint32_t gic_mask = 0xFF;
    uint32_t baud_rate = 115200;

    HAL_interrupt_init((void *)&gic_mask);

    HAL_uart_init(baud_rate, GIC_INTID_UART_2);
    HAL_timer_init(GIC_INTID_TIMER_4);
    HAL_wdt_init(GIC_INTID_WDT);

    return;
}

static void kernel_init(void)
{
    int32_t task_id = -1;

    kernel_task_init();
    kernel_event_flag_init();
    kernel_msgq_init();
    kernel_sem_init(1);
    kernel_mutex_init();

    task_id = kernel_task_create(test_user_task0);
    if (NOT_ENOUGH_TASK_NUM == task_id)
        debug_printf("[TASK] task 0 creation fail!%s\n");

    task_id = kernel_task_create(test_user_task1);
    if (NOT_ENOUGH_TASK_NUM == task_id)
        debug_printf("[TASK] task 1 creation fail!%s\n");

    task_id = kernel_task_create(test_user_task2);
    if (NOT_ENOUGH_TASK_NUM == task_id)
        debug_printf("[TASK] task 2 creation fail!%s\n");

    kernel_start();
}

static void test_critical_section(uint32_t p, uint32_t task_id)
{
    kernel_lock_mutex();
    // kernel_lock_sem();

    debug_printf("User Task #%u Send=%u\n", task_id, p);

    test_shared_value = p;
    kernel_yield();
    delay(1000);    //< T.B.D - 1sec

    debug_printf("User Task #%u Shared Value=%u\n", task_id, test_shared_value);

    kernel_unlock_mutex();
    // kernel_unlock_sem();
}

void test_i2c_master_write()
{
    hal_i2c_transaction_t transaction;
    uint8_t data[31] = {
        0x11,0x2D,0x75,0x40,0x01,0x00,
        0x08,0x82,0x00,0x0E,0xD9,0x45,
        0xA0,0xAC,0x80,0x08,0x80,0x11,
        0x84,0x02,0x22,0x44,0x86,0x54,
        0xE4,0x24,0x00,0x00,0x00,0x01,
        0x80};
    uint32_t wr_cnt = sizeof(data) / sizeof(data[0]);
    volatile uint32_t *mux = (volatile uint32_t *)0x11400080;

    memset(&transaction, 0, sizeof(transaction));

    *mux = 0x44000;

    HAL_i2c_dev_open(TEST_I2C_ID);

    transaction.addr = 0xE0;        //< [7:1] 0x70 (Slave Address)
    transaction.sub_addr = 0x01;
    transaction.buf = data;
    transaction.cnt = wr_cnt;
    HAL_i2c_data_transmit(TEST_I2C_ID, &transaction);

    HAL_i2c_dev_close(TEST_I2C_ID);
}

void test_i2c_master_read()
{
    hal_i2c_transaction_t transaction;
    uint8_t data[31];
    uint32_t rd_cnt = sizeof(data) / sizeof(data[0]);
    volatile uint32_t *mux = (volatile uint32_t *)0x11400080;
    uint32_t i = 0;

    memset(&transaction, 0, sizeof(transaction));
    memset(data, 0x0, sizeof(data));
    
    *mux = 0x44000;

    HAL_i2c_dev_open(TEST_I2C_ID);

    transaction.addr = 0xE0;        //< [7:1] 0x70 (Slave Address)
    transaction.sub_addr = 0x01;
    transaction.buf = data;
    transaction.cnt = rd_cnt;
    HAL_i2c_data_receive(TEST_I2C_ID, &transaction);

    debug_printf("\n");

    for (i = 0; i < rd_cnt; i++) {
        debug_printf("0x%x ", data[i]);
        if ((i % 5) == 0)
            debug_printf("\n");
    }

    HAL_i2c_dev_close(TEST_I2C_ID);
}

static void test_i2c_slave_write()
{

}

static void test_i2c_slave_read()
{

}
