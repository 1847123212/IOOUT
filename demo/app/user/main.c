/**
  * @file       main.c
  * @brief      ������
  * @author     redoc <619675912@qq.com>
  * @version    v1.0
  * @date       2017-08-23
  *
  * @note
  * [2016-08-03] <redoc> v1.0
  * ��ʼ�汾
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "bsp.h"
#include "ioout.h"


/* typedef -----------------------------------------------------------*/
/* define ------------------------------------------------------------*/
/* macro -------------------------------------------------------------*/
#define ENABLE_INT()	__ASM volatile("cpsie i")           /* ʹ��ȫ���ж� */
#define DISABLE_INT()	__ASM volatile("cpsid i")           /* ��ֹȫ���ж� */

/* variables ---------------------------------------------------------*/
const uint8_t projectTab[] = {"operation"};                  /**<  ��Ŀ����   */
const uint8_t versionsTab[] = {"V1.1.00beta"};               /**<  �汾��Ϣ   */
const uint8_t userNameTab[] = {"redoc"};                     /**<  �û���     */

/* function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);


/* functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    DISABLE_INT();

    BSP_Init();
    ioout_Config();

    ENABLE_INT();

    ioout_Set(ID_IOOUT_LED0,1000,1000,0);
    ioout_Set(ID_IOOUT_LED1,200,200,0);

    while (1)
    {
        ioout_Pause(ID_IOOUT_LED1);
        HAL_Delay(1000);
        ioout_Start(ID_IOOUT_LED1);
        HAL_Delay(1000);
        ioout_Stop(ID_IOOUT_LED1);
        HAL_Delay(1000);
        ioout_Set(ID_IOOUT_LED1,200,200,2000);
        HAL_Delay(5000);

    }
}

/**
  * @brief      ϵͳʱ������
  * @param      void
  *
  * @return     void
  * @remark
  */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState        = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
}

/**
  * @brief      ϵͳ�ж�����
  * @param      void
  *
  * @return     void
  * @remark
  */
void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* System interrupt init*/
    /* MemoryManagement_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    /* BusFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    /* UsageFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    /* DebugMonitor_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, INT_PRO_SYSTICK, 0);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif



