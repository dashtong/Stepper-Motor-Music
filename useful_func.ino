
void note_duration(float quarter) {
  tempo = (float)music_tempo / quarter;
}

void copy(float* dst, float* src, int len) {
  memcpy(dst, src, sizeof(src[0])*len);
}

void copy(int* dst, int* src, int len) {
  memcpy(dst, src, sizeof(src[0])*len);
}

bool cmp_length(arr_w_num_i a[MOTOR_NUM], arr_w_num_f b[MOTOR_NUM]) {
  for (int i = 0; i < MOTOR_NUM; i++) {
    if (a[i].num != b[i].num) return false;
  }
  return true;
}

int sum_notes(arr_w_num_i a[MOTOR_NUM]) {
  int res = 0;
  for (int i = 0; i < MOTOR_NUM; i++) {
    res += a[i].num;
  }
  return res;
}

bool check_ptr(int* p, arr_w_num_i a[MOTOR_NUM]) {
  // Check if any number in p is larger than a
  for (int i = 0; i < MOTOR_NUM; i++) {
    if (p[i] > a[i].num) return true;
  }
  return false;
}
