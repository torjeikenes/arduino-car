//input for pwm signal
byte PWM_PIN = 3;
byte PWM_PIN2 = 4;
 
float pwm_value;
float avrpwm;
float pwm;

//pins for led
int pin1 = 8;
int pin2 = 9;
int pin3 = 10;

int rightPin = 3;
int leftPin = 5;

float throt;
float steer;
float left;
float right;

//funksjon for aa faa ut gjennonsnitlig pwm signal over 5 perioder
int getPwm(int pwmPin){
	
	avrpwm = 0;
	for(int i=0; i<5; i++){
		pwm_value = pulseIn(pwmPin, HIGH);
		avrpwm += pwm_value;
		delay(1);
	}
	//trekker fra 896 for at 0 skal vere 0
	pwm = (avrpwm / 5)-896;
	return pwm;
}

void setup() {
	pinMode(PWM_PIN, INPUT);
	pinMode(PWM_PIN2, INPUT);
	pinMode(rightPin, OUTPUT);
	pinMode(leftPin, OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	Serial.begin(9600);
}
 
void loop() {
	//leser pwm fra throttle pinnen. deler på 8 for å få resultater innenfor 128 verdier
	throt = getPwm(PWM_PIN)/8;
	//deler på 512 for at verdien skal gå fra 0 til 2. Den funker som en multiplier
	steer = getPwm(PWM_PIN2)/512;
	//throt = (float)analogRead(PWM_PIN)/8;
	//steer = (float)analogRead(PWM_PIN2)/512; 

	// ganger throttle med steer. når steer er 1 vil begge hjul gå like fort. 
	left = throt * steer;
	//omvendt proposjonal med venstre hjul
	right = throt * (2.0-steer);

	Serial.println(left);
	Serial.println(right);
	//Serial.println(right);

	analogWrite(pin1, (int)left);
	analogWrite(pin2, (int)right);
	delay(100);
	/*
	if (throt < 10) {
		digitalWrite(pin1, LOW);	
		digitalWrite(pin1, LOW);	
		digitalWrite(pin1, LOW);	
	}
	else if (throt <300){
		digitalWrite(pin1, HIGH);	
		digitalWrite(pin2, LOW);	
		digitalWrite(pin3, LOW);	
	}
	else if (throt < 600){
		digitalWrite(pin1, HIGH);	
		digitalWrite(pin2, HIGH);	
		digitalWrite(pin3, LOW);	
	}
	else if (throt < 1000){
		digitalWrite(pin1, HIGH);	
		digitalWrite(pin2, HIGH);	
		digitalWrite(pin3, HIGH);	
	}*/
}

