//---------------------------------------------------------------------------

#ifndef DUTH
#define DUTH

#include <iostream>
#include <string>

using namespace std;


class DUT
{

   private:

        unsigned int NUM_COM;

        unsigned char PortStatus;


        void * HandlerCom;

        void SearchPort();


        string ModemMode;
        

    public:


        int SearchComPort();
        int GetComPort();

        bool ConnectPort();
        bool DisconnectPort();

        bool SetModemModeOnline();
        bool SetModemModeFTM();


        string GetModemMode();

        DUT();

        ~DUT();
};










//---------------------------------------------------------------------------
#endif
