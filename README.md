## Controlador Proporcional

* **Descrição geral do Sistema:**

   O controlador proporcional possui uma interface composta por display 16x2 e 4 botões (P | UP | DOWN | S). O controle é feito proporcionalmente e a configuração de alguns parâmetros do sistema é feita através da interface de usuário. Sâo elas:
      * Novo set-point.
      * Valor do ganho do Heat.
      * Valor do ganho do Fan.
      * Se o modo vai ser manual.
      * Ganho manual do Heat.
      * Ganho manual do Fan.
      * Desabilitar o controlador independentemente da temperatura.

<div align="center">
   <img src="diagrama_de_blocos.PNG" alt="diagrama" width="50%" height="20%"/></center>
</div>

* **Funcionamento:**

   O sistema se inicializa na tela de supervisão, com o ganho de valor 15.0 que melhor se ajustou tanto para o FAN quanto para o HEAT. Nela é possível observar o estado atual do controlador, os valores de set-point e o valor da temperatura atual. Ao clicar no botão P, o sistema altera a tela, sendo que existem 6 telas se o modo manual estiver desativado, e 8 telas se estiver ativado. Estando na tela desejada, ao clicar no botão S aparecerá a opção de editar os valores, independente da tela. Para editar alguma configuração de alguma tela, dar um clique simples no botão P (se for editar ON/OFF) ou clicar nos botões UP e DOWN para alterar valores. Para salvar a configuração, clicar no botão S novamente.

* **Periféricos:**
   * **Sensor:** O Sensor de temperatura utilizado é o sensor analógico LM35.
   * **MCU:** O MCU escolhido para o desenvolvimento foi o ATMega328p (Arduino) e ele é o responsável pelas tarefas de controle e interface do sistema. 
   * **Driver:** O driver do controlador é composto um único transistor do tipo MOSFET ligado no componente virtual OVEN do Proteus.
   * **L293D:** Ponte H utilizada para controlar ventilador e aquecedor.
   * **Ventilador:** Utilizado para o modo Fan.
   * **Aquecedor:** Utilizado para o modo Heat.

* **Software:**
   * **IDE:** Foi utilizada Sloeber, IDE do Eclipse para o Arduino.
   * **Bibliotecas utilizadas:** LiquidCrystal e Bounce2.
   * **Definições:** O arquivo */include/definitions.h* contém todas as definições de GPIOs, ID das telas da interface, parâmetros iniciais do controlador e a assinatura dos métodos.
   * **Arquivo .hex:** Ao compilar a aplicação, os arquivos .hex e .elf ficam localizados na pasta **Release**. 

 
* **Fotos:**

<div align="center">
   <img src="proteus.PNG" alt="diagrama" width="50%" height="20%"/></center>
</div>

<div align="center">
   <img src="protoboard.jpeg" alt="diagrama" width="50%" height="20%"/></center>
</div>
