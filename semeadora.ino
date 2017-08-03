FILE* datalog;
FILE* plant;
FILE* sequencia;
int pin = 2, apin = 3;
int aRead, cont = 0, filename = 0;
unsigned long start, finish = 0, timef;
float distance, veloc, aux2 = 0, naux = 0, oldaux = 0;
volatile float aux = 0;
char nome[100], getC;
int media = 0;
char nome2[100] ="/www/pages/logs/";
int aux42;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial){
  
  }
  pinMode(pin, INPUT);
  attachInterrupt(2, sensor, RISING);
  start = micros();


 //nomeando log
  sequencia = fopen("sequencia.txt", "r");
  getC = fgetc (sequencia);
  Serial.println (getC);
  aux42 = getC - '0';
  sprintf (nome,"%d",aux42);
  strcat(nome, ".txt");
  strcat(nome2, nome);
  
  Serial.println (aux42);
  fclose(sequencia);

  sequencia = fopen("sequencia.txt", "w");
  aux42++;
  char convert[100];
  sprintf(convert, "%d", aux42);
  Serial.println(convert);
  
  fputs(convert, sequencia);
  fclose(sequencia);
}

void loop() {
  // put your main code here, to run repeatedly:

  aRead = analogRead(apin);
  naux = aux/100;
  finish = micros();
  timef = ((finish-start)/1000000);
  veloc = (naux-oldaux)/timef;
  oldaux = naux;
  start = finish;
  char dist[10], veloci[9], pot[5];
  sprintf (dist,"%.2f", naux);
  sprintf (veloci,"%.2f", veloc);
  sprintf (pot,"%d", aRead);
  
  //file json
  datalog = fopen("/www/pages/realtime.json", "w");
  
  if (datalog){
    Serial.println ("writing...");
    fputs("{", datalog);
    fputs("\"distancia\" :", datalog);
    fputs(dist, datalog);
    fputs(",", datalog);
    fputs("\"profundidade\" :", datalog);
    fputs(pot, datalog);
    fputs(",", datalog);
    fputs("\"velocidade\" :", datalog);
    fputs(veloci, datalog);
    fputs("}", datalog);
    fclose(datalog);
 
    Serial.println("done");
 
  }else{
    Serial.println ("ERROR: File can't be open");
  }
  //
  //file txt
    plant = fopen(nome2, "a");
    fputs(dist, plant);
    fputs(";", plant);
    fputs(veloci, plant);
    fputs(";", plant);
    fputs(pot, plant);
    fputs(";", plant);
    fputs("\n", plant);
    fclose(plant);

  //
  delay(2000);
    
}

void sensor(){
  aux += 16.76;
}
