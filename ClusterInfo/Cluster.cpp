//IPW 2 #4 draft/ Grishan Ruslan
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
using namespace std;
int main() {
    HANDLE hFile = INVALID_HANDLE_VALUE; //drive or file to be checked

    LPCWSTR txtFile = L"Text.txt"; //text file
    hFile = CreateFile(txtFile,                         //target file
        GENERIC_READ | GENERIC_WRITE,    //read and write
        FILE_SHARE_READ | FILE_SHARE_WRITE,//allows sharing of read and writes
        NULL,                            //security prevents child process from inheriting the handle
        OPEN_EXISTING,                   //open file or drive if it exist 
        FILE_ATTRIBUTE_NORMAL,           //default settings for files
        NULL);                           //template file with generiv read access rights    
    if (hFile == INVALID_HANDLE_VALUE)  //error handling
    {
        cout << "File does not exist" << endl;
        CloseHandle(hFile);
        system("pause");
        return 0;
    }
    cout << "you opened the file succesfully: " << hFile << endl;

    const DWORD Clusters = 1000;
    const DWORD rpBufferSize = sizeof(RETRIEVAL_POINTERS_BUFFER) + (2 * (Clusters - 1) * sizeof(LARGE_INTEGER));
    BYTE output[rpBufferSize];
    STARTING_VCN_INPUT_BUFFER startVcn;
    RETRIEVAL_POINTERS_BUFFER* retrievalBuffer = (RETRIEVAL_POINTERS_BUFFER*) output;
    DWORD error = ERROR_MORE_DATA;
    BOOL returns;
    startVcn.StartingVcn.QuadPart = 0;
    while (error == ERROR_MORE_DATA) {

        DWORD bytesReturned;

        returns = DeviceIoControl(hFile,
            FSCTL_GET_RETRIEVAL_POINTERS,
            &startVcn,
            sizeof(startVcn),
            &output,
            sizeof(output),
            &bytesReturned,
            NULL);
        error = GetLastError();
        DWORD lastExtentN = retrievalBuffer->ExtentCount - 1;
        LONGLONG lastExtent = retrievalBuffer->Extents[lastExtentN].Lcn.QuadPart;
        LONGLONG lengthOfCluster = retrievalBuffer->Extents[lastExtentN].NextVcn.QuadPart - retrievalBuffer->Extents[lastExtentN - 1].NextVcn.QuadPart;

        switch (error) {

        case ERROR_HANDLE_EOF:
            //file sizes 0-1kb will return EOF error 
            cout << "ERROR_HANDLE_EOF" << endl;
            returns = true;
            break;

        case ERROR_MORE_DATA:
            cout << "ERROR_MORE_DATA" << endl;
            startVcn.StartingVcn = retrievalBuffer->Extents[0].NextVcn;

        case NO_ERROR:

            cout << "NO_ERROR, here is some info: " << endl;
            cout << "This is the lcnextent : " << retrievalBuffer->Extents[lastExtentN].Lcn.QuadPart << endl;
            cout << "This is the nextvnc: " << retrievalBuffer->Extents[lastExtentN].NextVcn.QuadPart << endl;
            cout << "This is the Extent count: " << retrievalBuffer->ExtentCount << endl;
            cout << "This is the Starting Vnc" << retrievalBuffer->StartingVcn.QuadPart << endl;
            cout << " The length of the cluster is: " << lengthOfCluster << endl;
            cout << " The last cluster is: " << lastExtent + lengthOfCluster - 1 << endl << endl << endl;
            break;

        default:
            cout << "Error in the code or input error" << endl;
            break;
        }
    }
}