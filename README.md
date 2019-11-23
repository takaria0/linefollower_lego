# How to import nxc file to LEGO
In the nbc's directory.
```bash
./nbc -d -S=usb filename
```
filename = "something.nxc"

# Be sure not to use common name as filename. 
I guess there's a duplication in global scope. So do not use like test or something.
I failed 'test.nxc' once.

# parameters doc
Wait(1000) // wait for a second 1sec = 1000

# Play sound
PlaySound(SOUND_DOUBLE_BEEP)
SOUND_CLICK ピッ
SOUND_DOUBLE_BEEP ピーッ、ピーッ
SOUND_DOWN ピロピロ〜と低くなる音
SOUND_UP ピロピロ〜と高く音
SOUND_LOW_BEEP ブーという低い音
SOUND_FAST_UP ピロピロ〜と速く高くなる音

# How to measure Light sensor value
実際の明るさを測定してみましょう。 トップメニューから「View」を選び、 左右の矢印ボタンで「Reflected light」を選
びます。 そしてさらに左右の矢印ボタンで光センサを接続している 端子 (port) 番号を選べばディスプレイにセンサの値
が表示されます。
周りの明るさの違いやセンサの個体差もあるので、 周りのグループのセンサの値と違っていても不思議ではありません。

```c
void onRL(float speed_l, float speed_r) {
  OnFwd(OUT_B, speed_r);
  OnFwd(OUT_C, speed_l);
};

void goForward(float SPEED) {
    onRL(SPEED, SPEED);
};

task main() {
  Wait(3000);
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
```