#include "main.h"
#include <string.h>


extern uint8_t UART_flag;
extern UART_HandleTypeDef huart1;

extern uint8_t UART1_rxBuffer[DATA_LENGTH];


int main(void){
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  UART_Transmit_Message();
  HAL_UART_Receive_IT(&huart1, UART1_rxBuffer, DATA_LENGTH);
  UART_Transmit_Message();
  while (1){
      if(UART_flag == 1){
          HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
          HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
          UART_Transmit_Message();
          HAL_Delay(100);
          HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
          UART_flag = 0;
      }
  }

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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
