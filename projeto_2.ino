#include "Arduino.h"
#include "botoes.h"
#include "controles.h"
#include "heart_beat.h"
#include "lcd_telas.h"
#include "lm35.h"

void setup()
{
  inicianiza_botoes();
  ini_trat_botoes();
  inicia_controlador();
  inicializa_lcd();
}

void loop()
{
  funcao_principal();
}

