//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadThread.h"
#include "Signatures.h"
#include "sqlite3.h"
#include <windows.h>
#include <iostream>
#include <string.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

Iterator::Iterator(AbstractFS* FS)
	:ClusterNumber(0), ClustersTotal(FS->GetTotalClusters()), Done(false), FS(FS)
{
    ClusterContent = new BYTE[FS->GetBytesPerCluster()];
}
void Iterator::first(){
    	ClusterNumber = 0;
}
void Iterator::next(){
    ClusterNumber++;
}
bool Iterator::IsDone(){
    return Done;
}
bool Iterator::ForceDone(){
	Done = true;
    return Done;
}
unsigned long Iterator::GetClusterNumber(){
	return ClusterNumber;
}

BYTE* Iterator::GetClusterContent(){
	DWORD BytesRead;
	LARGE_INTEGER Offset;
	Offset.QuadPart = ClusterNumber*FS->GetBytesPerCluster(); //bytes to skip

	unsigned long Pointer = SetFilePointer(FS->GetDiskHandle(), Offset.LowPart, &Offset.HighPart, FILE_BEGIN);
	if (Pointer != Offset.LowPart) {
	   Application->MessageBox(L"[ITERATOR]Error while trying set position in disk!",L"Message", MB_OK);
       return ClusterContent;
	}

	bool ReadCluster = ReadFile(FS->GetDiskHandle(), ClusterContent, FS->GetBytesPerCluster(), &BytesRead, NULL);
	if (ReadCluster == false || BytesRead != FS->GetBytesPerCluster()){
		Application -> MessageBox(L"[ITERATOR]Error while trying to read cluster!", L"Message",MB_OK);
	}
	return ClusterContent;
}

bool Decorator(BYTE* Content){
	if (Content[0] == 0x00) {
		return false;
	}
	return true;
}

__fastcall ReadThread::ReadThread(bool CreateSuspended, AbstractFS* FS, bool EnableDec, sqlite3* Database)
	: TThread(CreateSuspended), FS(FS), EnableDec(EnableDec), Database(Database)
{
	 FreeOnTerminate = true;
	 Iter = new Iterator(FS);

}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
     for(Iter->first();(!Iter->IsDone());Iter->next())
	 {
		if(Terminated){
            break;
		}
		Content = Iter ->GetClusterContent();
		if(EnableDec){
			bool Dec = Decorator(Content);
			if (!Dec) {
				continue;
			}
		}
		int sign = SignatureSearch(Content);
		if (sign != -1) {
			sqlite3_stmt* pStatement;
            std::wstring delrow = L"INSERT INTO Clusters (ClusterNumber, Signature) VALUES (" + std::to_wstring(Iter->GetClusterNumber());
			switch (sign) {
				case 0:
				delrow += L",\"jpeg\");";
				break;
				case 1:
				delrow += L",\"png\");";
				break;
				case 2:
				delrow += L",\"zip\");";
				break;
				case 3:
				delrow += L",\"rar\");";
				break;
				case 4:
				delrow += L",\"gzip\");";
				break;
				case 5:
                delrow += L",\"zip7\");";
				break;
			}
			const wchar_t* sql = delrow.c_str();
			int result = sqlite3_prepare16_v2(Database, sql, -1, &pStatement, NULL);
			if (result != SQLITE_OK) {
				Application->MessageBox(L"[ITERATOR] Error on Insert into table-1!",L"Message", MB_OK);
			}else{
				result = sqlite3_step(pStatement);
				if(result != SQLITE_DONE)
				{
					Application->MessageBox(L"[ITERATOR] Error on Insert into table-2!",L"Message", MB_OK);
				}
			}
   			sqlite3_finalize(pStatement);
		}

	 }
}
//---------------------------------------------------------------------------
