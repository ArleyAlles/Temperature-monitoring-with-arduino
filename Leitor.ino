//========================== BIBLIOTECAS ===========================//
#include <EEPROM.h>
//==================================================================//



//======= ENTRADAS DIGITAIS (BOTÕES) E ANALÓGICAS (TRANSDUTOR) =====//
#define calibrar 2
#define valor_max 12
#define reset 7
#define analogPin A0
//=================================================================//



//============================= VARIÁVEIS =========================//
char resultado[5];
int  cont   = 0;
int  cont2  = 0;
int  cont3  = 0;
int  cont4  = 0;
int  cont5  = 0;
bool cont6  = false;
int cont7   = 0;
int valor2  = 0;
int filtered2 = 0;
float valor = 0;
float peso[10];
float C = 0;
float D = 0;
float coef[2];
float coef2[2];
float maior_vlr = 0;
float maior_vlr2 = 0;
const byte addr1 = 14;
const byte addr2 = 15;
int leit_ard[10];
int n = 50;
int numbers[50];
int original;
int filtered;
unsigned long tempo = 0;
String F;
//=================================================================//



//========================= PORTAS DO TECLADO =====================//
int linhas[]      = {3,4,5,6};
int colunas []    = {8,9,10,11};
char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};
//================================================================//




//=============================== SETUP ===========================//
void setup(){
  
  /*Botões*/
  pinMode(calibrar, INPUT_PULLUP);
  pinMode(valor_max, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);
  pinMode(tara, INPUT_PULLUP);
  Serial.begin(9600);
  
  /*Definindo linhas do telcado*/
  for(int num_L = 0; num_L <= 3; num_L++){
    pinMode(linhas[num_L], OUTPUT);
    digitalWrite(linhas[num_L], HIGH);
  }//Fim do for
  
  
  /*Definindo colunas do telcado*/
  for(int num_C = 0; num_C <= 3; num_C++){
    pinMode(colunas[num_C], INPUT_PULLUP);
  }//Fim do for
  
}//Fim do setup 
//=================================================================//




//============================= LOOP ================================//
void loop(){
  
  delay(60);
  
  FUNCIONAMENTO();
 
  CALIBRACAO();
  
}//Fim do loop
//=====================================================================//





//===================== FUNÇÃO BOTÃO CALIBRAR =======================//
bool BotaoCalibrar() {
  
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)
   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(calibrar);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}//Fim da função Botao
//===================================================================//





//===================== FUNÇÃO BOTÃO MAIOR VALOR =======================//
bool BotaoMaiorValor() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)
   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(valor_max);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}//Fim da função BotaoMaiorValor
//===================================================================//



//===================== FUNÇÃO BOTÃO RESET =======================//
bool BotaoReset() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)
   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(reset);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}//Fim da função RESET
//===================================================================//




//======================== FUNÇÃO TECLADO ===========================//
float Teclado(){

  float valor = 100000;
  /*Varredura em todas as linhas*/
  for (int num_L = 0; num_L <= 3; num_L++){
    digitalWrite(linhas[num_L], LOW);
    
    /*Varredura em todas as colunas*/
    for (int num_C = 0; num_C <= 3; num_C++){
      
      /*Saber se apertou algum botão*/
      if(digitalRead(colunas[num_C]) == LOW){
        resultado[cont]= teclas[num_L][num_C];
        cont += 1;
        if (cont == 5){
          F = String(resultado[0])+String(resultado[1])+String(resultado[2])+String(resultado[3])+String(resultado[4])+String(resultado[5]);
          float v_flt = F.toFloat();
          cont = 0;
          valor = v_flt/100;
        }//Fim do if para concatenar
        
        while(digitalRead(colunas[num_C]) == LOW){}   
      }//Fim do if para saber se apertou no botão
    }//Fim do for para colunas
    
      digitalWrite(linhas[num_L], HIGH);    
    }//Fim do for para linhas
  
    delay(10);
  
  return valor;
}//Fim da função Teclado
//================================================================//




//============== FUNÇÃO TECLADO PARA QTD DE PONTOS ===============//
int N_pontos(){
  int valor2 = 0;
  /*Varredura em todas as linhas*/
  for (int num_L = 0; num_L <= 3; num_L++){
    digitalWrite(linhas[num_L], LOW);
    
    /*Varredura em todas as colunas*/
    for (int num_C = 0; num_C <= 3; num_C++){
      
      /*Saber se apertou algum botão*/
      if(digitalRead(colunas[num_C]) == LOW){
        F = String(teclas[num_L][num_C]);
        valor2 = F.toInt();
        while(digitalRead(colunas[num_C]) == LOW){}   
      }//Fim do if para saber se apertou no botão
    }//Fim do for para colunas
      digitalWrite(linhas[num_L], HIGH);    
    }//Fim do for para linhas
  
    delay(10);
  return valor2;
}//Fim da função Teclado
//================================================================//




//===================== FUNÇÃO DE MÉDIA MÓVEL ====================//
long MEDIA_MOVEL(){
  long soma = 0; //Variável local
  numbers[0]= original; //Guardando o valor lido pelo arduino no primeiro elemento do vetor
  for (int i= n-1; i>0; i--) numbers[i]= numbers[i-1]; //Deslocamento dos elementos do vetor para direita
  for (int i=0; i<n; i++) soma+=numbers[i]; //Somatório dos elementos do vetor
  return soma/n; //Média móvel  
    
} // fim de MEDIA_MOVEL
//================================================================//





void FUNCIONAMENTO (){

if(!BotaoCalibrar()){
    
    /* Caso haja erro na digitação da calibração e queria voltar  do início */
    char resultado[5];
    cont = 0;
    
    /* Leitura da entrada analógica */
    int contador2 = 0;
    while(contador2 < 200){
      original = analogRead(analogPin);
      filtered2 = MEDIA_MOVEL();
        contador2 += 1;
    }//Fim do while
      
    /* Pegar valores de coeficiente angular e linear da EEPROM */
    EEPROM.get(addr1,coef2);
    
    /* Cálculo do valor do peso lido pelo arduin */
    float resp = (coef2[0]*filtered2) + coef2[1];
    
    /*Salvar o maior valor lido*/
    if((resp > maior_vlr) && (!BotaoReset())){
      maior_vlr = resp;
    }//Fim do if para salvar maior valor
    
    if(BotaoReset()){maior_vlr = 0;}
    
    if (cont6 == false){
      Serial.print("O valor atual do peso: ");
      Serial.println(resp);
    }//Fim do if para imprimir valor constantemente
    
    
    /* Mostrando o maior valor */
    if(BotaoMaiorValor()){
      Serial.print("O maior valor de peso foi: ");
      Serial.println(maior_vlr);
      cont6 = true;
    }//Fim do if para mostrar o maior valor
    
    if(!BotaoMaiorValor()){cont6 = false;}
    
    /* Reset dos contadores durante a calibração */
    cont2 = 0;
    cont3 = 0;
    cont4 = 0;
  }//Fim do if para NÃO pressionar o botão de calibrar 

}//Fim da função FUNCIONAMENTO
//=================================================================//







//============================ CALIBRAÇÃO ========================//

void CALIBRACAO(){

  /*Estado do botão de calibração*/
  if(BotaoCalibrar()){
 
    maior_vlr = 0;
    if(cont3 == 0){
      Serial.println("");
      Serial.print("Digite o numero de pontos de calibracao: ");
      cont3 = 1;
    }//Fim do if para número de pontos de calibração
  
    /*Anotando o número de pontos de calibração*/
    if(cont3 == 1){valor2 = N_pontos();}
    if((cont3 == 1) && (valor2 != 0)){
      Serial.println(valor2);
      float peso[valor2];
      int leit_ard[valor2];
      cont3 = 2;
    }//Fim do if para anotar número de pontos de calibração
   
    
    /*Print para digite valor do peso*/
    if((cont2 == 0) && (cont3 == 2) && (cont4 <= (valor2-1))){
        Serial.print("Digite o valor do peso: ");
        cont2 = 1;
        cont4 += 1;
    }//Fim do if para print
    
    /*Anotando valor do peso e lendo a entrada analógica do arduino*/
    if(cont3 == 2) {valor = Teclado();}
    if((valor != 100000) && (cont3 == 2) && (cont4 <= valor2)){
        int contador = 0;
        while(contador < 300){
          original = analogRead(analogPin);
        filtered = MEDIA_MOVEL();
          contador += 1;
        }//Fim do while
      
        Serial.println(valor);
        peso[(cont4-1)] = valor;
        leit_ard[(cont4-1)] = filtered;
        cont2 = 0;
      
       /*Realizando o ajuste de curvas*/
       if((cont4 == valor2) && (cont4>0)){
          float A = Sxx();
          float B = Sxy();
          C = B/A;
          D = B2();
          coef[0] = C;
          coef[1] = D;
          EEPROM.put(addr1, coef);
          Serial.println("//==================== Fim da calibracao ====================//");
          delay(500);

       }//Fim do if para ajuste de curvas     
    }//Fim do if para anotar valor do peso    
  }//Fim do if para ACIONAR botão de calibração
  
}//Fim da função CALIBRAÇÃO
//================================================================//



//========================= AJUSTE DE CURVAS ====================//
float Sxx(){
  
  float media_x;
  float soma_x = 0;
  float dif_x = 0;
  float a = 0;
  
  /*Média de x*/
  for (int i = 0; i < valor2; i++){
    soma_x = soma_x + leit_ard[i];
  }//Fim do for para soma de X
  media_x = soma_x/valor2;
  
  for (int j = 0; j < valor2; j++){
    a = pow((leit_ard[j]-media_x),2);
    dif_x = dif_x + a;
  }//Fim do for para diferença entre x
  
  return dif_x;

}//Fim da função Sxx


float Sxy(){
  
  float media_x;
  float soma_x = 0;
  float dif_x  = 0;
  float a      = 0;
  
  /*Média de x*/
  for (int i = 0; i < valor2; i++){
    soma_x = soma_x + leit_ard[i];
  }//Fim do for para soma de X
  media_x = soma_x/valor2;
  
  for (int j = 0; j < valor2; j++){
    a = peso[j]*(leit_ard[j]-media_x);
    dif_x = dif_x + a;
  }//Fim do for para diferença entre x
  
  return dif_x;
    
}//Fim da função Sxy



float B2 (){
  
  float media_x;
  float soma_x = 0;
  
  /*Média de x*/
  for (int i = 0; i < valor2; i++){
    soma_x = soma_x + leit_ard[i];
  }//Fim do for para soma de X
  media_x = soma_x/valor2;

  
  float media_y;
  float soma_y = 0;
  
  /*Média de y*/
  for (int i = 0; i < valor2; i++){
    soma_y = soma_y + peso[i];
  }//Fim do for para soma de X
  media_y = soma_y/valor2;
  
  return (media_y - (C*media_x));
}//Fim da função B2
//============================================================//
