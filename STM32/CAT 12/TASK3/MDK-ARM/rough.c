int main(void)
{
	int pressed=0;
	uint32_t  press_start;
	int isBlinking=0;
	uint32_t  blink_start;
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  while (1)
  {
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET) {
			if(pressed==0) {
				pressed=1;
				press_start=HAL_GetTick();
			}
		}
		else {
			if(pressed==1) {
				pressed=0;
				if(HAL_GetTick()-press_start<1000) {
					if(isBlinking==0) {
						HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
					}
					else {
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
						isBlinking=0;
					}
				}
				else {
					if(isBlinking==0) {
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
						isBlinking = 1;
						blink_start=HAL_GetTick();
					}
				}
			}
		}
		if(isBlinking==1) {
			if(HAL_GetTick() - blink_start >=100) {
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
						blink_start=HAL_GetTick();
			}
		}
  }
}