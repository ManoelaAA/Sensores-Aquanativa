/***********************************************************************************************************************************************************
Exemplo de utilização da library AcquaShield com o Shield de EC, este exemplo mostra como realizar a leitura de EC e temperatura do Shield, realizar o procedimento
de calbração do eletrodo de EC (K1.0), fazer a leitura dos parâmetros de calibração e mostrar dados no display do Shield de EC.

******** Procedimento de calibração do eletrodo de pH: ********
** Abra o "Serial Monitor" do Arduino.
-> Envie o comando #ECCal#
** O Shield retornará "Procedimento de calibração iniciado...".
** O Shield começará a enviar as leituras de tensão do circuito.
** Mantenha o eletrodo de EC em contato com o Ar e aguarde a leitura estabilizar. 
-> Envie o comando #Cal,dry#
<- O Shield deve retornar *OK
** Este comando faz a calibração inicial do sensor na condição de contato com o Ar.

** Separe as soluções de calibração (84uS/cm e 1413uS/cm).

** Coloque o eletrodo, inicialmente, na solução de 84uS/cm.
** O Shield começará a enviar as leituras de EC, aguarde a leitura se estabilizar.
-> Envie o comando #Cal,lo#
<- O Shield deverá retornar *OK.
** Lave o eletrodo em água destilada ou em solução própria.
** Na sequência repita o procedimento acima com a solução de 1413uS/cm 
-> Envie ocomando #Cal,hi#
** Ao finalizar o procedimento de calibração, a leitura deverá convergir para o valor da solução de teste (1413uS/cm).
**
** OBSERVAÇÂO: Durante o processo de calibraçao, o sistema realiza a compensação de temperatura automaticamente. Portanto,
**             é fundamentalque que se mantenha o sensor de temperatura na mesma solução do eletrodo durante a calibração.
**             Somente após a calibração completa é que o usuário observará a convergência das leituras, no terminal, para
**             o valor da solução (1413uS/cm), caso a temperatura seja de 25°C.
**             Como a compensação durante a calibração é automática, variação de 2% de  uS/cm/°C poderá ser observada.

-> Envie o comando F
** O Shield retornará "Roina de calibração finalizada."
** Reinicie o sistema (Arduino + Shield).
** Pronto, o Shield de EC está calibrado.

*************  Leituras dos parâmetros ************************
** O Shield_EC é capaz de fazer a leitura de:
>>>>> Condutividade Elétrica (EC) [uS/cm], Range: 0 - 5200uS/cm
>>>>> TDS [ppm].
>>>>> Salinidade [ppt].
>>>>> Temperatura [°C].

** A compensação de temperatura na leitura de EC pode ser habilitada (#ECEComp#) ou desabilitada (#ECDComp#). O equipamento
** tem a compensação habilitada de fábrica e seu ultimo estado (#ECSTComp#) é armazenado em memória não volátil.
**
** O Coeficiente de temperatura para compensação da leitura de EC pode ser ajustado pelo usuário (#ECSFCompx.xx#) entre 0 - 2.55 
** [% uS/cm/°C]. O valor de fábrica é 2.0 % uS/cm/°C. Deve-se ressaltar que o Coeficiente de Temperatura do processo de calibração
** também é 2.0 % uS/cm/°C, mas este não é ajustável pois segue as propriedades físicas das soluções de calibração. A referencia de 
** temperatura para a compensação da leitura em ambos os casos é 25°C.
**
** O fator de conversão de TDS (fts) pode ser ajustado pelo usuário (#ECFtds#) entre 0 - 2.55, sendo que TDS = fts*EC. O ajuste do
** valor do fator de convesão é armazenado em memória não volátil. O valor de fábrica para o fator de conversão é de 0.65.
**
** Comandos adicionais podem ser consultados a seguir.
**

******** Comandos para retorno dos dados do eletrodo de EC ********
** Abra o "Serial Monitor" do Arduino.
-> Comando para retornar o valor de Offset do eletrodo de EC:
   #ECDry# -> O Shield retornará o valor de Offset do eletrodo.

-> Comando para retornar o Slope e Coeficiente Linear da curva de calibração do sensor.
   #ECParam# -> O Shield retornará o valor do Sloope e Coeficiente Linear.

-> Comando para retornar o valor da temperatura de calibração do Shield.
   #ECCatmp# -> Retorna o valor da temparatura no momento da calibração do Shield (Tcal).

-> Comando para apagar a calibração do Shield
   #ECCeras# -> Este comando apaga a ultima calibração realizada e coloca os valores de calibração default.

-> Comandos para alterar segunda variável do display:
   #ECTds#     -> Imprime o valor de TDS [ppm] no campo secundário do display
   #ECSalin#   -> Imprime o valor de Salinidade [ppt] no campo secundário do display
   #ECTemp#    -> Imprime o valor de Temperatura [°C] no campo secundário do display (Default)

-> Comando para retornar o fator de conversao TDS:
   #ECFtds# -> Retorna o valor do Fator de conversão de TDS

-> Comando para Setar um novo valor para o Fator de conversao TDS:
   #ECSFtdsx.xx -> Seta valor para x.xx. Range: 0 - 2.55

-> Comando para Resetar o Fator de Conversao TDS para o valor default:
   #ECRFtds#   -> Reseta o fator de conversão para 0.65

-> Comando para habilitar a compnesação de temperatura:
   #ECEComp#   -> Habilita a compensação de temperatura com referencia a 25°C

-> Comando para desabilitar a compesação de temperatura:
   #ECDComp#   -> Desabilita a compensação de temperatura

-> Comando para retornar o estado da compensação de temperatura
   #ECSTComp#  -> Retorna o estado da compensação de temperatura (Habilitada/Desabilitada)

-> Comando para retornar o valor do Coeficiente de temperatura:
   #ECFComp#   -> Retorna o valor do coeficiente [% uS/cm/°C]

-> Comando para setar um novo valor do Coeficiente de temperatura:
   #ECSFCompx.xx#  -> Define um novo valor para o coeficiente de temperatura. Range: 0 - 2.55 [% uS/cm/°C]

-> Comando para resetar o Coeficiente de temperatura para o valor default:
   #ECRFComp#  -> Reseta o valor do Coeficiente de temperatura para o valor default 2.0 [% uS/cm/°C]

** Firmware desenvolvido para Arduino UNO **
** Acquanativa **
** 19/07/2022 **
***********************************************************************************************************************************************************/

#include <Arduino.h>
#include "include/AcquaShield.h"

ECShield Shield_EC; //Instancia a variável "ECShield".

void setup() 
{
    Serial.begin(9600);   //Inicializa a UART do Arduino.
    Shield_EC.init();     //Inicializa o Shield de EC.

    delay(1000);
    Shield_EC.DispBuffClear();                      //Limpa o buffer do display do Shield de EC.
    Shield_EC.DispWrite(3, 13, 21, "Acquanativa");  //Envia a string para o buffer do display do Shield de EC.
    Shield_EC.DispShow();                           //Mostra a string no display do Shield de EC.
    delay(1000); 
}

void loop() 
{
    static char vetor_temp[6];             //Vetor para armazenar a string de temperatura do Shield de EC.
    static char vetor_EC[12];               //Vetor para armazenar a string de EC do Shield de EC.
    static unsigned int previous_mod = 0;  //Variável para contagem do tempo de loop.

    float ec = 0.0;
    float tds_value = 0.0;
       
    if(millis() - previous_mod >= 1000)
    {     

      Shield_EC.DispBuffClear();                 //Limpa o buffer do display do Shield de EC.
      
      ec = Shield_EC.EC();                      //recebe a leitura de EC do Shield_EC
      
      //verifica a magnitude para definir o numero de casas decimais
      if(ec < 100)
         dtostrf(ec, 5, 2, vetor_EC);   //Faz a leitura de Condutividade Eletrica e converte a variável float "EC" em string.
      else if (ec < 1000)
         dtostrf(ec, 5, 1, vetor_EC);
      else
         dtostrf(ec, 4, 0, vetor_EC);

      strcpy(vetor_EC, vetor_EC);                    //Deixa a String no formato correto para ser mostrada no display do Shield de EC.     
      Shield_EC.DispWrite(5, 0, 18, "EC:");          //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de EC. 
      Shield_EC.DispWrite(5, 50, 18, vetor_EC);      //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de EC, para o buffer do display do Shield de EC. 
            

      if(var_type == temperatura)
      {
         dtostrf(Shield_EC.temp(), 2, 1, vetor_temp);  //Faz a leitura da temperatura e converte a variável float "temp" em string.
         strcpy(vetor_temp, vetor_temp);               //Deixa a String no formato correto para ser mostrada no display do Shield de EC.
         Shield_EC.DispWrite(1, 38, 31, "Temp:");      //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de EC.
         Shield_EC.DispWrite(1, 71, 31, vetor_temp);   //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de temperatura, para o buffer do display do Shield de EC.
      }
      else if(var_type == tds)
      {
         tds_value = Shield_EC.Tds();                 //Recebe o valor de TDS do Shield_EC

         //verifica a magnitude para definir o numero de casas decimais        
         if(tds_value < 100)
            dtostrf(tds_value, 3, 2, vetor_temp);     //Converte a variável float "tds_value" em string.
         else if(tds_value < 1000)
            dtostrf(tds_value, 2, 1, vetor_temp);
         else
            dtostrf(tds_value, 2, 0, vetor_temp);
         
         strcpy(vetor_temp, vetor_temp);                 //Deixa a String no formato correto para ser mostrada no display do Shield de EC.
         Shield_EC.DispWrite(1, 38, 31, "TDS:");       //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de EC.
         Shield_EC.DispWrite(1, 68, 31, vetor_temp);     //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de temperatura, para o buffer do display do Shield de EC.
      }
      else if(var_type == salinidade)
      {
         dtostrf(Shield_EC.Salin(), 2, 2, vetor_temp);   //Faz a leitura de salinidade e converte a variável float "temp" em string.
         strcpy(vetor_temp, vetor_temp);                 //Deixa a String no formato correto para ser mostrada no display do Shield de EC.
         Shield_EC.DispWrite(1, 38, 31, "Salin:");       //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de EC.
         Shield_EC.DispWrite(1, 78, 31, vetor_temp);     //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de temperatura, para o buffer do display do Shield de EC.
      }

      Shield_EC.DispShow();                         //Mostra a string no display do Shield de EC.
            
      previous_mod = millis();
    }
}
