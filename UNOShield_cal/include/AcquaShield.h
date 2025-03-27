#ifndef ACQUASHIELD_H_INCLUDED
#define ACQUASHIELD_H_INCLUDED

#include <Arduino.h>

#define StartCommand '#'
#define EndCommand '#'

class pHShield
{
    public:  
        init(void);                                           //Inicializa o pHShied.
        float temp(void);                                     //Retorna o valor de temperatura lido no pHShield.
        float pH(void);                                       //Retorna o valor de pH.
        void DispWrite(char font, int x, int y, char str[]);  //Escreve uma string no display do pHShield.
        void DispBuffClear(void);                             //Apaga o buffer do display do pHShield.
        void DispClear(void);                                 //Apaga o display do pHShield.
        void DispShow(void);                                  //Envia os dados do fuffer para a tela do display do pHShield.
       
    private:
};

#define ShieldOD_addr 0xE7   //Endereço do Shield no protocolo UART (0xE7).

//enumera opções de improessao de OD
enum od_disp {mgl, saturacao};

//define variavel global para opção de impressao de OD
extern od_disp od_type;

class ODShield
{
    public:
        init(void);
        float temp(void);
        float OD(void);
        float ODsat(void);
        void DispWrite(char font, int x, int y, char str[]);  //Escreve uma string no display do pHShield.
        void DispBuffClear(void);                             //Apaga o buffer do display do pHShield.
        void DispClear(void);                                 //Apaga o display do pHShield.
        void DispShow(void);                                  //Envia os dados do fuffer para a tela do display do pHShield.
    
    private:
};

#define ShieldEC_addr 0xE9   //Endereço do Shield no protocolo UART (0xE9)

//enumera opções de impressão de variáveis no display
enum var_disp {temperatura, tds, salinidade};

//variável global para definir a variável a ser impressa no display
extern var_disp var_type;

class ECShield
{
    public:  
        init(void);                                           //Inicializa o ECShied.
        float temp(void);                                     //Retorna o valor de temperatura lido no ECShield.
        float EC(void);                                       //Retorna o valor de EC.
        float Salin(void);                                    //Retorna o valor de Salinidade
        float Tds(void);                                      //Retorna o valor de TDS
        void DispWrite(char font, int x, int y, char str[]);  //Escreve uma string no display do ECShield.
        void DispBuffClear(void);                             //Apaga o buffer do display do ECShield.
        void DispClear(void);                                 //Apaga o display do ECShield.
        void DispShow(void);                                  //Envia os dados do fuffer para a tela do display do ECShield.
       
    private:
};

#endif