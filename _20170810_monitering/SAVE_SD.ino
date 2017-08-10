#include <SD.h>
#include <SPI.h>

File file;

int CS_PIN = 4;

void initializeSD()
{
  if (SD.begin(CS_PIN)) {
    Serial.println("initialization done.");
  } else {
    Serial.println("initialization failed!");
    return;
  }
}

int openFileToWrite(char filename[])
{
    file = SD.open(filename, FILE_WRITE);

    if (file) {
      Serial.println("File open done.");
      return 1;
    } else {
      Serial.println("File open fail.");
      return 0;
    }
}

int writeToFile(String text)
{
  if (file) {
    file.println(text);
    Serial.println("File Writing ....");
    return 1;
  } else {
    Serial.println("File Writing Fail");
    return 0;
  }
}
void closeFile() {
  if (file) {
    file.close();
    Serial.println("File Close Done.");
  }
}

void writeEntryToFile(String entry) {

  openFileToWrite("log.txt");
  writeToFile(entry);
  closeFile();
}

