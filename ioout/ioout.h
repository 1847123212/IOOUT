/**
  * @file       ioout.h
  * @brief      IO�������ͷ�ļ�
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-09
  *
  * @note
  * [2016-08-09] <redoc> v1.0
  * ��ʼ�汾
  * @remark
  */


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __IOOUT_H
#define __IOOUT_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ioout_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if !defined(IOOUT_BASE_TIME)
#error "Please configure basic time (in ioout_cfg.h)"
#endif

/* types ------------------------------------------------------------*/
struct ioout_struct
{
    uint16_t interval;          /**<  ���ʱ�䣨ռ�ձȵͣ�     */
    uint16_t work_time;         /**<  ����ʱ�䣨ռ�ձȸߣ�     */
    uint16_t ctrl_time;         /**<  ��ʱ��                   */
    uint16_t cur_count;         /**<  �����ڼ���               */
    uint16_t sum_count;         /**<  ��ʱ�����               */
    uint8_t  enable       :1;   /**<  ʹ��                     */
    uint8_t  io_state     :1;   /**<  ���Ʊ仯��־             */
    uint8_t  reserved     :6;   /**<  ����                     */
    void (*ioout_cb)(uint8_t);  /**<  �ص����� ����true/false  */
    struct ioout_struct* next;
};

typedef struct ioout_struct *ioout_t;


/* constants --------------------------------------------------------*/
/* variables --------------------------------------------------------*/
/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/
// ioout_port.c
int ioout_config(void);

#ifdef IOOUT_USE_MEM
void *ioout_malloc(uint32_t nbytes);
void ioout_free (void *ptr);
#endif

// ioout.c
int ioout_init(ioout_t handle, void(*ioout_cb)(uint8_t));
int ioout_kill(ioout_t handle);
int ioout_start(ioout_t handle);
int ioout_stop(ioout_t handle);
int ioout_pause(ioout_t handle);
int ioout_set(ioout_t handle, uint32_t interval, uint32_t work_time, uint32_t ctrl_time, uint8_t interval_first);
void ioout_loop(void);

#ifdef __cplusplus
}
#endif

#endif  /*__IOOUT_H*/

