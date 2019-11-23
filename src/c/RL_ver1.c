int getState(int threshold) {
  int state;
  int sensorValue;

  sensorValue = SENSOR_3;

  if (sensorValue > threshold) {
    state = 1;
  };

  if (sensorValue < threshold) {
    state = 2;
  };

  return state;

};

double getReward() {
  double reward;
  // int sensorValue = SENSOR_3;
  

  reward = 0;

  if (1) {
    reward = 100;
  };

  if (1) {
    reward = -100;
  }

  return reward;
};



void doAction(int action) {
  void onRL(float speed_l, float speed_r) {
      // OnFwd(OUT_B, speed_r);
      // OnFwd(OUT_C, speed_l);
  };

  // actionToSpeedArray = [][];
  if (action == 0) {
    onRL(100, 100);
  } else if (action == 1) {
    onRL(20, 0);
  } else if (action == 2) {
    onRL(0, 20);
  } else if (action == 3) {
    onRL(50, 50);
  } else if (action == 4) {
    onRL(0, 0);
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

void main() {
  int numberOfAction = 5;
  int numberofState = 10;
  double Qtable[10][5];

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

  for (i = 0; i < numberofState; i++) {
    for (j = 0; j < numberOfAction; j++) {
      Qtable[i][j] = 0;
    }
  }

  int threshold = 42;

  state = getState(threshold); // get initial state

  while (1) {

    action = epsilonGreedy(epsilon, state, numberOfAction, Qtable);

    doAction(action);

    stateNext = getState(threshold);
    reward = getReward();

    maxQ = getMaxQval(stateNext, numberOfAction, Qtable);
    Qtable[state][action] = (1 - alpha) * Qtable[state][action] + alpha * (reward + gamma * maxQ);

    state = stateNext;
  }


}