# Installation
## On MacOS
You have to install "nbc-1.2.1.r5.osx.tgz" from test release in http://bricxcc.sourceforge.net/ .
then find a binary file named nbc. It is used to transfer nxc file from mac to LEGO MINDSTORM NXT via USB.

## On Windows 
I don't know.

# How to import nxc file to LEGO
In the nbc's directory.
```bash
./nbc -d -S=usb filename
```
filename = "something.nxc"

# Be sure not to use common name as filename. 
I guess there's a duplication in global scope. So do not use like "test" or something.
I failed 'test.nxc' once.

# parameters doc
Wait(1000) // wait for a second. 1 sec = 1000

# Play sound
PlaySound(SOUND_DOUBLE_BEEP)
SOUND_CLICK ピッ
SOUND_DOUBLE_BEEP ピーッ、ピーッ
SOUND_DOWN ピロピロ〜と低くなる音
SOUND_UP ピロピロ〜と高く音
SOUND_LOW_BEEP ブーという低い音
SOUND_FAST_UP ピロピロ〜と速く高くなる音

# How to measure Light sensor value
明るさを測定 
トップメニューから「View」を選び、 左右の矢印ボタンで「Reflected light」を選びます。 そしてさらに左右の矢印ボタンで光センサを接続している 端子 (port) 番号を選べばディスプレイにセンサの値が表示されます。周りの明るさの違いやセンサの個体差もあるので、 周りのグループのセンサの値と違っていても不思議ではありません。

# References
http://yakushi.shinshu-u.ac.jp/robotics-jr/robotics-jr.html

http://yakushi.shinshu-u.ac.jp/robotics/?NXT/SampleProgram

http://yakushi.shinshu-u.ac.jp/robotics/?NXT

http://yakushi.shinshu-u.ac.jp/robotics-jr/robotics-jr-2013.pdf
