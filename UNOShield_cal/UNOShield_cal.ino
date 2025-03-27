#include <Arduino.h>
#include "include/AcquaShield.h"

pHShield Shield_pH; //Instancia a variável "pHShield".
ODShield Shield_OD; //Instancia a variável "ODShield".
ECShield Shield_EC; //Instancia a variável "ECShield".


void setup() 
{
    Serial.begin(9600);   //Inicializa a UART do Arduino.
    Shield_pH.init();     //Inicializa o Shield de pH.
    Shield_OD.init();     //Inicializa o Shield de OD.
    Shield_EC.init();     //Inicializa o Shield de EC.


    od_type = mgl;        //iicializa variável externa para indicar tipo de impressão de OD


    delay(1000);
    Shield_pH.DispBuffClear();                      //Limpa o buffer do display do Shield de pH.
    Shield_OD.DispBuffClear();                      //Limpa o buffer do display do Shield de OD.
    Shield_EC.DispBuffClear();                      //Limpa o buffer do display do Shield de EC.


    Shield_pH.DispWrite(3, 13, 21, "Acquanativa");  //Envia a string para o buffer do display do Shield de pH.
    Shield_OD.DispWrite(3, 13, 21, "Acquanativa");  //Envia a string para o buffer do display do Shield de OD.
    Shield_EC.DispWrite(3, 13, 21, "Acquanativa");  //Envia a string para o buffer do display do Shield de EC.


    Shield_pH.DispShow();                           //Mostra a string no display do Shield de pH.
    Shield_OD.DispShow();                           //Mostra a string no display do Shield de OD.
    Shield_EC.DispShow();                           //Mostra a string no display do Shield de EC.


    delay(1000); 
}

void loop() 
{
    static char vetor_temp[5];             //Vetor para armazenar a string de temperatura do Shield de pH.
    static char vetor_pH[5];               //Vetor para armazenar a string de pH do Shield de pH.
    static char vetor_OD[12];               //Vetor para armazenar a string de EC do Shield de EC.

    static char vetor_EC[12];               //Vetor para armazenar a string de EC do Shield de EC.

    static unsigned int previous_mod = 0;  //Variável para contagem do tempo de loop.
    
    float od = 0.0;
    float ec = 0.0;
    float tds_value = 0.0;

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
        
        Shield_OD.DispBuffClear();      //Limpa o buffer do display do Shield de OD.
        
        if(od_type == mgl)
        {
            od = Shield_OD.OD();                       //Faz a leitura do valor de OD do Shield.

            if(od < 10.0)
            {
                dtostrf(od, 2, 1, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
                strcpy(vetor_OD, vetor_OD);                //Deixa a String no formato correto para ser mostrada no display do Shield de OD.     
                Shield_OD.DispWrite(4, 6, 16, "OD:");      //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD. 
                Shield_OD.DispWrite(4, 49, 16, vetor_OD);  //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de OD, para o buffer do display do Shield de OD. 
                Shield_OD.DispWrite(2, 96, 16, "mg/L");    //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.  
            }
            else
            {

                dtostrf(od, 2, 1, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
                strcpy(vetor_OD, vetor_OD);                //Deixa a String no formato correto para ser mostrada no display do Shield de OD.     
                Shield_OD.DispWrite(4, 6, 16, "OD:");      //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD. 
                Shield_OD.DispWrite(4, 49, 16, vetor_OD);  //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de OD, para o buffer do display do Shield de OD. 
                Shield_OD.DispWrite(2, 105, 16, "mg/L");    //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.  
            }

        } 
        else
        {
            od = Shield_OD.ODsat();  

            Shield_OD.DispWrite(4, 6, 16, "OD:");           //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.  
   
            if(od < 10.0)
            {
                dtostrf(od, 2, 1, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
                strcpy(vetor_OD, vetor_OD);
                Shield_OD.DispWrite(4, 49, 16, vetor_OD);
                Shield_OD.DispWrite(2, 100, 16, "%");            //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.  

            }
            else if((od >= 10.0) & (od <= 99.9))
            {
                dtostrf(od, 2, 1, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
                strcpy(vetor_OD, vetor_OD);
                Shield_OD.DispWrite(4, 49, 16, vetor_OD);
                Shield_OD.DispWrite(2, 110, 16, "%");            //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.  
  
            }
            else
            {
                dtostrf(od, 3, 0, vetor_OD);               //Faz a leitura do OD e converte a variável float "OD" em string.
                strcpy(vetor_OD, vetor_OD);
                Shield_OD.DispWrite(4, 49, 16, vetor_OD);
                Shield_OD.DispWrite(2, 105, 16, "%");            //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.   
      
            } 

        }      

        dtostrf(Shield_OD.temp(), 2, 1, vetor_temp);  //Faz a leitura da temperatura e converte a variável float "temp" em string.
        strcpy(vetor_temp, vetor_temp);               //Deixa a String no formato correto para ser mostrada no display do Shield de OD.
        Shield_OD.DispWrite(1, 7, 32, "Temp:");       //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia a string para o buffer do display do Shield de OD.
        Shield_OD.DispWrite(1, 40, 32, vetor_temp);   //.DispWrite(Fonte(1 a 4), x, y, string); -> Envia o vetor de string, com o valor de temperatura, para o buffer do display do Shield de OD.
    
        Shield_OD.DispShow();                         //Mostra a string no display do Shield de OD.   

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