#include <Servo.h>

#define echo 4
#define trig 3
#define enA 5
#define enB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define servo_pin 11
#define led 13

Servo servo;

int robot_speed = 100;

void setup() 
{
    Serial.begin(9600);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    servo.attach(servo_pin);
    give();
    led_on();
}

void loop() 
{
    if (Serial.available()) 
    {
        // читаем строку до конца и убираем пробелы/переводы строки
        String val = Serial.readStringUntil('\n');
        val.trim();

        // выводим в монитор то, что пришло с Bluetooth
        Serial.print("Получено по Bluetooth: ");
        Serial.println(val);

        // выполняем команды
        if (val == "Вперёд") {
            forward();
            Serial.println("➡ Выполняю: Вперёд");
        }
        else if (val == "Назад") {
            backward();
            Serial.println("⬅ Выполняю: Назад");
        }
        else if (val == "Вправо") {
            right();
            Serial.println("↪ Выполняю: Вправо");
        }
        else if (val == "Влево") {
            left();
            Serial.println("↩ Выполняю: Влево");
        }
        else if (val == "Стоп") {
            robot_stop();
            Serial.println("⛔ Выполняю: Стоп");
        }
        else {
            Serial.println("⚠ Неизвестная команда");
        }
    }
}

void forward() 
{
    // Оба мотора вращаются вперёд
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(enA, robot_speed);
    analogWrite(enB, robot_speed);
}

void backward() 
{
    // Оба мотора вращаются назад
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(enA, robot_speed);
    analogWrite(enB, robot_speed);
}

void left() 
{
    // Левый мотор назад, правый вперёд -> поворот влево
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(enA, robot_speed);
    analogWrite(enB, robot_speed);
}

void right() 
{
    // Левый мотор вперёд, правый назад -> поворот вправо
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(enA, robot_speed);
    analogWrite(enB, robot_speed);
}

void robot_stop() 
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}


//======================================
float distance() 
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    float t = pulseIn(echo, HIGH);
    float cm = t / 58.0;
    return cm;
}

void led_on() 
{
    digitalWrite(led, HIGH);
}

void led_off() 
{
    digitalWrite(led, LOW);
}

void take() 
{
    servo.write(25);
}

void give() 
{
    servo.write(5);
}
