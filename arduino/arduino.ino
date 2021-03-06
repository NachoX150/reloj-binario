    
//Pin connectado al latch pin (ST_CP) de 74HC595
const int latchPin = 8;
//Pin connectado al clock pin (SH_CP) de 74HC595
const int clockPin = 12;
//Pin connectado al Data in (DS) de 74HC595
const int dataPin = 11;

//Datos tipo byte para cara digito de la hora
byte h1,h2,m1,m2,s1,s2;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  int hora,minuto,segundo;
  hora=15;
  minuto=20;
  segundo=37;

  intAbyte(hora, 0);
  intAbyte(minuto, 1);
  //intAbyte(segundo, 2);
  if (Serial.available() > 0) {
    int val=Serial.read();
    //intAbyte(val,2);
    s2=byte(val);
    s2 = s2 << 1;    //Shift de un bit por error de integrado
    registerWrite(s2, HIGH);
  }
  
}
//ESTA FUNCION QUIZAS NO HAGA FALTA CUANDO PASEMOS EL BYTE DESDE LINUX
void intAbyte(int ent, int tipo){  //tipo: 0=hora 1=minuto 2=segundo
  int dec,uni, *ptr;
  uni=ent % 10;  //Toma la unidad
  dec=( ent-(ent%10) )/10; //Toma la decena
  switch(tipo){
  case 0:
      h1=byte(dec);
      h2=byte(uni);
  break;
  case 1:
      m1=byte(dec);
      m2=byte(uni);
  break;
  case 2:
      s1=byte(dec);
      s2=byte(uni);
  break;
  default:
  break;
  };
  
}



void registerWrite(byte dato, int estado) {
	
	digitalWrite(latchPin, LOW);

	// turn on the next highest bit in bitsToSend:
	//bitWrite(bitsToSend, bitToSet, estado); //Coloca un 1 en el bit de posicion bitToSet
  
	// shift the bits out:
	//shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
  shiftOut(dataPin, clockPin, LSBFIRST, dato);
	// turn on the output so the LEDs can light up:
	digitalWrite(latchPin, HIGH);

}
