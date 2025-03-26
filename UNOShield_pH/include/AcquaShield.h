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
#endif