int getState(int threshold) {
  int state;
  int sensorValue;

  sensorValue = SENSOR_3;

  if (sensorValue < threshold - 10) {
    state = 0;
  };

  if (sensorValue < threshold - 5)
  {
    state = 1;
  };

  if (sensorValue < threshold)
  {
    state = 2;
  };

  if (sensorValue < threshold + 5)
  {
    // black
    state = 3;
  };

  if (sensorValue < threshold + 10)
  {
    // black
    state = 4;
  }

  if (threshold + 10 < sensorValue)
  {
    //black
    state = 5;
  }

  return state;

};

double getReward(int state) {
  double reward;
  // int sensorValue = SENSOR_3;
  

  reward = 0;

  if (state > 2) {
    reward = 100;
  };

  if (state <= 2) {
    reward = -50;
  }

  return reward;
};



void doAction(int action) {
  void onRL(float speed_l, float speed_r) {
      OnFwd(OUT_B, speed_r);
      OnFwd(OUT_C, speed_l);
  };

  // actionToSpeedArray = [][];
  if (action == 0)
  {
    onRL(100, 100);
  } 
  else if (action == 1) 
  {
    onRL(80, 40);
  } 
  else if (action == 2) 
  {
    onRL(60, 30);
  } 
  else if (action == 3) 
  {
    onRL(80, 0);
  }
  else if (action == 4)
  {
    onRL(60, 0);
  }
  else if (action == 5)
  {
    onRL(40, 80);
  }
  else if (action == 6)
  {
    onRL(30, 60);
  }
  else if (action == 7)
  {
    onRL(0, 80);
  }
  else if (action == 8)
  {
    onRL(0, 60);
  }
  else if (action == 9)
  {
    onRL(100, 20);
  }
  else if (action == 10)
  {
    onRL(20, 100);
  }

};

double getMaxQval(int state, int num, double Qtable[3][5]) {
  double maxQval;
  int i = 0;

  maxQval = Qtable[state][0];

  for (i = 1; i < num; i++) {
    if (Qtable[state][i] > maxQval) {
      maxQval = Qtable[state][i];
    };
  };

  return maxQval;
};

int selectAction(int state, int num, double Qtable[3][5]) {
  double maxQval;
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
};

int epsilonGreedy(int eps, int state, int num, double Qtable[3][5]) {
  int action;
  if (eps > rand() % 100) {
    action = rand() % num;
  } else {
    action = selectAction(state, num, Qtable);
  }
  return action;
};

double updateQtable(double Qtable[3][5], int state, int action, double reward, double alpha, double gamma, double maxQ) {
  return (1 - alpha) * Qtable[state][action] + alpha * (reward + gamma * maxQ);
}

void main() {
  int numberOfAction = 11;
  int numberofState = 6;
  double Qtable[numberofState][numberOfAction];

  double maxQ = 0;
  double reward = 0;
  double alpha = 0.5;
  double gamma = 0.9;
  int epsilon = 5;
  
  int action = 0;
  int state = 0;
  int stateNext = 0;
  int i, j;
  int seed = 0;
  int threshold = 42;

  for (i = 0; i < numberofState; i++) {
    for (j = 0; j < numberOfAction; j++) {
      Qtable[i][j] = 0;
    }
  }

  state = getState(threshold); // get initial state

  while (1) {

    action = epsilonGreedy(epsilon, state, numberOfAction, Qtable);
    doAction(action);
    
    /////////////////////////
    Wait(10);
    /////////////////////////

    stateNext = getState(threshold);

    reward = getReward(stateNext);
    maxQ = getMaxQval(stateNext, numberOfAction, Qtable);
    Qtable[state][action] = updateQtable(Qtable, state, action, reward, alpha, gamma, maxQ);

    state = stateNext;
  }


}