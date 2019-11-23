// float GetAngle(float d) // 距離 d からタイヤの回転数を計算する関数
// {
// const float diameter = 5.45; // タイヤの直径(cm)
// const float pi=3.1415; // 円周率
// float ang = d/(diameter*pi)*360.0; // 角度を計算する
// return ang; // 角度を返す(float型)
// }
// NXTのセンサは、黒で25〜30、白で55〜60くらいなので、 その中間くらいの42を「しきい値」として設定しています。 光セ
// ンサはモノによって多少のバラつきがありますし、 部屋の明るさによっても変化しますので、 実際に明るさを測定して、よ
//     り適切な値を選びます。

void onRL(float speed_l, float speed_r) {
  OnFwd(OUT_B, speed_r);
  OnFwd(OUT_C, speed_l);
};

void goForward(float SPEED) {
    onRL(SPEED, SPEED);
};

// int checkLight(int sensorInput, int threshold) {
//   if (sensorInput < threshold) {
//     return 1;
//   } else {
//     return 0;
//   }
// };

void main() {
  // SetSensorLight(S3); // 端子3には光センサ
  Wait(3000);
  // int angle = GetAngle(20.0); // 20.0cm進むのに必要な回転角度
  // 自動的にfloatからint型に変換して代入
  // RotateMotor(OUT_BC, SPEED, angle); // 角度指定でモータを回転
  // SetSensorTouch(S1);
  // int thresholdLight = 42;

  float speed = 50.0;
  long move_time = 3000.0;
  long t0 = CurrentTick();

  while (CurrentTick() - t0 <= (move_time/2)) {
    goForward(speed);
  };
  while (CurrentTick() - t0  <= move_time) {
    onRL(speed, 0);
  };

  PlaySound(SOUND_DOUBLE_BEEP);
  Float(OUT_B);
  Float(OUT_C);
};