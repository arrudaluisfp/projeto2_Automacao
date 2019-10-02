#include "Arduino.h"
#include "botoes.h"
#include "controles.h"
#include "heart_beat.h"
#include "lcd_telas.h"
#include "lm35.h"
#include <LiquidCrystal.h>
#include <Bounce2.h>

LiquidCrystal lcd(12, 11, 4, 3, 2, 1);

int estado = DRIVE, manual_HEATpwm = 0, manual_FANpwm = 0;
bool modo_HEAT = false, modo_FAN = false, configuracao = false;

void inicializa_lcd()
{
  lcd.begin(16, 2);
  pinMode(LM35, INPUT);
  pinMode(HEART_BEAT, OUTPUT);
}

void estado_inicial()
{
  while (estado == PRINCIPAL)
  {
    update_botoes();
    heart_beating();
    lcd.setCursor(0, 0);
    lcd.print("SP: ");
    lcd.print(tempPadrao, 1);
    lcd.setCursor(8, 0);
    lcd.print("C");
    //delay(50);
    Le_temperatura();
    lcd.setCursor(0, 1);
    lcd.print("PV: ");
    lcd.print(temperatura, 1);
    lcd.setCursor(8, 1);
    lcd.print("C");

    if (digitalRead(ENABLE) == LOW)
      estado_driver = 0;
    else
      estado_driver = 1;

    calculo_ganho();
    estado_atual();

    if (estado_driver == 0)
    {
      lcd.setCursor(11, 0);
      lcd.print("Driver");
      lcd.setCursor(12, 1);
      lcd.print("OFF");
    }
    else if (estado_driver == 1 && estado_heat == 0 && estado_fan == 0)
    {
      lcd.setCursor(11, 0);
      lcd.print("Driver");
      lcd.setCursor(12, 1);
      lcd.print("ON ");
    }
    else if (estado_driver == 1 && estado_heat == 1 && estado_fan == 0)
    {
      lcd.setCursor(10, 0);
      lcd.print("  Heat");
      lcd.setCursor(12, 1);
      lcd.print("ON ");
      if (modo_HEAT == false)
      {
    	  automatico_heatpwm();
      }
      else if (modo_HEAT == true)
      {
        manual_HEATpwm = map(manual_HEAT, 0, 100, HEAT_MIN, HEAT_MAX);
        analogWrite(HEAT, manual_HEATpwm);
        analogWrite(FAN, 0);
      }
    }
    else if (estado_driver == 1 && estado_heat == 0 && estado_fan == 1)
    {
      lcd.setCursor(10, 0);
      lcd.print("  Fan ");
      lcd.setCursor(12, 1);
      lcd.print("ON ");
      if (modo_FAN == false)
      {

      }
      else if (modo_FAN == true)
      {
        manual_FANpwm = map(manual_FAN, 0, 100, FAN_MIN, FAN_MAX);
        analogWrite(HEAT, 0);
        analogWrite(FAN, manual_FANpwm);
      }
    }

    if (P_button())
      estado = SET_POINT;
  }
}

void funcao_set_point()
{
  while (estado == SET_POINT)
  {
    heart_beating();
    lcd.setCursor(0, 0);
    lcd.print("New Set Point");
    lcd.setCursor(0, 1);
    lcd.print("SP: ");
    lcd.print(tempPadrao, 1);
    update_botoes();

    if (UP_button())
      tempPadrao += 1;

    if (DOWN_button())
      tempPadrao -= 1;

    if (P_button())
      estado = GANHO;
  }
}

void funcao_ganho()
{
  while (estado == GANHO)
  {
    heart_beating();
    lcd.setCursor(0, 0);
    lcd.print("New Prop. Gain");
    lcd.setCursor(0, 1);
    lcd.print("Kp: ");
    lcd.print(ganho, 1);
    update_botoes();

    if (UP_button())
      ganho += 1;

    if (DOWN_button())
    {
      ganho -= 1;
      if (ganho < 1)
        ganho = 1;
    }

    if (P_button())
      estado = AQUECEDOR;
  }
}

void aquecedor_m()
{
  while (estado == AQUECEDOR)
  {
    heart_beating();
    lcd.setCursor(2, 0);
    lcd.print("Manual Mode");
    lcd.setCursor(0, 1);
    lcd.print("Heat: ");
    update_botoes();

    if (modo_HEAT == true)
    {
      lcd.setCursor(6, 1);
      lcd.print("ON ");
      lcd.setCursor(10, 1);
      lcd.print(manual_HEAT);
      lcd.setCursor(13, 1);
      lcd.print("%");
    }
    else if (modo_HEAT == false)
    {
      lcd.setCursor(6, 1);
      lcd.print("OFF");
      lcd.setCursor(10, 1);
      lcd.print("    ");
    }

    if (UP_button())
      modo_HEAT  = true;

    if (DOWN_button())
      modo_HEAT  = false;

    if (SetPoint_button())
    {
      lcd.setCursor(15, 1);
      lcd.print("<");
      if (modo_HEAT == true)
      {
        configuracao = true;
        while (configuracao == true)
        {
          heart_beating();
          update_botoes();
          if (UP_button())
          {
            manual_HEAT += 5;
            lcd.setCursor(10, 1);
            lcd.print("   ");
            if (manual_HEAT >= 100)
              manual_HEAT = 100;
          }
          if (DOWN_button())
          {
            manual_HEAT -= 5;
            lcd.setCursor(10, 1);
            lcd.print("   ");
            if (manual_HEAT < 0)
              manual_HEAT = 0;
          }
          lcd.setCursor(10, 1);
          lcd.print(manual_HEAT);
          if (SetPoint_button())
          {
            lcd.setCursor(15, 1);
            lcd.print(" ");
            configuracao = false;
          }
        }
      }
    }
    if (P_button())
      estado = VENTILADOR;
  }
}

void ventilador_m()
{
  while (estado == VENTILADOR)
  {
    heart_beating();
    lcd.setCursor(2, 0);
    lcd.print("Manual Mode");
    lcd.setCursor(0, 1);
    lcd.print("Fan: ");
    update_botoes();

    if (modo_FAN == true)
    {
      lcd.setCursor(6, 1);
      lcd.print("ON ");
      lcd.setCursor(10, 1);
      lcd.print(manual_FAN);
      lcd.setCursor(13, 1);
      lcd.print("%");
    }
    else if (modo_FAN == false)
    {
      lcd.setCursor(6, 1);
      lcd.print("OFF");
      lcd.setCursor(10, 1);
      lcd.print("    ");
    }

    if (UP_button())
      modo_FAN  = true;

    if (DOWN_button())
      modo_FAN  = false;

    if (SetPoint_button())
    {
      lcd.setCursor(15, 1);
      lcd.print("<");
      if (modo_FAN == true)
      {
        configuracao = true;
        while (configuracao == true)
        {
          heart_beating();
          update_botoes();
          if (UP_button())
          {
            manual_FAN += 5;
            lcd.setCursor(10, 1);
            lcd.print("   ");
            if (manual_FAN >= 100)
              manual_FAN = 100;
          }
          if (DOWN_button())
          {
            manual_FAN -= 5;
            lcd.setCursor(10, 1);
            lcd.print("   ");
            if (manual_FAN < 0)
              manual_FAN = 0;
          }
          lcd.setCursor(10, 1);
          lcd.print(manual_FAN);
          if (SetPoint_button())
          {
            lcd.setCursor(15, 1);
            lcd.print(" ");
            configuracao = false;
          }
        }
      }
    }
    if (P_button())
      estado = DRIVE;
  }
}

void func_drive()
{
  while (estado == DRIVE)
  {
    heart_beating();
    lcd.setCursor(2, 0);
    lcd.print("Driver Status");
    update_botoes();
    if (digitalRead(ENABLE) == HIGH)
    {
      lcd.setCursor(4, 1);
      lcd.print("Enable ");
    }
    else
    {
      lcd.setCursor(4, 1);
      lcd.print("Disable");
    }

    if (UP_button())
      digitalWrite(ENABLE, HIGH);

    if (DOWN_button())
      digitalWrite(ENABLE, LOW);

    if (P_button())
      estado = PRINCIPAL;
  }
}

void funcao_principal()
{
  switch (estado)
  {
    case PRINCIPAL:
      lcd.clear();
      estado_inicial();
      break;

    case SET_POINT:
      lcd.clear();
      funcao_set_point();
      break;

    case GANHO:
      lcd.clear();
      funcao_ganho();
      break;

    case AQUECEDOR:
      lcd.clear();
      aquecedor_m();
      break;

    case VENTILADOR:
      lcd.clear();
      ventilador_m();
      break;

    case DRIVE:
      lcd.clear();
      func_drive();
      break;
  }
}

