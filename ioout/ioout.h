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
#include "ioout_config.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

/**
  * @brief IO������ƻص��������Ͷ���
  */
typedef void (*IOOUTCALLBACK)(uint8_t);

/**
  * @brief IO���error code
  */
typedef enum
{
    IOOUT_ERR_INIT = -4,        /**<  ��ʼ������  */
    IOOUT_ERR_PARAM = -3,       /**<  �����������  */
    IOOUT_ERR_FAIL = -2,        /**<  ����ʧ��  */
    IOOUT_ERR_MAX = -1,         /**<  �������ֵ  */
    IOOUT_NO_ERR = 0,           /**<  �޴���  */

}ioout_err_t;

/**
  * @brief IO������Ƽ�ʱ���ṹ
  */
typedef struct
{
    uint32_t interval;          /**<  ���ʱ�䣨ռ�ձȵͣ�  */
    uint32_t workTime;          /**<  ����ʱ�䣨ռ�ձȸߣ�  */
    uint32_t ctlTime;           /**<  ��ʱ��  */
    uint32_t curCount;          /**<  �����ڼ���  */
    uint32_t sumCount;          /**<  ��ʱ�����  */
    uint8_t enable;             /**<  ʹ��  */
    uint8_t valid_enable;       /**<  �Ƿ���Ч��true��ʾ��Ч������ʹ�ã�false��ʾ��Ч�����Է���  */
    uint8_t ioCtl;              /**<  ���Ʊ仯��־  */
    uint16_t index;             /**<  ���  */
    IOOUTCALLBACK handle;       /**<  ����ָ��  */
} ioout_t;


/* constants --------------------------------------------------------*/
/* variables --------------------------------------------------------*/

/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/
void ioout_config(void);
ioout_err_t ioout_init(ioout_id_t ioout_id,IOOUTCALLBACK timproc);
ioout_err_t ioout_set(ioout_id_t ioout_id,uint32_t interval,uint32_t workTime,uint32_t ctltime);
ioout_err_t ioout_stop(ioout_id_t ioout_id);
ioout_err_t ioout_start(ioout_id_t ioout_id);
ioout_err_t ioout_pause(ioout_id_t ioout_id);
ioout_err_t ioout_kill(ioout_id_t ioout_id);
void ioout_callback_process(void);

void ioout_port_init(void);

#ifdef __cplusplus
}
#endif

#endif  /*__IOOUT_H*/

