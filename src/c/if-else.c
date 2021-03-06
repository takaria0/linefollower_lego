// // NXTのセンサは、黒で25〜30、白で55〜60くらいなので、 その中間くらいの42を「しきい値」として設定しています。 光セ
// // ンサはモノによって多少のバラつきがありますし、 部屋の明るさによっても変化しますので、 実際に明るさを測定して、よ
// //     り適切な値を選びます。

// void onRL(float speed_r, float speed_l)
// {
//   OnFwd(OUT_B, speed_r);
//   OnFwd(OUT_C, speed_l);
// };

// void goForward(float SPEED)
// {
//   onRL(SPEED, SPEED);
// };

// int doActionBasedOnState(int threshold)
// {
//   int state;
//   int sensorValue;
//   SetSensorLight(S3);
//   sensorValue = SENSOR_3;

//   if (sensorValue < threshold - 15)
//   {
//     onRL(50, -50);
//     state = 0;
//   }
//   else if (sensorValue < threshold - 7)
//   {
//     onRL(50, 0);
//     state = 1;
//   }
//   else if (sensorValue < threshold + 7)
//   {
//     onRL(50, 50);
//     state = 2;
//   }
//   else if (sensorValue < threshold + 15)
//   {
//     onRL(50, 50);
//     state = 3;
//   }
//   else
//   {
//     onRL(0, 50);
//     state = 3;
//   }

//   return state;
// };



// task main()
// {
//   // SetSensorLight(S3); // 端子3には光センサ
//   Wait(3000);

//   int thresholdLight = 45;
//   long move_time = 10000.0;
//   long t0 = CurrentTick();
//   int state;

//   while (CurrentTick() - t0 <= move_time)
//   {
//     state = doActionBasedOnState(thresholdLight);
//   };

//   PlaySound(SOUND_DOUBLE_BEEP);
//   Float(OUT_B);
//   Float(OUT_C);
// };

void onRL(float speed_r, float speed_l)
{
  OnFwd(OUT_B, speed_r);
  OnFwd(OUT_C, speed_l);
};

task main()
{
  SetSensorLight(S3);
  int threshold = 50;
  int timeSize = 180000;
  int sensorRecord[timeSize];

  int timeCount = 0;
  while(1)
  {
    Wait(25);
    if (SENSOR_3 < threshold)
    {
      onRL(60, 10);
    }
    else if (SENSOR_3 > threshold)
    {
      onRL(10, 60);
    }
    sensorRecord[timeCount] = SENSOR_3;
    timeCount += 1;
    Wait(25);
  }
}