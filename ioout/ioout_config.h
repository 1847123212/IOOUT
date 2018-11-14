/**
  * @file       ioout_config.h
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

#ifndef __IOOUT_CONFIG_H
#define __IOOUT_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

/**
  * @brief IO�������ID
  */
typedef enum
{

    ID_IOOUT_LED1=0,
	ID_IOOUT_LED2,

	ID_IOOUT_NUM,
}ioout_id_t;

/**
  * @brief IO��������������Ͷ���
  */
typedef enum
{
    IOOUT_MAX = (ID_IOOUT_NUM),

}ioout_index_num_t;



/* constants --------------------------------------------------------*/
/* variables --------------------------------------------------------*/

/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif  /*__IOOUT_H*/

