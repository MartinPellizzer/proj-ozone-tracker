void ReadSensor()
{
  if (Serial.available() > 0)
  {
    byte _buffer[8];
    Serial.readBytes(_buffer, 9);

    if (_CheckSum(_buffer, 9) == _buffer[8])
    {
      current_millis_zero = millis();
      sensor_val = CalculatePPB(_buffer);
    }
  }
}

int CalculatePPB(byte _buffer[])
{
  int _temp = _buffer[4] * 256 + _buffer[5];
  if (_temp >= 0 && _temp <= 10000)
  {
    return _temp;
  }
  return 0;
}

unsigned char _CheckSum(unsigned char *i, unsigned char ln)
{
  unsigned char j, tempq = 0;
  i += 1;
  for (j = 0; j < (ln - 2); j++)
  {
    tempq += *i;
    i++;
  }
  tempq = (~tempq) + 1; return (tempq);
}
