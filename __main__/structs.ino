
void FifoPush(Fifo *s, int val) {
  for (int i = s->n - 2; i >= 0; i--) {
    s->a[i + 1] = s->a[i];
  }
  s->a[0] = val;
}

int FifoGetVal(Fifo s, int i) {
  return s.a[i];
}

int FifoGetAvg(Fifo s) {
  long _avg = 0;
  
  for (int i = 0; i < s.n; i++) {
    _avg += s.a[i];
  }
  _avg /= s.n;

  return (int)_avg;
}

void FifoPrint(Fifo s) {
  for (int i = 0; i < s.n; i++) {
    Serial.print(s.a[i]);
    Serial.print(",");
  }
  Serial.println();
}



bool CircInsert(Circ *s, int val) {
  bool is_overflow = false;
  
  s->a[s->i] = val;
  s->i = ++s->i % s->n;

  if (s->i == 0) is_overflow = true;
  return is_overflow;
}

int CircAvg(const Circ *self) {
  long _avg = 0;
  
  for (int i = 0; i < self->n; i++) {
    _avg += self->a[i];
  }
  _avg /= self->n;

  return (int)_avg;
}

void CircPrint(const Circ *self) {
  for (int i = 0; i < self->n; i++) {
    Serial.print(self->a[i]);
    Serial.print(",");
  }
  Serial.println();
}
