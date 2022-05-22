#include <stdint.h>
#include "stdbool.h"
extern  int x ;
extern  bool isPlay ;
extern  bool isPaused ;
extern char buffer [5];

void EdgeCounter_Init(void);
void GPIOPortF_Handler(void);
