/**************************************************************************************************************************************************************************
Exemplo de utilização da library AcquaShield com o Shield de pH, este exemplo mostra como realizar a leitura de pH e temperatura do Shield, realizar o procedimento
de calbração do eletrodo de pH, fazer a leitura dos parâmetros de calibração (Sloope, offset, etc) e mostrar dados no display do Shield de pH.

******** Procedimento de calibração do eletrodo de pH: ********
** Abra o "Serial Monitor" do Arduino.
-> Envie o comando #pHCal#
** O Shield retornará "Procedimento de calibração iniciado...".
** O Shield começará a enviar as leituras de tensão do circuito.
** Retire o eletrodo de pH do conecor do Shield e coloque um "Jumper" entre os terminais. 
-> Envie o comando #Cal,cc#
<- O Shield deve retornar *OK
** Este comando faz a correção da tensão de offset do circuito eletrônico.
** Retire o jumper do conector do Shield e conecte o eletrodo de pH.
** Separe as soluções de calibração (pH07, pH04 e pH10).

** Coloque o eletrodo, inicialmente, na solução de pH07.
** O Shield começará a enviar as leituras de pH, aguarde cerca de 1 minuto até que a leitura de pH se estabilize.
-> Envie o comando #Cal,07#
<- O Shield deverá retornar *OK.
** Lave o eletrodo em águua destilada ou em solução própria.
** Na sequência repita o procedimento acima com as soluções de pH04(#Cal,04#) e pH10(#Cal,10#), de preferência, nesta ordem.
** Ao finalizar os procedimentos de calibração...

-> Envie o comando F
** O Shield retornará "Rotina de calibração finalizada, reinicie o sistema..."
** Reinicie todo sistema (Arduino + Shield).
** Pronto, seu Shield de pH está calibrado.



******** Comandos para retorno dos dados do eletrodo de pH ********
** Abra o "Serial Monitor" do Arduino.
-> Comando para retornar o valor de Offset do eletrodo de pH:
   #pHOft# -> O Shield retornará o valor de Offset do eletrodo (Valor de referência <= 35mV).

-> Comando para retornar o Sloope entre os valores de pH04 e pH07.
   #pHSlp04# -> O Shield retornará o valor do Sloope (Valor de referência 95% <= Sloope <= 105%).

-> Comando para retornar o Sloope entre os valores de pH10 e pH07.
   #pHSlp10# -> O Shield retornará o valor do Sloope (Valor de referência 95% <= Sloope <= 105%).

-> Comando para retornar o valor da temperatura de calibração do Shield.
   #pHCatmp# -> Retorna o valor da temparatura no momento da calibração do Shield (Tcal).

-> Comando para apagar a calibração do Shield
   #pHCeras# -> Este comando apaga a ultima calibração realizada e coloca os valores de calibração default.

** Firmware desenvolvido para Arduino UNO **
** Acquanativa **
** 28/06/2021 **
***************************************************************************************************************************************************************************/

#include <Arduino.h>
#include "include/AcquaShield.h"

pHShield Shield_pH; //Instancia a variável "pHShield".

void setup() 
{
    Serial.begin(9600);   //Inicializa a UART do Arduino.
    Shield_pH.init();     //Inicializa o Shield de pH.

    delay(1000);
    Shield_pH.DispBuffClear();                      //Limpa o buffer do display do Shield de pH.
    Shield_pH.DispWrite(3, 13, 21, "Acquanativa");  //Envia a string para o buffer do display do Shield de pH.
    Shield_pH.DispShow();                           //Mostra a string no display do Shield de pH.
    delay(1000); 
}

void loop() 
{
    static char vetor_temp[5];             //Vetor para armazenar a string de temperatura do Shield de pH.
    static char vetor_pH[5];               //Vetor para armazenar a string de pH do Shield de pH.
    static unsigned int previous_mod = 0;  //Variável para contagem do tempo de loop.
       
    if(millis() - previous_mod >= 1000)
    {     
        Shield_pH.DispBuffClear();                 //Limpa o buffer do display do Shield de pH.
        
        dtostrf(Shield_pH.pH(), 2, 1, vetor_pH);   //Faz a leitura do pH e converte a variável float "pH" em string.
        strcpy(vetor_pH, vetor_pH);                //Deixa a String no formato correto para ser mostrada no display do Shield de pH.     
        Shield_pH.DispWrite(4, 18, 18, "pH:");     //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de pH. 
        Shield_pH.DispWrite(4, 60, 18, vetor_pH);  //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de pH, para o buffer do display do Shield de pH. 

        dtostrf(Shield_pH.temp(), 2, 1, vetor_temp);  //Faz a leitura da temperatura e converte a variável float "temp" em string.
        strcpy(vetor_temp, vetor_temp);               //Deixa a String no formato correto para ser mostrada no display do Shield de pH.
        Shield_pH.DispWrite(1, 45, 31, "Temp:");      //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de pH.
        Shield_pH.DispWrite(1, 78, 31, vetor_temp);   //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de temperatura, para o buffer do display do Shield de pH.
         
        Shield_pH.DispShow();                         //Mostra a string no display do Shield de pH.
               
        previous_mod = millis();
    }
}
