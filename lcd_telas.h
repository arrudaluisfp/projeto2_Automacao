#ifndef LCD_TELAS_H_
#define LCD_TELAS_H_

typedef enum
{
  PRINCIPAL = 0, SET_POINT, GANHO, AQUECEDOR, VENTILADOR, DRIVE
} Estados;

extern int   estado;
extern int   manual_HEATpwm;
extern int   manual_FANpwm;
extern bool  configuracao;

void inicializa_lcd();
void estado_inicial();
void funcao_set_point();
void funcao_ganho();
void aquecedor_m();
void ventilador_m();
void func_drive();
void funcao_principal();

#endif
