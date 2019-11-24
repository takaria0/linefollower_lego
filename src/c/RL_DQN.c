#define inputSize  10
#define hiddenSize  3
#define outputSize 5

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// Neural Network Part
// input state vector [10, 1]
// output qvalues [5, 1]
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

struct NeuralNet
{
  int inputLayer[inputSize];

  double hiddenWeight[hiddenSize][inputSize + 1];
  double hiddenLayer[hiddenSize];

  double outputWeight[outputSize][hiddenSize + 1];
  double outputLayer[outputSize];

};

void initHiddenWeight()
{
  int i, j;
  for(i = 0; i < hiddenSize; i++)
  {
    for(j = 0; j < inputSize; j++)
    {
      NN.hiddenWeight[i][j] = drand();
    }
  }
}

void initOutputWeight()
{
  int i, j;
  for (i = 0; i < outputSize; i++) {
    for (j = 0; i < hiddenSize; j++) {
      NN.outputWeight[i][j] = drand();
    }
  }
}

void initNN() 
{
  initHiddenWeight();
  initOutputWeight();
}

double sigmoid(int x) 
{
  double s;
  return s;
}

double forwardProp()
{
  int i, j;
  double hiddenTemp;
  double output;

  for (i = 0; i < hiddenSize; i++) 
  {
    hiddenTemp = 0;
    for (j = 0; j < inputSize; j++) 
    {
      hiddenTemp += NN.inputLayer[j] * NN.hiddenWeight[i][j];
    }
    hiddenTemp -= NN.hiddenWeight[i][j];
    NN.hiddenLayer[i] = sigmoid(hiddenTemp);
  }

  output = 0;
  for (i = 0; i < hiddenSize; i++)
  {
    output += NN.hiddenLayer[i] * NN.outputWeight[i][j];
    output -= NN.outputWeight[i][j];
  }

  return sigmoid(output);
}

void backProp()
{

}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// Reinforcement Learning Part
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

struct RLParams
{
  int alpha;
  int gamma;
  int epsilon;
  int seed;
  int threshold;
};

double getQValue(int state)
{
  NN.inputLayer[state] = 1;
  return forwardProp();
}

int selectAction(int state, int num)
{
  int action;
  double Qvalues;

  Qvalues = getQValue(state);
  action = argMax(Qvalues);

  return action;
};

int epsilonGreedy(int eps, int state, int num)
{
  int action;
  if (eps > rand() % 100)
  {
    action = rand() % num;
  }
  else
  {
    action = selectAction(state, num);
  }
  return action;
};

void updateWeight(int state, int nextState, double reward)
{
  double currentQvalue;
  double labeledQvalue;

  currentQvalue = getQvalue(state);
  labeledQvalue = (1 - P.alpha) * currentQvalue + P.alpha * (reward);
  backProp(labeledQvalue);
}

int getState(int threshold)
{
  int state;
  int sensorValue;

  sensorValue = SENSOR_3;

  if (sensorValue < threshold - 10)
  {
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

void doAction(int action)
{
  void onRL(float speed_l, float speed_r)
  {
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

double getReward(int state)
{
  double reward;
  // int sensorValue = SENSOR_3;

  reward = 0;

  if (state > 2)
  {
    reward = 100;
  };

  if (state <= 2)
  {
    reward = -50;
  }

  return reward;
};

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
struct NeuralNet NN;
struct RLParams P;

void main()
{


  P.alpha = 0.5;
  P.gamma = 0.9;
  P.epsilon = 5;
  P.seed = 0;
  P.threshold = 42;

  int numberOfAction = 5;
  int numberofState = 10;

  double reward = 0;
  int action = 0;
  int state = 0;
  int stateNext = 0;
  int i, j;




  state = getState(P.threshold); // get initial state

  initNN();

  while (1)
  {
    action = epsilonGreedy(P.epsilon, state, numberOfAction);
    doAction(action);

    ////////////
    Wait(10);
    ////////////

    stateNext = getState(P.threshold); // get state from sensor
    reward = getReward(stateNext);

    // update weight
    updateWeight(state, stateNext, reward);

    state = stateNext;
  }
}
