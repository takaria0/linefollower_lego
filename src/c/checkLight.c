task main()
{
  int sensorValue;
  SetSensorLight(S3);
  sensorValue = SENSOR_3;
  while (1)
  {
  ClearScreen();
  TextOut(0, LCD_LINE1, "Light:"); // 1行目の左端に表示
  NumOut(80, LCD_LINE1, sensorValue);  // 超音波センサの値を表示
  }
}