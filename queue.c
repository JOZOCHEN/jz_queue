/**
 * @file queue.c
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#include "queue.h"

static inline unsigned char Queue_IsFull(Queue_HandleType* handle);
static inline unsigned char Queue_IsEmpty(Queue_HandleType* handle);

int Queue_Creat(Queue_HandleType* handle, unsigned char* buf, 
                        unsigned short element_size, unsigned short element_num)
{
    int ret = E_QUEUE_FAIL;

    if( (handle != NULL) && (buf != NULL) && (element_size != 0u) && (element_num != 0u))
    {
        handle->pbuf = buf;
        handle->element_size = element_size;
        handle->element_ind_max = (element_num - 1) * element_size;
        handle->head_ind = 0u;
        handle->tail_ind = 0u;
        handle->empty_flg = TRUE;
        handle->full_flg = FALSE;

        ret = E_QUEUE_OK;
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

static inline unsigned char Queue_IsFull(Queue_HandleType* handle)
{
    return handle->full_flg;
}

static inline unsigned char Queue_IsEmpty(Queue_HandleType* handle)
{
    return handle->empty_flg;   
}

int Queue_Push(Queue_HandleType* handle, unsigned char* data, unsigned short num)
{
    int ret = E_QUEUE_FAIL;
    unsigned long i = 0u, j = 0u;

    if( (handle != NULL) && (data != NULL) )
    {
        if(Queue_IsFull(handle) == TRUE)
        {
            ret = E_QUEUE_FAIL;
        }
        else
        {
            for(j = 0; j < num; j++){
                for(i = 0u; i < handle->element_size; i++)
                {
                    handle->pbuf[handle->head_ind + i] = data[j * handle->element_size + i];
                }
                handle->empty_flg = FALSE;

                handle->head_ind += handle->element_size;
                if(handle->head_ind > handle->element_ind_max)
                {
                    handle->head_ind = 0u;
                }
                else
                {
                    /*nothing*/
                }

                if(handle->head_ind == handle->tail_ind)
                {
                    handle->full_flg = TRUE;
                    j++;
                    break;
                }
                else
                {
                    /*nothing*/
                }
            }
            ret = j;
        }      
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

int Queue_Pop(Queue_HandleType* handle, unsigned char* data, unsigned short num)
{
    int ret = E_QUEUE_FAIL;
    unsigned long i = 0u, j= 0u;

    if( (handle != NULL) && (data != NULL) )
    {
        if(Queue_IsEmpty(handle) == TRUE)
        {
            ret = E_QUEUE_FAIL;
        }
        else
        {
            for(j = 0; j < num; j++){
                for(i = 0u; i < handle->element_size; i++)
                {
                    data[j * handle->element_size + i] = handle->pbuf[handle->tail_ind + i];
                }
                handle->full_flg = FALSE;

                handle->tail_ind += handle->element_size;
                if(handle->tail_ind > handle->element_ind_max)
                {
                    handle->tail_ind = 0u;
                }
                else
                {
                    /*nothing*/
                }

                if(handle->head_ind == handle->tail_ind)
                {
                    handle->empty_flg = TRUE;
                    j++;
                    break;
                }
                else
                {
                    /*nothing*/
                }
            }
            ret = j;
        }      
    }
    else
    {
        /*nothing*/
    }

    return ret;
}

#if 0
#include "stdio.h"
#include "stdint.h"

#define QUEUE_SIZE 5
#define TX_BUF_SIZE 6
#define RX_BUF_SIZE 6
void Queue_test(int32_t wr_cnt, int32_t rd_cnt, int32_t answer_wr_cnt, int32_t answer_read_cnt)
{
typedef uint8_t element_type;

    Queue_HandleType test_queue_handle;
    element_type test_queue_buf[QUEUE_SIZE];

    element_type test_tx_buf[TX_BUF_SIZE];
    element_type test_rx_buf[RX_BUF_SIZE];
    int32_t i = 0;

    int32_t test_wr_len = 0;
    int32_t test_rd_len = 0;

    //init
    // printf("init test_tx_buf\n");
    for(i = 0; i < TX_BUF_SIZE; i++){
        test_tx_buf[i] = i;
        // printf("0x%d ", test_tx_buf[i]);
    }
    // printf("\n");
    Queue_Creat(&test_queue_handle, (unsigned char *)test_queue_buf, 
        sizeof(test_queue_buf[0]), sizeof(test_queue_buf)/sizeof(test_queue_buf[0]));

    printf("test_wr_len = %d, test_rd_len = %d\n", wr_cnt, rd_cnt);
    test_wr_len = Queue_Push(&test_queue_handle, (uint8_t *)test_tx_buf, wr_cnt);
    // printf("Queue_Push:%d\n",test_wr_len);
    // if(test_wr_len > 0){
    //     for(i = 0 ; i < test_wr_len ; i++){
    //         printf("0x%d ", test_tx_buf[i]);
    //     }
    // }
    // printf("\n");    

    test_rd_len = Queue_Pop(&test_queue_handle, (uint8_t *)test_rx_buf, rd_cnt);
    // printf("Queue_Pop:%d\n",test_rd_len);
    // if(test_rd_len > 0){
    //     for(i = 0 ; i < test_rd_len ; i++){
    //         printf("0x%d ", test_rx_buf[i]);
    //     }
    // }
    // printf("\n");
    if( (answer_wr_cnt == test_wr_len) && (answer_read_cnt == test_rd_len)){
        printf("pass\n");
    }else{
        printf("fail\n");
    }
    // printf("\n");
}

int main(int arc, char** argv)
{
    Queue_test(4,4,4,4);
    Queue_test(4,5,4,4);
    Queue_test(4,6,4,4);

    Queue_test(5,4,5,4);
    Queue_test(5,5,5,5);
    Queue_test(5,6,5,5);

    Queue_test(6,4,5,4);
    Queue_test(6,5,5,5);
    Queue_test(6,6,5,5);
}
#endif
