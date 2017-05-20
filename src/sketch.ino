// Definerer input pinsene for pwm signalet fra receiveren
int PWM_PIN = 7;
int PWM_PIN2 = 4;

// Definerer pinsene for høyre og venstre hjul
int rightPin = 3;
int leftPin = 5;


// Funksjon for å få ut gjennonsnitlig pwm signal over 5 perioder
float getPwm(int pwmPin){
	float avrpwm = 0; // Setter gjennomsnitlig pwm til 0
	for(int i=0; i<5; i++){ // Kjører 5 ganger
		float pwm_value = pulseIn(pwmPin, HIGH); // setter pwm_value 
							//til lengden på en 
							// høy puls i ms.
		avrpwm += pwm_value; // plusser på pwm_value til avrpwm
		delay(0.1); //veldig kort pause for å unngå error
	}
	//trekker fra 896 for at 0 throttle på kontrolleren skal ha verdi 0
	float pwm = (avrpwm / 5)-896;
	return pwm;
}

void setup() {
	// Setter PWM pinsene til input og rightpin og leftpin til output
	pinMode(PWM_PIN, INPUT);
	pinMode(PWM_PIN2, INPUT);
	pinMode(rightPin, OUTPUT);
	pinMode(leftPin, OUTPUT);
	// Starter seriekommunikasjon til pcen, med overføringshastiget på 9600
	Serial.begin(9600);
}
 
void loop() {
	//leser pwm fra throttle pinnen. deler på 8 for å få resultater 
	//innenfor 128 verdier
	float throt = getPwm(PWM_PIN)/8;
	//deler på 512 for at verdien skal gå fra 0 til 2. 
	//Den funker som en multiplier
	float steer = getPwm(PWM_PIN2)/512;

	// ganger throttle med steer. 
	//når steer er 1 vil begge hjul gå like fort. 
	float left = throt * steer;
	// steer fungere omvendt proposjonal på høyre hjul, 
	// i forhold til venstre hjul
	float right = throt * (2.0-steer);

	// Sender verdiene for høyre og venstre hjul over serie, 
	//så det kan sees på pc
	Serial.println(left);
	Serial.println(right);

	// Skriver pwm verdien for høyre og venstre hjul til utgangene.
	analogWrite(leftPin, (int)left);
	analogWrite(rightPin, (int)right);
	// venter i 100 ms
	delay(100);
}

