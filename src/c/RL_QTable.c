int numberOfAction = 4;
int numberofState = 6;
long Qtable[numberofState][numberOfAction];
long maxQ = 0;
long reward = 0;
long alpha = 0.7;
long gamma = 0.9;
int epsilon = 50;

int action = 0;
int state = 0;
int stateNext = 0;
int i, j;
int seed = 0;
int threshold = 60;
int actionRecord[];
int rewardRecord = 1;

int getState(int threshold) {
  int state;
  SetSensorLight(S3);

  if (SENSOR_3 < threshold - 10)
  {
    state = 0;
  }
  else if (SENSOR_3 < threshold - 5)
  {
    state = 1;
  }
  else if (SENSOR_3 < threshold)
  {
    state = 2;
  }
  else if (SENSOR_3 < threshold + 5)
  {
    state = 3;
  }
  else if (SENSOR_3 < threshold + 10)
  {
    state = 4;
  }
  else
  {
    state = 5;
  }
  ClearScreen();
  TextOut(0, LCD_LINE1, "Light:");   // 1行目の左端に表示
  NumOut(80, LCD_LINE1, Sensor(S3)); // 超音波センサの値を表示
  TextOut(0, LCD_LINE2, "State:");   // 1行目の左端に表示
  NumOut(80, LCD_LINE2, state); // 超音波センサの値を表示

  return state;

}

long getReward(int state) {
  long reward;

  reward = 0;
  if (SENSOR_3 < threshold)
  {
    rewardRecord += 1;
    reward = 100 * rewardRecord;
  }
  else
  {
    rewardRecord = 1;
    reward = -1000;
  }

  return reward;
}

void onRL(float speed_l, float speed_r)
{
  OnFwd(OUT_B, speed_r);
  OnFwd(OUT_C, speed_l);
}

void doAction(int action) {


  // actionToSpeedArray = [][];
  if (action == 0)
  {
    onRL(25, 40);
  } 
  else if (action == 1) 
  {
    onRL(40,25);
  }
  else if (action == 2)
  {
    onRL(30, 0);
  }
  else if (action == 3)
  {
    onRL(0, 30);
  }
}

long getMaxQval(int state, int num) {
  long maxQval;
  int i = 0;

  maxQval = Qtable[state][0];

  for (i = 1; i < num; i++) {
    if (Qtable[state][i] > maxQval) {
      maxQval = Qtable[state][i];
    };
  };

  return maxQval;
}

int selectAction(int state, int num) {
  long maxQval;
  int i = 0;
  int maxIndex;
  int action;

  maxQval = Qtable[state][0];
  maxIndex = 0;

  for (i = 1; i < num; i++) {
    if (Qtable[state][i] > maxQval) {
      maxQval = Qtable[state][i];
      maxIndex = i;
    };
  };

  action = maxIndex;
  return action;
}

int epsilonGreedy(int eps, int state, int num) {
  int action;
  if (eps > rand() % 100) {
    action = rand() % num;
  } else {
    action = selectAction(state, num);
  }
  return action;
}

// long updateQtable(long Qtable[numberofState][numberOfAction], int state, int action, long reward, long alpha, long gamma, long maxQ) {
  
//   return (1 - alpha) * Qtable[state][action] + alpha * (reward + gamma * maxQ);
// }


 





task main() {

  for (i = 0; i < numberofState; i++) {
    for (j = 0; j < numberOfAction; j++) {
      Qtable[i][j] = 0;
    }
  }

  state = getState(threshold); // get initial state

  int minusRewardCount = 0;
  int rewardBefore = 0;
  while (1) {
    action = epsilonGreedy(epsilon, state, numberOfAction);

    doAction(action);

    stateNext = getState(threshold);
    reward = getReward(stateNext);
    maxQ = getMaxQval(stateNext, numberOfAction);
    Qtable[state][action] = (1 - alpha) * Qtable[state][action] + alpha * (reward + gamma * maxQ);

     if (reward < 0)
    {
      minusRewardCount += 1;
      if (minusRewardCount == 5) {
        PlaySound(SOUND_LOW_BEEP);
        Off(OUT_BC);
        Off(OUT_B);
        Off(OUT_C);
      } else {
        PlaySound(SOUND_LOW_BEEP);
        Off(OUT_BC);
        Off(OUT_B);
        Off(OUT_C);
        Wait(2000);
      }
    }
    else
    {
      minusRewardCount = 0;
      PlaySound(SOUND_CLICK);
      Wait(100);
      Off(OUT_B);
      Off(OUT_C);
      Wait(100);
    }
    rewardBefore = reward;
    state = stateNext;
  }
}