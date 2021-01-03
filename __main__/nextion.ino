void NextionPrintChart(Fifo f)
{
  int _val;
  int _digit_1, _digit_2, _digit_3, _digit_4, _digit_5;

  for (int i = 0; i < f.n; i++)
  {
    _val = FifoGetVal(f, i);
    NextionPrintSensorVal(_val, i);
  }
}

void NextionPrintSensorVal(int _val, int i)
{
  int _digit_1 = (_val % 10 / 1);
  int _digit_2 = (_val % 100 / 10);
  int _digit_3 = (_val % 1000 / 100);
  int _digit_4 = (_val % 10000 / 1000);
  int _digit_5 = (_val % 100000 / 10000);

  nextion.print(F("t"));
  nextion.print(i);
  nextion.print(F(".txt=\""));
  nextion.print(_digit_5);
  nextion.print(_digit_4);
  nextion.print(F("."));
  nextion.print(_digit_3);
  nextion.print(_digit_2);
  nextion.print(F("\""));
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.write(0xFF);
}

void NextionPrintInfo()
{
  nextion.print(F("t0.txt=\""));
  nextion.print(MODEL_ID);
  nextion.print(F("\""));
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.print(F("t1.txt=\""));
  nextion.print(VERSION_NUMBER);
  nextion.print(F("\""));
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.print(F("t2.txt=\""));
  nextion.print(SENSOR_SENSIBILITY);
  nextion.print(F("\""));
  nextion.write(0xFF);
  nextion.write(0xFF);
  nextion.write(0xFF);
}

void NextionHandleInputs()
{
  String message = myNextion.listen();
  if (message != "")
  {
    if (message == "65 0 1 1 ffff ffff ffff") state = HOME_PAGE;
    else if (message == "65 0 2 1 ffff ffff ffff") state = CHART_PAGE;
    else if (message == "65 0 3 1 ffff ffff ffff") state = FUNC_PAGE;
    else if (message == "65 0 4 1 ffff ffff ffff") state = INFO_PAGE;

    else if (message == "65 1 1 1 ffff ffff ffff") state = HOME_PAGE;
    else if (message == "65 1 2 1 ffff ffff ffff") state = CHART_PAGE;
    else if (message == "65 1 3 1 ffff ffff ffff") state = FUNC_PAGE;
    else if (message == "65 1 4 1 ffff ffff ffff") state = INFO_PAGE;

    else if (message == "65 2 1 1 ffff ffff ffff") state = HOME_PAGE;
    else if (message == "65 2 2 1 ffff ffff ffff") state = CHART_PAGE;
    else if (message == "65 2 3 1 ffff ffff ffff") state = FUNC_PAGE;
    else if (message == "65 2 4 1 ffff ffff ffff") state = INFO_PAGE;

    else if (message == "65 3 1 1 ffff ffff ffff") state = HOME_PAGE;
    else if (message == "65 3 2 1 ffff ffff ffff") state = CHART_PAGE;
    else if (message == "65 3 3 1 ffff ffff ffff") state = FUNC_PAGE;
    else if (message == "65 3 4 1 ffff ffff ffff") state = INFO_PAGE;
  }
}

void NextionHandleOutputs()
{
  bool is_page_changed = NextionHandlePageChanged();

  if (is_page_changed) NextionHandlePageRefreshed(true);
  else NextionHandlePageRefreshed(false);
}

bool NextionHandlePageChanged()
{
  if (state_prev != state)
  {
    state_prev = state;

    if (state == HOME_PAGE) nextion.print(F("page p_home"));
    else if (state == CHART_PAGE) nextion.print(F("page p_chart"));
    else if (state == FUNC_PAGE) nextion.print(F("page p_func"));
    else if (state == INFO_PAGE) nextion.print(F("page p_info"));
    nextion.write(0xFF);
    nextion.write(0xFF);
    nextion.write(0xFF);

    return 1;
  }
  return 0;
}

void NextionHandlePageRefreshed(bool force_refresh)
{
  if (state == HOME_PAGE)
  {
    if (sensor_val_prev != sensor_val || force_refresh)
    {
      sensor_val_prev = sensor_val;
      NextionPrintSensorVal(sensor_val, 0);
    }
  }
  else if (state == CHART_PAGE)
  {
    if (is_f_updated || force_refresh)
    {
      is_f_updated = false;
      NextionPrintChart(f);
    }
  }
  else if (state == FUNC_PAGE)
  {
    if (is_f_updated || force_refresh)
    {
      is_f_updated = false;
      int _avg = FifoGetAvg(f);
      NextionPrintSensorVal(_avg, 0);
    }
  }
  else if (state == INFO_PAGE)
  {
    if (force_refresh)
    {
      NextionPrintInfo();
    }
  }
}
