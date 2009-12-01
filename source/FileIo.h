extern char *pFileBuffer;

int readFile(const char *fileName);
int readFileBuffer(const char *fileName, char *pBuffer);
int writeFileBuffer(const char *fileName, char *pBuffer);
// int decompressFileBuffer(char *fileName, char *pBuffer, int bufferLen);
int readFileSize(const char *fileName);
