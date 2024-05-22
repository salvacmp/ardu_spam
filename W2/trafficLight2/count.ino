void countA() {
  if (counterA == 0) {
    b_lock = 1;
    if (statusA == 1) {
      counterA = y_interval;
      setLampGA(0, 1, 0);
    }
    if (statusA == 2) {
      counterA = g_interval;
      setLampGA(0, 0, 1);
    }
    if (statusA == 3) {
      counterA = y_interval;
      setLampGA(0, 1, 0);
    }

    if (statusA == 4) {
      counterA = cycle;
      statusA = 0;
      setLampGA(1, 0, 0);
    }
    statusA++;
  }


  if (global_time - holdA >= interval) {
    holdA = global_time;
    counterA--;
    displayA.showNumberDec(counterA, true, 2, 2);
  }
}
void countB() {
  if (counterB == 0) {
    c_lock = 1;
    switch (statusB) {
      case 1:
        counterB = y_interval;
        setLampGB(0, 1, 0);
        break;
      case 2:
        if (g_lock == 0) {
          g_lock = 1;
          counterB = g_interval;
          setLampGB(0, 0, 1);
        }
        break;
      case 3:
        g_lock = 0;
        counterB = y_interval;
        setLampGB(0, 1, 0);
        break;
    }

    if (statusB >= 4) {
      counterB = cycle;
      statusB = 0;
      setLampGB(1, 0, 0);
    }
    statusB++;
  }

  if (global_time - holdB >= interval) {
    holdB = global_time;
    counterB--;
    displayB.showNumberDec(counterB, true, 2, 2);
  }
}
void countC() {
  if (counterC == 0) {
    switch (statusC) {
      case 1:
        counterC = y_interval;
        counterA = 5;
        setLampGC(0, 1, 0);
        break;
      case 2:
        if (g_lock == 0) {
          g_lock = 1;
          counterC = g_interval;
          setLampGC(0, 0, 1);
        }
        break;
      case 3:
        g_lock = 0;
        counterC = y_interval;
        setLampGC(0, 1, 0);
        break;
    }

    if (statusC >= 4) {
      counterC = cycle;
      statusC = 0;
      setLampGC(1, 0, 0);
    }
    statusC++;
  }
  if (global_time - holdC >= interval) {
    holdC = global_time;
    counterC--;
    displayC.showNumberDec(counterC, true, 2, 2);
  }
}