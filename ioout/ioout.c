/**
  * @file       ioout.c
  * @brief      IO�������
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-09
  *
  * @note
  * [2016-08-09] <redoc> v1.0
  * ��ʼ�汾
  * [2017-08-16] <redoc> v2.0
  * 1.���IO���ã���ֱ�ӵ���
  * [2017-08-23] <redoc> v3.0
  * 1.��������������c���ļ�
  * 2.���Ĳ��ֺ���������
  * [2017-08-29] <redoc> v3.1
  * 1.��Ӻ���ָ���ж�
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "ioout.h"
#include "gpio.h"


/* typedef -----------------------------------------------------------*/
/* define ------------------------------------------------------------*/
/* constants ---------------------------------------------------------*/
const uint16_t ioout_Time_Interval = 10;            /**< ��ѯ���    */


/* variables ---------------------------------------------------------*/
static ioOut_Typedef m_nIoOutList[IOOUT_MAX];       /**<  IO�����   */
static uint16_t iooutIdBuf[IOOUT_MAX] ;             /**<  IOID��   */
static uint8_t iooutInitFlag = false;                  /**<  ioout��ʼ����־   */

/* functions ---------------------------------------------------------*/
static void ioout_ListInit(void);
static iooutErrCode_Typedef ioout_GetIOIndex(uint16_t *sIndex);
static iooutErrCode_Typedef ioout_SetUnlinkIO(uint16_t index);
static iooutErrCode_Typedef ioout_LinkToIO(uint16_t index,IOOUTCALLBACK handle);
static iooutErrCode_Typedef ioout_SetStartIO(uint16_t index);
static iooutErrCode_Typedef ioout_KillIO(uint16_t *sIndex);
static iooutErrCode_Typedef ioout_SetStopIO(uint16_t index);
static iooutErrCode_Typedef ioout_SetPauseIO(uint16_t index);
static iooutErrCode_Typedef ioout_SetParmIO(uint16_t index,uint32_t interval,uint32_t beeptime,uint32_t ctltime);

/**
  * @brief	����ioout
  * @param	void
  *
  * @return	void
  * @remark
  */
void ioout_Config(void)
{
    ioout_ListInit();

    /*--------------- ��ֲ����Start */

    if(IOOUT_NO_ERR != ioout_Init(ID_IOOUT_LED0,GPIO_SetLed0))
    {
    	//do something
    }

    if(IOOUT_NO_ERR != ioout_Init(ID_IOOUT_LED1,GPIO_SetLed1))
    {
        //do something
    }

    /*--------------- ��ֲ����End */
}

/**
  * @brief	IO������ʼ��
  * @param	��
  *
  * @return	��
  * @remark
  */
static void ioout_ListInit(void)
{
    uint16_t i = 0;

    for(i = 0; i < IOOUT_MAX; i++)
    {
        m_nIoOutList[i].interval        = 0;
        m_nIoOutList[i].workTime        = 0;
        m_nIoOutList[i].ctlTime         = 0;
        m_nIoOutList[i].curCount        = 0;
        m_nIoOutList[i].sumCount        = 0;
        m_nIoOutList[i].handle          = NULL;
        m_nIoOutList[i].enable          = false;
        m_nIoOutList[i].valid_enable    = false;
        m_nIoOutList[i].ioCtl           = false;
        m_nIoOutList[i].index           = 0xFFFF;
        iooutIdBuf[i]                   = 0xFFFF;
    }

    iooutInitFlag = true;
}

/**
  * @brief	���Ӷ�Ӧ���IO�Ĳ��ݺ���
  * @param	index��IO�����
  * @param	handle�����Ӻ���
  *
  * @return	����״̬
  * @remark
  */
static iooutErrCode_Typedef ioout_LinkToIO(uint16_t index,IOOUTCALLBACK handle)
{
    if(index > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    if(handle == NULL)
    {
        return IOOUT_ERR_PARAM;
    }

    m_nIoOutList[index].handle = handle;
    m_nIoOutList[index].valid_enable     = true;

    return IOOUT_NO_ERR;
}

/**
  * @brief	������index
  * @param	index��IO�����
  *
  * @return	����״̬
  * @remark
  */
static iooutErrCode_Typedef ioout_SetUnlinkIO(uint16_t index)
{
    if(index > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }


    m_nIoOutList[index].handle(false);
    m_nIoOutList[index].interval 		= 0;
    m_nIoOutList[index].workTime        = 0;
    m_nIoOutList[index].ctlTime 		= 0;
    m_nIoOutList[index].curCount    	= 0;
    m_nIoOutList[index].sumCount   	 	= 0;
    m_nIoOutList[index].handle      	= NULL;
    m_nIoOutList[index].index       	= 0xFFFF;
    m_nIoOutList[index].ioCtl         	= false;
    m_nIoOutList[index].enable      	= false;
    m_nIoOutList[index].valid_enable    = false;

    return IOOUT_NO_ERR;
}

/**
  * @brief	��ȡ���ƿڵ����
  * @param	*mindex��IO�����(����)
  *
  * @return	����״̬
  * @remark
  */
static iooutErrCode_Typedef ioout_GetIOIndex(uint16_t *sIndex)
{
    uint16_t i = 0;

    for(i = 0; i < IOOUT_MAX; i++)
    {
        if(false == m_nIoOutList[i].valid_enable)
        {
            *sIndex = i;
            return IOOUT_NO_ERR;
        }
    }

    return IOOUT_ERR_FAIL;
}

/**
  * @brief	�����ͻָ���Ӧ��ŵ�IO
  * @param	index��IO�����
  *
  * @return	����״̬
  * @remark
  */
static iooutErrCode_Typedef ioout_SetStartIO(uint16_t index)
{
    if(index == 0xFFFF)
    {
        return IOOUT_ERR_INIT;
    }

    if(false == m_nIoOutList[index].enable)
    {
        m_nIoOutList[index].enable     = true;
    }

    return IOOUT_NO_ERR;
}


/**
  * @brief	ɾ����Ӧ��ŵ�IO
  * @param	index��IO�����
  *
  * @return	����״̬
  * @remark	���ɻָ����ͷ���Դ
  */
static iooutErrCode_Typedef ioout_KillIO(uint16_t *sIndex)
{
    if(*sIndex == 0xFFFF)
    {
        return IOOUT_ERR_INIT;
    }

    ioout_SetUnlinkIO(*sIndex);
    *sIndex = 0xffff;

    return IOOUT_NO_ERR;
}

/**
  * @brief	ֹͣ��Ӧ��ŵ�IO
  * @param	index��IO�����
  *
  * @return	����״̬
  * @remark	���ͷ���Դ��������ǰ���񣬲��ɻָ�
  */
static iooutErrCode_Typedef ioout_SetStopIO(uint16_t index)
{
    if(index == 0xFFFF)
    {
        return IOOUT_ERR_INIT;
    }


    m_nIoOutList[index].handle(false);

    m_nIoOutList[index].interval 		= 0;
    m_nIoOutList[index].workTime 	    = 0;
    m_nIoOutList[index].ctlTime 		= 0;
    m_nIoOutList[index].curCount    	= 0;
    m_nIoOutList[index].sumCount   	 	= 0;
    m_nIoOutList[index].enable      	= false;

    return IOOUT_NO_ERR;
}
/**
  * @brief	��ͣ��Ӧ��ŵ�IO
  * @param	index��IO�����
  *
  * @return	����״̬
  * @remark	��ͣ��ǰ���񣬻ָ�������ǰ����
  */
static iooutErrCode_Typedef ioout_SetPauseIO(uint16_t index)
{
    if(index == 0xFFFF)
    {
        return IOOUT_ERR_INIT;
    }

    m_nIoOutList[index].handle(false);
    m_nIoOutList[index].enable     = false;

    return IOOUT_NO_ERR;
}

/**
  * @brief	���ö�Ӧ���IO����
  * @param	index��IO�����
  * @param	interval�����ʱ��
  * @param	worktime������ʱ��
  * @param	ctltime����ʱ��
  *
  * @return	iooutErrCode_Typedef
  * @remark msΪ��λ,���������ǲ�ѯʱ������������˺���������worktimeΪ��
  */
static iooutErrCode_Typedef ioout_SetParmIO(uint16_t index,uint32_t interval,uint32_t workTime,uint32_t ctltime)
{
    if(index == 0xFFFF)
    {
        return IOOUT_ERR_INIT;
    }

    if(((interval % ioout_Time_Interval ) != 0 )
    || ((interval % ioout_Time_Interval ) != 0 )
    || ((interval % ioout_Time_Interval ) != 0 ))
    {
        return IOOUT_ERR_PARAM;
    }

    if(0 == workTime)
    {
        return IOOUT_ERR_PARAM;
    }

    m_nIoOutList[index].interval 		= interval;
    m_nIoOutList[index].workTime	    = workTime;
    m_nIoOutList[index].ctlTime			= ctltime;
    m_nIoOutList[index].sumCount    	= 0;
    m_nIoOutList[index].enable       	= true;

    return IOOUT_NO_ERR;
}

/**
  * @brief	��ʼ��IOOUTʹ�ýӿں���
  * @param	timproc��IO�ڽӿں���
  *
  * @return	IO�ں�
  * @remark
  */
iooutErrCode_Typedef ioout_Init(iooutId_Typedef iooutId,IOOUTCALLBACK timproc)
{
    if(false == iooutInitFlag)
    {
        return IOOUT_ERR_INIT;
    }

    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    if(timproc == NULL)
    {
        return IOOUT_ERR_PARAM;
    }

    if(IOOUT_NO_ERR != ioout_GetIOIndex((uint16_t *)(iooutIdBuf + (uint8_t)iooutId)))
    {
        return IOOUT_ERR_FAIL;
    }

    if(IOOUT_NO_ERR != ioout_LinkToIO(iooutIdBuf[iooutId],timproc))
    {
        return IOOUT_ERR_FAIL;
    }

    return IOOUT_NO_ERR;
}

/**
  * @brief	����IO������
  * @param	iooutId:�����ID
  * @param	interval�����ʱ��
  * @param	worktime������ʱ��
  * @param	ctltime����ʱ��
  *
  * @return	iooutErrCode_Typedef
  * @remark ʱ����msΪ��λ,���������ǲ�ѯʱ�����������worktimeΪ0ֹͣ��ctltimeΪ0һֱ��������
  */
iooutErrCode_Typedef ioout_Set(iooutId_Typedef iooutId,uint32_t interval,uint32_t workTime,uint32_t ctlTime)
{
    iooutErrCode_Typedef status;

    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    if(workTime != 0)
    {
        status == ioout_SetParmIO(iooutIdBuf[iooutId],interval,workTime,ctlTime);

        if(IOOUT_NO_ERR == status)
        {
            ioout_SetStartIO(iooutIdBuf[iooutId]);
        }
        else
        {
            return status;
        }
    }
    else
    {
        ioout_SetStopIO(iooutIdBuf[iooutId]);
    }

    return IOOUT_NO_ERR;
}

/**
  * @brief	ֹͣ,��������
  * @param	iooutId:�����ID
  *
  * @return	iooutErrCode_Typedef
  * @remark
  */
iooutErrCode_Typedef ioout_Stop(iooutId_Typedef iooutId)
{
    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    return ioout_SetStopIO(iooutIdBuf[iooutId]);
}

/**
  * @brief	����
  * @param	iooutId:�����ID
  *
  * @return	iooutErrCode_Typedef
  * @remark
  */
iooutErrCode_Typedef ioout_Start(iooutId_Typedef iooutId)
{
    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    return ioout_SetStartIO(iooutIdBuf[iooutId]);
}

/**
  * @brief	��ͣ�����ݲ�����
  * @param	iooutId:�����ID
  *
  * @return	iooutErrCode_Typedef
  * @remark
  */
iooutErrCode_Typedef ioout_Pause(iooutId_Typedef iooutId)
{
    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    return ioout_SetPauseIO(iooutIdBuf[iooutId]);
}

/**
  * @brief	ɾ��
  * @param	iooutId:�����ID
  *
  * @return	iooutId
  * @remark ������ʹ��
  */
iooutErrCode_Typedef ioout_Kill(iooutId_Typedef iooutId)
{
    int16_t id;

    if(iooutId > IOOUT_MAX)
    {
        return IOOUT_ERR_MAX;
    }

    id = iooutId;

    return ioout_KillIO((uint16_t *)(iooutIdBuf + id));
}


/**
  * @brief	IO���ƿڴ�����
  * @param	��
  *
  * @return	��
  * @remark
  */
void ioout_CallBackProcRoutine(void)
{
    const uint16_t xfer_count = ioout_Time_Interval;
    uint8_t i;

    for(i = 0;i < IOOUT_MAX;i++)
    {
        /*  IO�ں�δʹ��  */
        if(m_nIoOutList[i].valid_enable && !m_nIoOutList[i].enable)
        {
            m_nIoOutList[i].handle(false);
            m_nIoOutList[i].sumCount     = 0;
            continue;
        }

        /*  IO�ں�ʹ��  */
        if(m_nIoOutList[i].valid_enable && m_nIoOutList[i].enable)
        {
            /*  �޼��   */
            if(0 == m_nIoOutList[i].interval)
            {

                m_nIoOutList[i].handle(true);

                /*  ��ʱ  */
                if(m_nIoOutList[i].ctlTime)
                {
                    m_nIoOutList[i].sumCount += xfer_count;

                    if(m_nIoOutList[i].sumCount >= m_nIoOutList[i].ctlTime)
                    {
                        m_nIoOutList[i].handle(false);
                        m_nIoOutList[i].sumCount	= 0;
                        m_nIoOutList[i].ioCtl		= false;
                        m_nIoOutList[i].enable      = false;

                    }
                }
            }
            /*  �м��   */
            else
            {
                m_nIoOutList[i].sumCount += xfer_count;

                /*  ��ʱ��  */
                if(m_nIoOutList[i].ctlTime)
                {
                    if(m_nIoOutList[i].sumCount >= m_nIoOutList[i].ctlTime)
                    {
                        m_nIoOutList[i].handle(false);
                        m_nIoOutList[i].sumCount = 0;
                        m_nIoOutList[i].enable = false;
                        m_nIoOutList[i].ioCtl = false;
                        m_nIoOutList[i].curCount = 0;
                        continue;
                    }
                }
                else
                {
                	m_nIoOutList[i].sumCount=0;
                }

                m_nIoOutList[i].curCount += xfer_count;
                m_nIoOutList[i].handle(m_nIoOutList[i].ioCtl);

                /*  ����ʱ��  */
                if(true == m_nIoOutList[i].ioCtl)
                {
                    if(m_nIoOutList[i].curCount >= m_nIoOutList[i].workTime)
                    {
                        m_nIoOutList[i].handle(false);
                        m_nIoOutList[i].ioCtl = false;
                        m_nIoOutList[i].curCount = 0;
                    }
                }
                /*  ���ʱ��  */
                else
                {
                    if(m_nIoOutList[i].curCount >= m_nIoOutList[i].interval)
                    {
                        m_nIoOutList[i].handle(true);
                        m_nIoOutList[i].ioCtl = true;
                        m_nIoOutList[i].curCount = 0;
                    }
                }

            }

        }
    }
}



