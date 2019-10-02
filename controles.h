#ifndef CONTROLES_H_
#define CONTROLES_H_

#define HEAT   5
#define FAN    6
#define ENABLE 7

#define HEAT_MIN   0
#define HEAT_MAX  35
#define FAN_MIN   56
#define FAN_MAX  255

extern int   estado_heat;
extern int   estado_fan;
extern int   estado_driver;
extern int   manual_HEAT;
extern int   manual_FAN;
extern int   ganho_pwm;
extern float tempPadrao;
extern float ganho;
extern bool  modo_HEAT;
extern bool  modo_FAN;

extern void inicia_controlador();
void calculo_ganho();
void automatico_heatpwm();
void automatico_fanpwm();
void estado_atual();

#endif
