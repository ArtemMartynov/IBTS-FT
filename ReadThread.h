//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Main.h"
#include "Factory.h"
#include "sqlite3.h"
//---------------------------------------------------------------------------

class Iterator
{
	protected:
	   unsigned long ClusterNumber;
	   BYTE* ClusterContent;
	   unsigned long ClustersTotal;
	   bool Done;
	   AbstractFS* FS;
	public:
        Iterator(AbstractFS* FS);
		unsigned long GetClusterNumber();
		BYTE* GetClusterContent();
		bool IsDone();
        bool ForceDone();
		void first();
		void next();

};

bool Decorator(BYTE* Content);


class ReadThread : public TThread
{
private:
protected:
	AbstractFS* FS;
	bool EnableDec;
    Iterator* Iter;
	void __fastcall Execute();
	BYTE* Content;
    sqlite3* Database;
public:
	AbstractFS* GetFS();
	bool GetEnableDec();
	__fastcall ReadThread(bool CreateSuspended, AbstractFS* FS, bool EnableDec, sqlite3* Database);
};
//---------------------------------------------------------------------------
#endif
