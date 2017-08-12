struct SENSOR_DATA get_random(SENSOR_DATA *data) {
  data -> HEART_RATE = random(70, 90);
  data -> SPO2 = random(95, 99);
  data -> SOUND = random(220, 240);
  return *data;
}

