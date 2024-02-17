#include <iostream>
#include <windows.h>
#include <string.h>
using namespace std;

int main(void){
    // variables
    HANDLE crFile;
    BOOL wrfile, refile;
    string textFile;
    int textLength;

    // create directory
     
    const char* directoryPath = "C:\\yakoyakee\\";
    if (CreateDirectory(directoryPath,NULL)){
        cout << "directory created successfully!" << endl;
    }else{
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS){
            cout << " the directory is already exists!\n" ;
        }
        else{
            cout << "Error creating directory :"+ error << endl;
        }
    }
    // creating file 
    crFile = CreateFile("C:\\yakoyakee\\yakoransom.txt",
    GENERIC_READ|GENERIC_WRITE,
    FILE_SHARE_READ,
    NULL,
    CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    NULL);
// cheking the file...
    if (crFile == INVALID_HANDLE_VALUE)
    {
        cout << "Create File Failed. Error No:" << GetLastError() <<endl;
        return 0;
    }
    cout << "create file sucessfull !\n";



    //Write the file
    cout << "put the text you want to write:" << endl;
    cin >> textFile;
    textLength = textFile.length();

    // alocate memory for the text
    char *chbuffer = new char[textLength+1];
    strcpy(chbuffer,textFile.c_str());

    //some other variables for writing func
    DWORD DwNoBytesToWrite = strlen(chbuffer);
    DWORD DwNoBytesWritten = 0;
    
    wrfile = WriteFile(
    crFile,
    chbuffer,
    DwNoBytesToWrite,
    &DwNoBytesWritten,
    NULL);
    if (!wrfile){
        cout << "Writefile is failed !,Error Num: " + GetLastError() << endl;
    }else{
        cout << "write file successful !" << endl;
    }

    delete[] chbuffer; // free the memory allocated for the array

    getchar();
    

    //get file size
    DWORD filesize = GetFileSize(crFile,NULL);
    if (filesize == INVALID_FILE_SIZE){
        cout << "couldn't get the file size,error No:" + GetLastError()<< endl;
        CloseHandle(crFile);
        return 1;
    }


    //Allocate a buffer to hold the contain file
    char *buffer = new char[filesize +1];
    if (buffer == NULL){
        cout << "couldn't get memory size" << endl;
    }
        

    //close the handle
    CloseHandle(crFile);
    return 0;
}