#include "Arduino.h"
#include "controles.h"
#include "lm35.h"

float tempPadrao;
float ganho = 1;
int manual_HEAT;
int manual_FAN;
int ganho_pwm     = 0;
int estado_heat   = 0;
int estado_fan    = 0;
int estado_driver = 0;

void inicia_controlador()
{
  tempPadrao  = 25.0;
  manual_HEAT = 50;
  manual_FAN  = 50;
  pinMode(HEAT,   OUTPUT);
  pinMode(FAN,    OUTPUT);
  pinMode(ENABLE, OUTPUT);
  analogWrite (HEAT,   0);
  analogWrite (FAN,    0);
  digitalWrite(ENABLE, 0);
}

void calculo_ganho()
{
  ganho_pwm = int((tempPadrao - temperatura) * ganho);
  abs(ganho_pwm);
}

void estado_atual()
{
  if (tempPadrao > temperatura)
  {
    estado_heat = 1;
    estado_fan  = 0;
  }
  else if (tempPadrao < temperatura)
  {
    estado_heat = 0;
    estado_fan  = 1;
  }
  else
  {
    estado_heat = 0;
    estado_fan  = 0;
  }
}

void automatico_heatpwm()
{
	if (ganho_pwm < HEAT_MIN)
	{
	  ganho_pwm = HEAT_MIN;
	  analogWrite(HEAT, ganho_pwm);
	}
	else if (ganho_pwm > HEAT_MAX)
	{
	  ganho_pwm = HEAT_MAX;
	  analogWrite(HEAT, ganho_pwm);
	}
	else
	{
	  analogWrite(HEAT, ganho_pwm);
	}
	analogWrite(FAN , 0);
}

void automatico_fanpwm()
{
	if (ganho_pwm < FAN_MIN)
	{
	  ganho_pwm = FAN_MIN;
	  analogWrite(FAN , ganho_pwm);
	}
	else if (ganho_pwm > FAN_MAX)
	{
	  ganho_pwm = FAN_MAX;
	  analogWrite(FAN , ganho_pwm);
	}
	else
	{
	  analogWrite(FAN, ganho_pwm);
	}
	analogWrite(HEAT, 0);
}
