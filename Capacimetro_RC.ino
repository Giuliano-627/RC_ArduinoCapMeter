unsigned long int tInicio = 0, tFinal = 0, t = 0, acumulador = 0;  //Incializacion de variables para medicion
void setup() {
  Serial.begin(9600);    //Inicializacion monitor serie
  pinMode(2, OUTPUT);    //Inicializacion pin 2 como salida digital
  digitalWrite(2, LOW);  //Set salida digital en bajo-GND
}

void loop() {
  Serial.println("Ready to read");
  while (!Serial.available())  //Bucle de espera infinito hasta que haya algo en puerto serie
    ;
  char c = Serial.read();  //Guardamos lo leido para limpiar el buffer
  acumulador = 0;
  for(int i=0; i<10; i++){
    acumulador += calcular(i);
  }
  float tPromedio = float(acumulador)/10;
  Serial.print("Tiempo de carga: ");
  Serial.print(tPromedio);
  Serial.println("uS");
  Serial.println("Descargando.");
}

unsigned long int calcular(int i) {

  tInicio = 0;  //Limpieza de variables
  tFinal = 0;   //Limpieza de variables
  t = 0;        //Limpieza de variables
  Serial.print("Leyendo iteracion ");
  Serial.println(i+1);
  tInicio = micros();           //Guardamos tiempo de inicio
  digitalWrite(2, HIGH);        //Seteamos el pin en alto para iniciar la carga
  while (analogRead(A0) < 647)  //Bucle de espera infinito hasta que se alcance un 63,2% de carga
    ;
  tFinal = micros();           //Guardamos el tiempo de carga
  digitalWrite(2, LOW);        //Iniciamos la descarga
  t = tFinal - tInicio;        //Guardamos la diferencia de tiempo
  while (analogRead(A0) > 10)  //Bucle infinito hasta que se descargue
    ;
  return t;
}