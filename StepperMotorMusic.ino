#include <AccelStepper.h>
#include "notes.h"
#define get_arr_size(a) (sizeof(a) / sizeof(a[0]))

#define MOTOR_NUM   2

struct arr_w_num_i {
  int* arr;
  int num;
};

struct arr_w_num_f {
  float* arr;
  int num;
};

AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::FULL4WIRE, 8, 9, 10, 11);

AccelStepper* stepper[MOTOR_NUM] = {&stepper1, &stepper2};
///////////////////////////////////////////////////
// Required initialized by user
// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Tempo of the song
const int music_tempo = 130;

// Twinkle twinkle little star
//int scoreR[] = {C4, C4, G4, G4, A4, A4, G4};
//float scoreR_duration[] = {1, 1, 1, 1, 1, 1, 2};
//int scoreL[] = {A3};
//float scoreL_duration[] = {8};

// Fur Elise
//int scoreR[] = {E5, E5b, E5, E5b, E5, B4, D5, C5, A4, REST, C4, E4, A4, B4, REST, E4, A4b, B4, C5, REST, E4, E5, E5b, E5, E5b, E5, B4, D5, C5, A4, REST, C4, E4, A4};
//float scoreR_duration[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25};
//int scoreL[] = {REST, REST, A2, E3, A3, REST, REST, E2, E3, A3b, REST, REST, A2, E3, A3, REST, REST, REST, A2, E3, A3, REST, REST};
//float scoreL_duration[] = {0.5, 4, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 4, 0.25, 0.25, 0.25, 0.5};

// Flight of the bumblebee 165
//int scoreR[] = {E6, E6b, D6, D6b, D6, D6b, C6, B5, C6, B5, B5b, A5, A5b, G5, G5b, F5, E5, E5b, D5, D5b, D5, D5b, C5, B4, C5, B4, B4b, A4, A4b, G4, G4b, F4,
//                E4, E4b, D4, D4b, D4, D4b, C4, B3, E4, E4b, D4, D4b, D4, D4b, C4, B3, E4, E4b, D4, D4b, D4, D4b, C4, B3, E4, E4b, D4, D4b, D4, D4b, C4, B3,
//                E4, E4b, D4, D4b, C4, F4, E4, E4b, E4, E4b, D4, D4b, C4, D4b, D4, E4b
//               }; // 10bar
//float scoreR_duration[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
//                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
//                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25
//                          };
//int scoreL[] = {G6, G6b, F6, E6, F6, E6, E6, D6, E6, D6, D6b, C6, B5, B5, B5b, A5, G5, G5b, F5, E5, F5, E5, E5, D5, E5, D5, D5b, C5, B4, B4, B4b, A4,
//                G4, G4b, F4, E4, F4, E4, E4, D4, G4, G4b, F4, E4, F4, E4, E4, D4, G4, G4b, F4, E4, F4, E4, E4, D4, G4, G4b, F4, E4, F4, E4, E4, D4,
//                G4, G4b, F4, E4, E4, A4, G4, G4b, G4, G4b, F4, E4, E4, E4, F4, G4b
//               };
//float scoreL_duration[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
//                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
//                           0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25
//                          };

// Taisho Roman 130
int scoreR[] = {D5b, E5, G5b, A5b, E5b, E5, G5b, C5, D5b, E5b, A4b, D4b, D4b, E4b, E4, A3b, A3, A3b, D4b, E4b, E4, E4, E4b, E4b, D4b, REST, D4b, E4, REST, E4, E4, E4, E4b, E4b, D4b, D4b, REST, B3, D4b, B3, D4b, E4b, REST, B3, A3,
                REST, A3b, G3, A3b, REST, B3, B3, A3, A3b, A3b, A3, C4, A4b, G4b, E4b, E4, E4b, D4b, D4b, D4b, E4b, E4, D4b, D4b, E4b, E4, G4b, E4, E4, A4b, A4, A4b,
                REST
               };
float scoreR_duration[] = {0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.25, 0.75, 0.5,
                           0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1, 0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.25, 0.25, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                           2
                          };
int scoreL[] = {A2, REST, A2, A2b, REST, A2b, REST, D3b, D3b, REST, D3b, REST, D2b, D3b, D2b, D3b, D2b, D3b, D2b, D3b, D2b, D3b, D2b, D3b, D2b, D3b, D2b, D3b, B1, B2, B1, B2, B1, B2, B1, B2,
                E2, E3, E2, E3, A1b, A2b, A1b, A2b, E2b, E3b, E2b, E3b, A1b, A2b, A1b, A2b, D2b, D3b, B1, B2, B1b, B2b, B1b, B2b, A1, A2, A1, A2, A1, A2, A1, A2, A2, A2,
                REST
               };
float scoreL_duration[] = {0.5, 1, 0.5, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                           0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.5, 0.5,
                           2
                          };



// Need to be modified if motor is added or removed
arr_w_num_i score[MOTOR_NUM] = {
  {scoreR, -1},
  {scoreL, -1}
};
arr_w_num_f score_duration[MOTOR_NUM] = {
  {scoreR_duration, -1},
  {scoreL_duration, -1}
};

///////////////////////////////////////////////////
const int btnPin = A0;
int btnReading = 0;
int lastBtnReading = 0;
int btnToggle = 0;
unsigned long btnPressedTime;

float tempo = (float)music_tempo;
const float sixteenth_spacing_time = 1000 / 320;  //ms
float shortest_duration = 16;
int ptr[MOTOR_NUM] = {0};
unsigned long start_time;
bool incorrect = false;

void setup()
{
  Serial.begin(9600);
  pinMode(btnPin, INPUT);
  // Initialize the score num
  // Need to be modified if motor is added or removed
  score[0].num = get_arr_size(scoreR);
  score[1].num = get_arr_size(scoreL);
  score_duration[0].num = get_arr_size(scoreR_duration);
  score_duration[1].num = get_arr_size(scoreL_duration);
  if (!cmp_length(score, score_duration)) {
    Serial.println("Incorrect length of score and score_duration");
    for (int i = 0; i < MOTOR_NUM; i++) {
      Serial.println("score[" + String(i) + "]: " + String(score[i].num));
      Serial.println("score_duration[" + String(i) + "]: " + String(score_duration[i].num));
    }
    incorrect = true;
  }
  else {
    // Getting the shortest duration
    for (int k = 0; k < MOTOR_NUM; k++) {
      for (int i = 0; i < score[k].num; i++) {
        if (shortest_duration > score_duration[k].arr[i]) {
          shortest_duration = score_duration[k].arr[i];
        }
      }
    }
    Serial.println("Shortest Duration: " + String(shortest_duration));

    // Pre-processing
    for (int k = 0; k < MOTOR_NUM; k++) {
      for (int i = 0; i < score[k].num; i++) {
        // Transforming from tempo to ms
        score_duration[k].arr[i] *= ((float)60 * 1000) / (float)music_tempo;
        // Changing from {1, 1, 0.5, 2, 1} to {1, 2, 2.5, 4.5, 5.5}
        if (i > 0) {
          score_duration[k].arr[i] += score_duration[k].arr[i - 1];
        }
        //        Serial.print(i); Serial.print("   ");
        //        Serial.println(score_duration[k].arr[i]);
      }
    }

    Serial.println("The music begins soon");
  }
  for (int i = 0; i < MOTOR_NUM; i++) {
    stepper[i]->setMaxSpeed(1000);
  }
}

void loop() {
  // Initialize
  for (int i = 0; i < MOTOR_NUM; i++) {
    ptr[i] = 0;
  }
  Serial.println("New Loop");
  start_time = millis();
  while (!incorrect) {
    // Check for button in every loop
    btnReading = digitalRead(btnPin);

    // Debounce and Toggle of the button
    if (btnReading != lastBtnReading && btnReading == 1 && millis() - btnPressedTime > 400)  //250
    {
      btnPressedTime = millis();
      btnToggle = 1;
    }
    else btnToggle = 0;
    lastBtnReading = btnReading;

    // Press Button to raise a key
    if (btnToggle == 1) {
      for (int i = 0; i < score[0].num; i++) {
        score[0].arr[i] = (int)(score[0].arr[i] * 1.0594);  // 2 ^ (1/12) = 1.0594
      }
    }


    if (Serial.available()) {
      int reading = Serial.read();
      /*TODO*/
      break;
    }

    if (check_ptr(ptr, score)) {
      break;
    }

    for (int i = 0; i < MOTOR_NUM; i++) {
      // Set the target speed that is in the decent frequency
      stepper[i]->setSpeed(score[i].arr[ptr[i]]);

      // Check if it is between the spacing time period
      if (millis() - start_time >= score_duration[i].arr[ptr[i]] - sixteenth_spacing_time && millis() - start_time < score_duration[i].arr[ptr[i]]) {
        // Need a spacing time
        stepper[i]->setSpeed(0);
      }
      else if (millis() - start_time >= score_duration[i].arr[ptr[i]]) {
        ptr[i]++;
      }
    }

    for (int i = 0; i < MOTOR_NUM; i++) {
      stepper[i]->runSpeed();
    }
    //        Serial.print(ptr[0]);Serial.print("   ");Serial.println(score[0].arr[ptr[0]]);
  }
}
