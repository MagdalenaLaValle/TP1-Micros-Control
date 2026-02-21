/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;

extern uint8_t flag_100ms, flag_500ms, flag_1s, UART_flag;
extern uint8_t UART1_rxBuffer[DATA_LENGTH];

char tecla_pulsada;

int main(void){
  //LECTURA DEL TECLADO Y LCD
  key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
  char tecla, last_selection = '\0'; //es un char de dos elementos de forma que el elemnto final sea NULL y lcd_send_string lo lea bien
  init_matrix(pressed_matrix);

  //MOTOR
  uint8_t *selected_flag, dead_flag = 0;
  selected_flag = &dead_flag; // originalmente, no hay ningún flag. Sólo es 0

  HAL_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_GPIO_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  //MX_USART1_UART_Init();

  //UART_Transmit_Message();
  //HAL_UART_Receive_IT(&huart1, UART1_rxBuffer, DATA_LENGTH);
  HAL_Delay(100);

  lcd_init();
  lcd_put_cur(0, 0);
  lcd_send_string("hola:");

  while (1){
      /*if(UART_flag == 1){
               HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
               HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
               UART_Transmit_Message();
               HAL_Delay(100);
               HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
               UART_flag = 0;
      }*/

    if (flag_1s==1){ //Con cada pulso del timer, leo la matriz
        //embolo = detectar_embolo();
        leer_matriz(pressed_matrix);
        tecla = get_key_pressed(pressed_matrix);
        if(last_selection != tecla && tecla!= 0){
        	lcd_put_cur(0, 0);
        	lcd_send_string("22:");
            last_selection = tecla;
        }
    }


     switch (last_selection){
            case '1':
                lcd_put_cur(0, 9);
                lcd_send_string("       ");
                lcd_put_cur(0, 9);
                lcd_send_string("1s");
                selected_flag = &flag_1s;
                break;
            case '2':
                lcd_put_cur(0, 9);
                lcd_send_string("       ");
                lcd_put_cur(0, 9);
                lcd_send_string("500ms");
                selected_flag = &flag_500ms;
                break;
            case '3':
                lcd_put_cur(0, 9);
                lcd_send_string("       ");
                lcd_put_cur(0, 9);
                lcd_send_string("100ms");
                selected_flag = &flag_100ms;
                break;
            case 'A':
                lcd_put_cur(0, 9);
                lcd_send_string("       ");
                lcd_put_cur(0, 9);
                lcd_send_string("INVALID");
                selected_flag = &dead_flag;
                break;
     }

    if(*selected_flag==1){
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
    }
    else{
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
    }

  }
}
