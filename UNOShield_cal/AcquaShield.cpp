#include "include/AcquaShield.h"
#include <SoftwareSerial.h>


SoftwareSerial mySerial1(3, 2); //RX,TX

SoftwareSerial mySerial2(5, 4); //RX,TX

SoftwareSerial mySerial3(7, 6); //RX,TX


//variável global para definir a variável a ser impressa no display
var_disp var_type = temperatura;

//iniciaiza variavel global para opcao de impressao de OD na unidade mg/L
od_disp od_type = mgl;



pHShield::init()
{
    mySerial1.begin(9600);
}

ODShield::init()
{
    mySerial2.begin(9600);
}

ECShield::init()
{
    mySerial3.begin(9600);
}



/*######################################################################################################################################################
Função responsável por retornar a leitura do sensor de temperatura do AcquaShied_pH.
Esta função retorna um valor float correspondente à leitura em graus celsius do DS18B20.
######################################################################################################################################################*/
float pHShield::temp(void)
{
    mySerial1.listen();
    if(mySerial1.available()) {
        
     float temp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("tmp"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         temp = atof(rx_vetor);     
         return temp;
     }
    }
}

/*######################################################################################################################################################
Função responsável por retornar a leitura do pH do AcquaShield_pH.
Esta função retorna um valor float correspondente à leitura do valor de pH.
######################################################################################################################################################*/
float pHShield::pH(void)
{
    mySerial1.listen();

    if(mySerial1.available()) {
     float ph = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("ph"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ph = atof(rx_vetor);     
         return ph;
     }
    }
}


/*######################################################################################################################################################
Função responsável por escrever uma String no diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void pHShield::DispWrite(char font, int x, int y, char str[])
{
    mySerial1.listen();

    if(mySerial1.available()) {
     unsigned int i = 0;
     
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("dsp");
     delay(10);
     mySerial1.write(font);
     delay(10);
     mySerial1.write(x);  
     delay(10);
     mySerial1.write(y); 
     delay(10);
     mySerial1.write(str); 
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.  
    } 
}

/*######################################################################################################################################################
Função responsável por apagar o buffer do diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void pHShield::DispBuffClear(void)
{   
    mySerial1.listen();

    if(mySerial1.available()) {
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("bff");
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.    
    }
}

/*######################################################################################################################################################
Função responsável por apagar os dados do diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void pHShield::DispClear(void)
{   
    mySerial1.listen();

    if(mySerial1.available()) {
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("clr");
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando. 
    }   
}

/*######################################################################################################################################################
Função responsável por mostras os caracteres no diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void pHShield::DispShow(void)
{    
    mySerial1.listen();

    if(mySerial1.available()) {
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("snd");
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.  
    }  
}

/*######################################################################################################################################################
Função responsável por chamar a rotina de calibração no pH_Shield
######################################################################################################################################################*/
void pH_Cal(void)
{
    mySerial1.listen();

    if(mySerial1.available()) {
    unsigned char uart_byte = 0;        //Recebe o byte recebido pela UART.
    unsigned char serial_byte = 0;      //Recebe o byte recebido pela UART.
    
     
    mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
    delay(10);
    mySerial1.write("Cal");
    delay(10);
    mySerial1.write(0xED);   //Envia o caractere de finalização do comando.   


    while(true) //Aguarda receber o byte de finalização da rotida de calibração do Shield de pH ('F').
    {                  
        if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
        {
            uart_byte = mySerial1.read();
            Serial.write(uart_byte);                            
        }

        if(Serial.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
        {
            serial_byte = Serial.read();   
            mySerial1.write(serial_byte);  
        }
        if(serial_byte == 'F')
        {
            Serial.write("Rotina de calibração finalizada, reinicie o sistema...");
            Serial.println(); 
            while(true)
            { 
                delay(100);
            }
        }
    } 
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor de Offset do eletrodo de pH no pH_Shield
######################################################################################################################################################*/
float pH_offset(void)
{
    mySerial1.listen();

    if(mySerial1.available()) {
     float ph_offset = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("Oft"); //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ph_offset = atof(rx_vetor);     
         return ph_offset;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do Sloope (pH04) do eletrodo de pH no pH_Shield.
######################################################################################################################################################*/
float pH_sloope_04(void) 
{
    mySerial1.listen();

    if(mySerial1.available()) {
     float ph_sl04 = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("Sl04"); //Envia o comando para leitura do sloope pH04 pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ph_sl04 = atof(rx_vetor);     
         return ph_sl04;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do Sloope (pH10) do eletrodo de pH no pH_Shield.
######################################################################################################################################################*/
float pH_sloope_10(void) 
{
    mySerial1.listen();

    if(mySerial1.available()) {
     float ph_sl10 = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("Sl10"); //Envia o comando para leitura do sloope pH04 pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ph_sl10 = atof(rx_vetor);     
         return ph_sl10;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor da temperatura de calibração do Shield de pH.
######################################################################################################################################################*/
float pH_CalTemp(void) 
{
    mySerial1.listen();

    if(mySerial1.available()) {
     float CalTemp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial1.write("Ctmp"); //Envia o comando para leitura do sloope pH04 pelo AcquaShield.
     delay(10);
     mySerial1.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial1.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial1.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         CalTemp = atof(rx_vetor);     
         return CalTemp;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por receber os dados da UART, vindos do Arduino UNO,a tratá-los conforme suas respectivas funções.
Esta função é chamada toda vez que um byte é recebudo pela UART e um buffer é preenchido com os dados para posterior tratamento.
######################################################################################################################################################*/
void serialEvent1(void)
{
    mySerial1.listen();

    if(mySerial1.available()) {
    unsigned char uart_byte = 0;         //Recebe o byte recebido pela UART.
    unsigned char uart_vetor[16];        //Vetor para armazenar os bytes de comando.
    unsigned int cont_comando = 0;       //Contador para indexar o vetor de comando.
    static boolean verif_addr = false;   //Bit para controle de acesso à função de comandos.
    unsigned int i = 0;
    static char vetor_serial[5];
    
    int cont_teste = 0;
    
    while(Serial.available() > 0)  //Aguarda o buffer da UART ser lido totalmente.
    {
        uart_byte = Serial.read();
    
        if((uart_byte == EndCommand)&(verif_addr == true))                               //Verifica se o comando de finalização chegou pela UART.
        {   
            for(i = (cont_comando); i < 16; i++)  
                uart_vetor[i] = '\0';
            
            if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'l')) 
            {
                pH_Cal();
            }       
            else
                if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'O')&(uart_vetor[3] == 'f')&(uart_vetor[4] == 't')) 
                {
                    dtostrf((pH_offset()*1000.0), 2, 1, vetor_serial);
                    strcpy(vetor_serial, vetor_serial);
                    Serial.write("pH Offset: ");
                    Serial.write(vetor_serial);
                    Serial.write("mV");
                    Serial.println();
                }
                else       
                    if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'l')&(uart_vetor[4] == 'p')&(uart_vetor[5] == '0')&(uart_vetor[6] == '4')) 
                    {
                        dtostrf(pH_sloope_04(), 2, 1, vetor_serial);
                        strcpy(vetor_serial, vetor_serial);
                        Serial.write("Sloope pH04: ");
                        Serial.write(vetor_serial);
                        Serial.write("%");
                        Serial.println();
                    }
                    else     
                        if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'l')&(uart_vetor[4] == 'p')&(uart_vetor[5] == '1')&(uart_vetor[6] == '0')) 
                        {
                            dtostrf(pH_sloope_10(), 2, 1, vetor_serial);
                            strcpy(vetor_serial, vetor_serial);
                            Serial.write("Sloope pH10: ");-
                            Serial.write(vetor_serial);
                            Serial.write("%");
                            Serial.println();
                        }
                        else     
                            if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 't')&(uart_vetor[5] == 'm')&(uart_vetor[6] == 'p')) 
                            {
                                dtostrf(pH_CalTemp(), 2, 1, vetor_serial);
                                strcpy(vetor_serial, vetor_serial);
                                Serial.write("Temperatura(Cal): ");
                                Serial.write(vetor_serial);
                                Serial.write("ºC");
                                Serial.println();
                            }
                            else
                                if((uart_vetor[0] == 'p')&(uart_vetor[1] == 'H')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'e')&(uart_vetor[4] == 'r')&(uart_vetor[5] == 'a')&(uart_vetor[6] == 's')) 
                                {
                                    mySerial1.write(0xE6);  //Envia o endereço do AcquaShield_pH pela UART.
                                    delay(10);
                                    mySerial1.write("Cers"); //Envia o comando para leitura do sloope pH04 pelo AcquaShield.
                                    delay(10);
                                    mySerial1.write(0xED);   //Envia o caractere de finalização do comando.   

                                    Serial.write("Calibração pH apagada !");
                                    Serial.println();
                                }
                                else         
                                    Serial.write("Comando não válido !");
            
            verif_addr = false;
            cont_comando = 0;    
        }
        if(verif_addr == true)    //Carrega o vetor da UART enquanto o comando de finalização não chegar.
        {   
            uart_vetor[cont_comando] = uart_byte;
            cont_comando++;  
            if(cont_comando > 16)  //Verifica se os bytes de comando estouraram o contador de comandos.
            {
                Serial.write("Estouro de comando !");
                cont_comando = 0;    
            }
        }
        if((uart_byte == StartCommand) & (verif_addr == false))  //Verifica se o byte recebido corresponde ao endereço do shield pH.
        {
            verif_addr = true;                                   //Ativa o bit de verificação de acesso. 
            cont_comando = 0;
        }
    }
    verif_addr = false;
    cont_comando = 0;   
    for(i = 0; i < 16; i++)
        uart_vetor[i] = '\0';
}
}


/*######################################################################################################################################################
Função responsável por retornar a leitura do sensor de temperatura do AcquaShied_pH.
Esta função retorna um valor float correspondente à leitura em graus celsius do DS18B20.
######################################################################################################################################################*/
float ODShield::temp(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float temp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("tmp"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         temp = atof(rx_vetor);     
         return temp;
     }
    }
}


/*######################################################################################################################################################
Função responsável por retornar a leitura do OD do AcquaShield_OD.
Esta função retorna um valor float correspondente à leitura do valor de OD.
######################################################################################################################################################*/
float ODShield::OD(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float od = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("odmgl"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         od = atof(rx_vetor);     
         return od;
     }
    }
}

/*######################################################################################################################################################
Função responsável por retornar a leitura do OD sat. do AcquaShield_OD.
Esta função retorna um valor float correspondente à leitura do valor de OD sat.
######################################################################################################################################################*/
float ODShield::ODsat(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float odsat = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("odsat"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         odsat = atof(rx_vetor);     
         return odsat;
     }
    }
}



/*######################################################################################################################################################
Função responsável por escrever uma String no diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void ODShield::DispWrite(char font, int x, int y, char str[])
{
    mySerial2.listen();

    if(mySerial2.available()) {
     unsigned int i = 0;
     
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("dsp");
     delay(10);
     mySerial2.write(font);
     delay(10);
     mySerial2.write(x);  
     delay(10);
     mySerial2.write(y); 
     delay(10);
     mySerial2.write(str); 
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.   

     mySerial2.flush();
    }
}

/*######################################################################################################################################################
Função responsável por apagar o buffer do diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void ODShield::DispBuffClear(void)
{    
    mySerial2.listen();

    if(mySerial2.available()) {
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("bff");
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.    
     
     //mySerial2.flush();
    }
}

/*######################################################################################################################################################
Função responsável por apagar os dados do diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void ODShield::DispClear(void)
{    
    mySerial2.listen();

    if(mySerial2.available()) {
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("clr");
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.    
     
     //mySerial2.flush();
    }
}

/*######################################################################################################################################################
Função responsável por mostras os caracteres no diplay 128x32 do AcquaShield_pH
######################################################################################################################################################*/
void ODShield::DispShow(void)
{    
    mySerial2.listen();

    if(mySerial2.available()) {
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("snd");
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.    

     //mySerial2.flush();
    }
}

/*######################################################################################################################################################
Função responsável por chamar a rotina de calibração no pH_Shield
######################################################################################################################################################*/
void OD_Cal(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
    unsigned char uart_byte = 0;        //Recebe o byte recebido pela UART.
    unsigned char serial_byte = 0;      //Recebe o byte recebido pela UART.
    
     
    mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
    delay(10);
    mySerial2.write("Cal");
    delay(10);
    mySerial2.write(0xED);   //Envia o caractere de finalização do comando.   


    while(true) //Aguarda receber o byte de finalização da rotida de calibração do Shield de pH ('F').
    {                  
        if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_OD
        {
            uart_byte = mySerial2.read();
            Serial.write(uart_byte);                            
        }

        if(Serial.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_OD
        {
            serial_byte = Serial.read();   
            mySerial2.write(serial_byte);  
        }
        if(serial_byte == 'F')
        {
            Serial.write("Rotina de calibração finalizada, reinicie o sistema...");
            Serial.println(); 
            while(true)
            { 
                delay(100);
            }
        }
    } 
}
}


/*######################################################################################################################################################
Função responsável por retornar os valores de calibração do Shield de OD.
######################################################################################################################################################*/
/* 
float OD_param(void)
{
     float ph_offset = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_pH pela UART.
     delay(10);
     mySerial2.write("Parm"); //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ph_offset = atof(rx_vetor);     
         return ph_offset;
     }    
}
 */


/*######################################################################################################################################################
Função responsável por retornar o valor de Offset do eletrodo de OD no AcquaShield_OD
######################################################################################################################################################*/
float OD_offset(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float od_offset = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_OD pela UART.
     delay(10);
     mySerial2.write("oft");         //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);          //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_OD
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         od_offset = atof(rx_vetor);     
         return od_offset;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor da tensao do eletrodo de OD no AcquaShield_OD na solução de 0mg/L
######################################################################################################################################################*/
float OD_voltage_0(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float od_v0 = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_OD pela UART.
     delay(10);
     mySerial2.write("v00");         //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);          //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_OD
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         od_v0 = atof(rx_vetor);     
         return od_v0;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor da tensao do eletrodo de OD no AcquaShield_OD na condição de contato com o Ar
######################################################################################################################################################*/
float OD_voltage_Ar(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
     float od_var = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial2.write(ShieldOD_addr);  //Envia o endereço do AcquaShield_OD pela UART.
     delay(10);
     mySerial2.write("var");         //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial2.write(0xED);          //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial2.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_OD
         {
             rx_vetor[contador] = mySerial2.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         od_var = atof(rx_vetor);     
         return od_var;
     }    
    }
}


/*######################################################################################################################################################
Função responsável por receber os dados da UART, vindos do Arduino UNO,a tratá-los conforme suas respectivas funções.
Esta função é chamada toda vez que um byte é recebudo pela UART e um buffer é preenchido com os dados para posterior tratamento.
######################################################################################################################################################*/
void serialEvent2(void)
{
    mySerial2.listen();

    if(mySerial2.available()) {
    unsigned char uart_byte = 0;         //Recebe o byte recebido pela UART.
    unsigned char uart_vetor[16];        //Vetor para armazenar os bytes de comando.
    unsigned int cont_comando = 0;       //Contador para indexar o vetor de comando.
    static boolean verif_addr = false;   //Bit para controle de acesso à função de comandos.
    unsigned int i = 0;
    static char vetor_serial[10];
    
    int cont_teste = 0;
    
    while(Serial.available() > 0)  //Aguarda o buffer da UART ser lido totalmente.
    {
        uart_byte = Serial.read();
    
        if((uart_byte == EndCommand)&(verif_addr == true))                               //Verifica se o comando de finalização chegou pela UART.
        {   
            for(i = (cont_comando); i < 16; i++)  
                uart_vetor[i] = '\0';
            
            if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'l')) 
            {
                OD_Cal();
            }       
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'O')&(uart_vetor[3] == 'f')&(uart_vetor[4] == 't')) 
            {
 
                //Recebe o valor de Offset
                dtostrf((OD_offset()), 2, 0, vetor_serial);
                
                strcpy(vetor_serial, vetor_serial);
                Serial.write("OD Offset: ");
                Serial.write(vetor_serial);
                Serial.write(" mV");
                Serial.println();

                //Serial.flush();
            }
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'V')&(uart_vetor[3] == '0')&(uart_vetor[4] == '0'))
            {

                //Recebe o valor de tensão na solução 00
                dtostrf(OD_voltage_0(), 2, 0, vetor_serial);
                
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Tensao OD Sol. 0 mg/L: ");
                Serial.write(vetor_serial);
                Serial.write(" mV");
                Serial.println();

                //Serial.flush();

            }
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'V')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'r'))
            {
              
                //recebe o valor de tensão no Ar
                dtostrf(OD_voltage_Ar(), 2, 0, vetor_serial);
                
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Tensao OD Ar: ");
                Serial.write(vetor_serial);
                Serial.write(" mV");
                Serial.println();

                //Serial.flush();

            }
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'M')&(uart_vetor[3] == 'g')&(uart_vetor[4] == 'l'))
            {
                od_type = mgl;
            }
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 't'))
            {
                od_type = saturacao;
            }
            else if((uart_vetor[0] == 'O')&(uart_vetor[1] == 'D')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'e')&(uart_vetor[4] == 'r')&(uart_vetor[5] == 'a')&(uart_vetor[6] == 's')) 
            {
                mySerial2.write(ShieldOD_addr); //Envia o endereço do AcquaShield_OD pela UART.
                delay(10);
                mySerial2.write("Cers"); //Envia o comando para leitura do sloope pH04 pelo AcquaShield.
                delay(10);
                mySerial2.write(0xED);   //Envia o caractere de finalização do comando.   

                Serial.write("Calibração OD apagada !");
                Serial.println();
            }
            else         
                Serial.write("Comando não válido !");
            
            verif_addr = false;
            cont_comando = 0;    
        }
        if(verif_addr == true)    //Carrega o vetor da UART enquanto o comando de finalização não chegar.
        {   
            uart_vetor[cont_comando] = uart_byte;
            cont_comando++;  
            if(cont_comando > 16)  //Verifica se os bytes de comando estouraram o contador de comandos.
            {
                Serial.write("Estouro de comando !");
                cont_comando = 0;    
            }
        }
        if((uart_byte == StartCommand) & (verif_addr == false))  //Verifica se o byte recebido corresponde ao endereço do shield pH.
        {
            verif_addr = true;                                   //Ativa o bit de verificação de acesso. 
            cont_comando = 0;
        }
    }
    verif_addr = false;
    cont_comando = 0;   
    for(i = 0; i < 16; i++)
        uart_vetor[i] = '\0';
}
}


/*######################################################################################################################################################
Função responsável por retornar a leitura do sensor de temperatura do AcquaShied_EC.
Esta função retorna um valor float correspondente à leitura em graus celsius do DS18B20.
######################################################################################################################################################*/
float ECShield::temp(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float temp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("tmp"); //Envia o comando para leitura da temperatura pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         temp = atof(rx_vetor);     
         return temp;
     }
    }
}

/*######################################################################################################################################################
Função responsável por retornar a leitura de EC do AcquaShield_EC.
Esta função retorna um valor float correspondente à leitura do valor de EC.
######################################################################################################################################################*/
float ECShield::EC(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float ec = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial3.write(ShieldEC_addr); //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("ec");          //Envia o comando para leitura da condutividade pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ec = atof(rx_vetor);     
         return ec;
     }
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor calculado de Salinidade do AcquaShield_EC.
Esta função retorna um valor float correspondente ao valor de Salinidade.
######################################################################################################################################################*/
float ECShield::Salin(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float salin = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial3.write(ShieldEC_addr); //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("sal");          //Envia o comando para leitura de salinidade pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         salin = atof(rx_vetor);     
         return salin;
     }
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor calculado de TDS do AcquaShield_EC.
Esta função retorna um valor float correspondente ao valor de TDS.
######################################################################################################################################################*/
float ECShield::Tds(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float _tds = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
     
     mySerial3.write(ShieldEC_addr); //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("tds");          //Envia o comando para leitura de salinidade pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.

     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         _tds = atof(rx_vetor);     
         return _tds;
     }
    }
}

/*######################################################################################################################################################
Função responsável por escrever uma String no diplay 128x32 do AcquaShield_EC
######################################################################################################################################################*/
void ECShield::DispWrite(char font, int x, int y, char str[])
{
    mySerial3.listen();

    if(mySerial3.available()) {
     unsigned int i = 0;
     
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("dsp");
     delay(10);
     mySerial3.write(font);
     delay(10);
     mySerial3.write(x);  
     delay(10);
     mySerial3.write(y); 
     delay(10);
     mySerial3.write(str); 
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.   

     mySerial3.flush();
    }
}

/*######################################################################################################################################################
Função responsável por apagar o buffer do diplay 128x32 do AcquaShield_EC
######################################################################################################################################################*/
void ECShield::DispBuffClear(void)
{   
    mySerial3.listen();
 
    if(mySerial3.available()) {
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("bff");
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.    
    }
}

/*######################################################################################################################################################
Função responsável por apagar os dados do diplay 128x32 do AcquaShield_EC
######################################################################################################################################################*/
void ECShield::DispClear(void)
{    
    mySerial3.listen();

    if(mySerial3.available()) {
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("clr");
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.  
    }  
}

/*######################################################################################################################################################
Função responsável por mostras os caracteres no diplay 128x32 do AcquaShield_EC
######################################################################################################################################################*/
void ECShield::DispShow(void)
{    
    mySerial3.listen();

    if(mySerial3.available()) {
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("snd");
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.  
    }  
}

/*######################################################################################################################################################
Função responsável por chamar a rotina de calibração no AcquaShield_EC
######################################################################################################################################################*/
void EC_Cal(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
    unsigned char uart_byte = 0;        //Recebe o byte recebido pela UART.
    unsigned char serial_byte = 0;      //Recebe o byte recebido pela UART.
    
     
    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_pH pela UART.
    delay(10);
    mySerial3.write("Cal");
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.   


    while(true) //Aguarda receber o byte de finalização da rotida de calibração do Shield de EC ('F').
    {                  
        if(mySerial3.available())                 //Verifica se recebeu um dado pela UART do AcquaShield_EC
        {
            uart_byte = mySerial3.read();
            Serial.write(uart_byte);                            
        }

        if(Serial.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_pH
        {
            serial_byte = Serial.read();   
            mySerial3.write(serial_byte);  
        }
        if(serial_byte == 'F')
        {
            Serial.write("Rotina de calibração finalizada.");
            Serial.println(); 
            while(true)
            { 
                delay(100);
            }
        }
    } 
}
}

/*######################################################################################################################################################
Função responsável por retornar o valor de Offset do eletrodo de EC no AcquaShield_EC na condição de contato com o Ar
######################################################################################################################################################*/
float EC_offset(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float ec_offset = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("Oft");         //Envia o comando para leitura do OffSet pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ec_offset = atof(rx_vetor);     
         return ec_offset;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do Slope (Lo ou Hi) do eletrodo de EC no AcquaShield_EC
######################################################################################################################################################*/
float EC_slope(char slope[]) 
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float ec_sl = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};

     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write(slope);        //Envia o comando para leitura do slope pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.

     contador = 0;
     rx_timeout = 0;     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ec_sl = atof(rx_vetor);     
         return ec_sl;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do Coeficiente angular (Lo ou Hi) do eletrodo de EC no AcquaShield_EC
######################################################################################################################################################*/
float EC_linear_coef(char linc[]) 
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float ec_lc = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write(linc);        //Envia o comando para leitura do coeficiente linear pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);          //Envia o caractere de finalização do comando.
     

     contador = 0;
     rx_timeout = 0;
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         ec_lc = atof(rx_vetor);     
         return ec_lc;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor da temperatura de calibração do AcquaShield_EC.
######################################################################################################################################################*/
float EC_CalTemp(void) 
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float CalTemp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("Ctmp"); //Envia o comando para leitura da temperatura de calibracao pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         CalTemp = atof(rx_vetor);     
         return CalTemp;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do do Fator de Conversão de TDS do AcquaShield_EC.
######################################################################################################################################################*/
float EC_FatorTds(void) 
{
    mySerial3.listen();

    if(mySerial3.available()) {
     float _FatorTds = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("Ftds"); //Envia o comando para leitura do Fator TDS pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         _FatorTds = atof(rx_vetor);     
         return _FatorTds;
     }  
    }  
}

/*######################################################################################################################################################
Função responsável por setar e retornar um novo valor para Fator de Conversão de TDS do AcquaShield_EC.
######################################################################################################################################################*/
float EC_SetFatorTds(char comando[]) 
{
    mySerial3.listen();

    if(mySerial3.available()) {
    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write(comando);        //Envia o comando para definir Fator TDS pelo AcquaShield.
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}

/*######################################################################################################################################################
Função responsável por resetar para o valor default o Fator de Conversão de TDS do AcquaShield_EC.
######################################################################################################################################################*/
float EC_ResetFatorTds(void) 
{   
    mySerial3.listen();

    if(mySerial3.available()) {
    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write("RFtds");        //Envia comando para resetar o Fator de Coversao TDS
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}

/*######################################################################################################################################################
Função responsável por habilitar a compensação de temperatura de EC do AcquaShield_EC.
######################################################################################################################################################*/
void EC_EnableCompTemp(void) 
{   
    mySerial3.listen();

    if(mySerial3.available()) {
    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write("EComp");        //Envia comando para habilitar compensação de temperatura
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}

/*######################################################################################################################################################
Função responsável por desabilitar a compensação de temperatura de EC do AcquaShield_EC.
######################################################################################################################################################*/
void EC_DisableCompTemp(void) 
{   
    mySerial3.listen();

    if(mySerial3.available()) {

    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write("DComp");        //Envia comando para desabilitar compensação de temperatura
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}


/*######################################################################################################################################################
Função responsável por retornar o valor da temperatura de calibração do AcquaShield_EC.
######################################################################################################################################################*/
uint8_t EC_StatusCompTemp(void) 
{
    mySerial3.listen();

    if(mySerial3.available()) {

     uint8_t StatusCompTemp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("STComp"); //Envia o comando para leitura da temperatura de calibracao pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.
     
     contador = 0;
     while((contador < 1)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
        if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
        {
            
            StatusCompTemp = mySerial3.read();      //Le o dado
            contador++;                            
        }
        rx_timeout++;                       
        delay(1);
     }
     if(rx_timeout >= 2000)
     {
        return 255;
     }   
     else
     {
        //StatusCompTemp = atoi(rx_vetor);     
        return StatusCompTemp;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por retornar o valor do Coeficiente de tmeperatura de EC do AcquaShield_EC.
######################################################################################################################################################*/
float EC_FatorComp(void) 
{
    mySerial3.listen();

    if(mySerial3.available()) {

     float _FatorTemp = 0;
     unsigned int contador = 0;
     unsigned int rx_timeout = 0;
     char rx_vetor[6] = {0,0,0,0,0,0};
    
     mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
     delay(10);
     mySerial3.write("FComp"); //Envia o comando para leitura do Coeficiente de temperatura pelo AcquaShield.
     delay(10);
     mySerial3.write(0xED);   //Envia o caractere de finalização do comando.
     
     while((contador <= 6)&(rx_timeout < 2000)) //Aguarda receber os 6 bytes da leitura de temperatura e, caso de algum erro, verifica a variável de timeout.
     {
         if(mySerial3.available())                   //Verifica se recebeu um dado pela UART do AcquaShield_EC
         {
             rx_vetor[contador] = mySerial3.read();  //Adiciona o dado ao vetor de RX.
             contador++;                            
         }
         rx_timeout++;                       
         delay(1);
     }
     if(rx_timeout >= 2000)
     {
         return 99.999;
     }   
     else
     {
         _FatorTemp = atof(rx_vetor);     
         return _FatorTemp;
     }    
    }
}

/*######################################################################################################################################################
Função responsável por setar valor para o Coeficiente de Temperatura do AcquaShield_EC.
######################################################################################################################################################*/
float EC_SetFatorComp(char comando[]) 
{
    mySerial3.listen();

    if(mySerial3.available()) {

    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write(comando);        //Envia o comando para definir Coeficiente de Temperatura  pelo AcquaShield.
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}

/*######################################################################################################################################################
Função responsável por resetar para o valor default o Coeficiente de Temperatura do AcquaShield_EC.
######################################################################################################################################################*/
float EC_ResetFatorComp(void) 
{   
    mySerial3.listen();

    if(mySerial3.available()) {

    mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
    delay(10);
    mySerial3.write("RFComp");        //Envia comando para resetar o Coeficiente de Temperatura de EC
    delay(10);
    mySerial3.write(0xED);           //Envia o caractere de finalização do comando.
    }
}





/*######################################################################################################################################################
Função responsável por receber os dados da UART, vindos do Arduino UNO,a tratá-los conforme suas respectivas funções.
Esta função é chamada toda vez que um byte é recebudo pela UART e um buffer é preenchido com os dados para posterior tratamento.
######################################################################################################################################################*/
void serialEvent3(void)
{
    mySerial3.listen();

    if(mySerial3.available()) {

    unsigned char uart_byte = 0;         //Recebe o byte recebido pela UART.
    unsigned char uart_vetor[16];        //Vetor para armazenar os bytes de comando.
    char comando_vetor[11];               //vetor para armazenar o comando recebido pela UART 
    unsigned int cont_comando = 0;       //Contador para indexar o vetor de comando.
    static boolean verif_addr = false;   //Bit para controle de acesso à função de comandos.
    unsigned int i = 0;
    static char vetor_serial[5];

    while(Serial.available() > 0)  //Aguarda o buffer da UART ser lido totalmente.
    {
        uart_byte = Serial.read();
    
        if((uart_byte == EndCommand)&(verif_addr == true))                               //Verifica se o comando de finalização chegou pela UART.
        {   
            for(i = (cont_comando); i < 16; i++)  
                uart_vetor[i] = '\0';
            
            if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'l')) 
            {
                EC_Cal();
            }       
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'D')&(uart_vetor[3] == 'r')&(uart_vetor[4] == 'y')) 
            {
                dtostrf((EC_offset()), 2, 1, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("EC Dry: ");
                Serial.write(vetor_serial);
                Serial.write("mV");
                Serial.println();
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'P')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'r')&(uart_vetor[5] == 'a')&(uart_vetor[6] == 'm')) 
            {
                dtostrf(EC_slope("SlopL"), 2, 4, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Slope Low EC: ");
                Serial.write(vetor_serial);
                Serial.write(" mV/(uS/cm)");
                Serial.println();

                Serial.flush();

                dtostrf(EC_linear_coef("LincL"), 3, 1, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Coef. Lin. Low EC: ");
                Serial.write(vetor_serial);
                Serial.write(" mV");
                Serial.println();

                Serial.flush();

                dtostrf(EC_slope("SlopH"), 2, 4, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Slope High EC: ");
                Serial.write(vetor_serial);
                Serial.write(" mV/(uS/cm)");
                Serial.println();

                Serial.flush();

                dtostrf(EC_linear_coef("LincH"), 3, 1, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Coef. Lin. High EC: ");
                Serial.write(vetor_serial);
                Serial.write(" mV");
                Serial.println();

                Serial.flush();
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 't')&(uart_vetor[5] == 'm')&(uart_vetor[6] == 'p')) 
            {
                dtostrf(EC_CalTemp(), 2, 1, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Temperatura(Cal): ");
                Serial.write(vetor_serial);
                Serial.write("ºC");
                Serial.println();
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'F')&(uart_vetor[3] == 't')&(uart_vetor[4] == 'd')&(uart_vetor[5] == 's'))
            {
                dtostrf(EC_FatorTds(), 3, 2, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Fator TDS: ");
                Serial.write(vetor_serial);              
                Serial.println();

            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'F')&(uart_vetor[4] == 't')&(uart_vetor[5] == 'd')&(uart_vetor[6] == 's'))
            {
                for(i=0; i<=9; i++)
                {
                    comando_vetor[i] = uart_vetor[i+2];     //filtra somente caracters do comando
                }
                strcpy(comando_vetor, comando_vetor);       //atribui o vetor char
                EC_SetFatorTds(comando_vetor);              //chama função para enviar comando para o Shield
              
                Serial.write("Novo Fator TDS setado! ");               
                Serial.println();  
                
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'R')&(uart_vetor[3] == 'F')&(uart_vetor[4] == 't')&(uart_vetor[5] == 'd')&(uart_vetor[6] == 's'))
            {
                EC_ResetFatorTds();                        //chama função para enviar comando para o Shield

                Serial.write("Fator TDS resetado! ");
                Serial.println();
                
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'C')&(uart_vetor[3] == 'e')&(uart_vetor[4] == 'r')&(uart_vetor[5] == 'a')&(uart_vetor[6] == 's')) 
            {
                mySerial3.write(ShieldEC_addr);  //Envia o endereço do AcquaShield_EC pela UART.
                delay(10);
                mySerial3.write("Cers");         //Envia o comando para resetar os parâmetros de calibração no AcquaShield.
                delay(10);
                mySerial3.write(0xED);           //Envia o caractere de finalização do comando.   
                
                Serial.write("Calibração EC apagada !");
                Serial.println();

            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'a')&(uart_vetor[4] == 'l')&(uart_vetor[5] == 'i')&(uart_vetor[6] == 'n'))
            {
                var_type = salinidade;
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'T')&(uart_vetor[3] == 'e')&(uart_vetor[4] == 'm')&(uart_vetor[5] == 'p'))
            {
                var_type = temperatura;
            }
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'T')&(uart_vetor[3] == 'd')&(uart_vetor[4] == 's'))
            {
                var_type = tds;
            }
            //Comando para habilitar a compensacao de temperatura
            else if ((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'E')&(uart_vetor[3] == 'C')&(uart_vetor[4] == 'o')&(uart_vetor[5] == 'm')&(uart_vetor[6] == 'p'))
            {
                EC_EnableCompTemp();

                Serial.write("Compensação de Temperatura habilitada! ");
                Serial.println();

            }
            //Comando para desabilitar a compensacao de temperatura
            else if ((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'D')&(uart_vetor[3] == 'C')&(uart_vetor[4] == 'o')&(uart_vetor[5] == 'm')&(uart_vetor[6] == 'p'))
            {
                EC_DisableCompTemp();

                Serial.write("Compensação de Temperatura desabilitada! ");
                Serial.println();
            }
            //Comando para retornar o estado da compensação de temperatura
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'T')&(uart_vetor[4] == 'C')&(uart_vetor[5] == 'o')&(uart_vetor[6] == 'm')&(uart_vetor[7] == 'p'))
            {
                switch (EC_StatusCompTemp())
                {
                    case 0:
                        Serial.write("Estado da Compensação de Temperatura: DESABILITADA ");
                        break;
                    case 1:
                        Serial.write("Estado da Compensação de Temperatura: HABILITADA ");
                        break;

                    case 255:
                        Serial.write("Estado da Compensação de Temperatura: TIMEOUT ");
                        break;
                    
                    default:
                        Serial.write("Estado da Compensação de Temperatura: INDEFNIDO ");
                        break;
                }

                Serial.println();

            }
            //Comando para retornar o Coeficiente de temperatura de EC
            else if((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'F')&(uart_vetor[3] == 'C')&(uart_vetor[4] == 'o')&(uart_vetor[5] == 'm')&(uart_vetor[6] == 'p'))
            {
                dtostrf(EC_FatorComp(), 3, 2, vetor_serial);
                strcpy(vetor_serial, vetor_serial);
                Serial.write("Coeficiente de Temperatura: ");
                Serial.write(vetor_serial);   
                Serial.write("  [% uS/cm/C]");
                Serial.println();

            }
            //Comando para setar um novo valor para o coeficiente de temperatura
            else if ((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'S')&(uart_vetor[3] == 'F')&(uart_vetor[4] == 'C')&(uart_vetor[5] == 'o')&(uart_vetor[6] == 'm')&(uart_vetor[7] == 'p'))
            {
                for(i=0; i<=10; i++)
                {
                    comando_vetor[i] = uart_vetor[i+2];     //filtra somente caracters do comando
                }
                strcpy(comando_vetor, comando_vetor);       //atribui o vetor char
                EC_SetFatorComp(comando_vetor);              //chama função para enviar comando para o Shield
              
                Serial.write("Novo Coeficiente de Temperatura setado! ");               
                Serial.println(); 
            }
            //Comando para resetar coeficiente de temperatura para o valor default
            else if ((uart_vetor[0] == 'E')&(uart_vetor[1] == 'C')&(uart_vetor[2] == 'R')&(uart_vetor[3] == 'F')&(uart_vetor[4] == 'C')&(uart_vetor[5] == 'o')&(uart_vetor[6] == 'm')&(uart_vetor[7] == 'p'))
            {
                EC_ResetFatorComp();                        //chama função para enviar comando para o Shield

                Serial.write("Coeficiente de Temperatura resetado! ");
                Serial.println();
            }
            else         
            {
                Serial.write("Comando não válido !");
                Serial.println();
            }
        
            verif_addr = false;
            cont_comando = 0;    
        }
        if(verif_addr == true)    //Carrega o vetor da UART enquanto o comando de finalização não chegar.
        {   
            uart_vetor[cont_comando] = uart_byte;
            cont_comando++;  
            if(cont_comando > 16)  //Verifica se os bytes de comando estouraram o contador de comandos.
            {
                Serial.write("Estouro de comando !");
                cont_comando = 0;    
            }
        }
        if((uart_byte == StartCommand) & (verif_addr == false))  //Verifica se o byte recebido corresponde ao endereço do shield pH.
        {
            verif_addr = true;                                   //Ativa o bit de verificação de acesso. 
            cont_comando = 0;
        }
    }
    verif_addr = false;
    cont_comando = 0;   
    for(i = 0; i < 16; i++)
        uart_vetor[i] = '\0';
}
}
