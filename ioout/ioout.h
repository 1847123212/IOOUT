/**
  * @file		ioout.h
  * @brief		IO�������ͷ�ļ�
  * @author 	redoc
  * @version	v1.0
  * @date		2016-08-09
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

#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

/**
  * @brief IO������ƻص��������Ͷ���
  */
typedef void (*IOOUTCALLBACK)(uint8_t);

/*------------ ��ֲ����Start */	
	
/**
  * @brief IO�������ID
  */
typedef enum
{
    ID_IOOUT_LED0 = 0,
	ID_IOOUT_LED1,

} iooutId_Typedef;

/**
  * @brief IO��������������Ͷ���
  */
typedef enum
{
    IOOUT_MAX = (ID_IOOUT_LED1 + 1),

} ioOutIndexNum_Typedef;

/*------------- ��ֲ����End */	


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

}iooutErrCode_Typedef;

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
} ioOut_Typedef;


/* constants --------------------------------------------------------*/
/* variables --------------------------------------------------------*/
/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/
void ioout_Config(void);
iooutErrCode_Typedef ioout_Init(iooutId_Typedef iooutId,IOOUTCALLBACK timproc);
iooutErrCode_Typedef ioout_Set(iooutId_Typedef iooutId,uint32_t interval,uint32_t workTime,uint32_t ctltime);
iooutErrCode_Typedef ioout_Stop(iooutId_Typedef iooutId);
iooutErrCode_Typedef ioout_Start(iooutId_Typedef iooutId);
iooutErrCode_Typedef ioout_Pause(iooutId_Typedef iooutId);
iooutErrCode_Typedef ioout_Kill(iooutId_Typedef iooutId);
void ioout_CallBackProcRoutine(void);

#ifdef __cplusplus
}
#endif

#endif  /*__IOOUT_H*/

