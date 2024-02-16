#ifndef SDcard_h
#define SDcard_h

//Classe inspirada no exemplo disponível no Arduino Ide para o uso de cartões SD.

#include "FS.h"
#include "SD.h"
#include "SPI.h"

class SDcard {
    public:
        SDcard();
        void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
        void createDir(fs::FS &fs, const char * path);
        void removeDir(fs::FS &fs, const char * path);
        void readFile(fs::FS &fs, const char * path);
        void writeFile(fs::FS &fs, const char * path, const char * message);
        void appendFile(fs::FS &fs, const char * path, const char * message);
        void renameFile(fs::FS &fs, const char * path1, const char * path2);
        void deleteFile(fs::FS &fs, const char * path);
        void testFileIO(fs::FS &fs, const char * path);
        void iniciar();        
};

#endif
