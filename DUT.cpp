//---------------------------------------------------------------------------


#pragma hdrstop

#include "DUT.h"

#include "QLib.h"



//---------------------------------------------------------------------------

// #pragma package(smart_init)


  DUT::DUT()
  {
      HandlerCom=NULL;
      NUM_COM=999;
      PortStatus=0x00;

  }


  DUT::~DUT()
  {
         if (HandlerCom!=NULL)

         DisconnectPort();



  }

   void DUT::SearchPort()
   {

    const unsigned char c_iPortListSize = 20;
    unsigned short _iPortListSize = 20;
    unsigned short _aiPortList[ c_iPortListSize ];
    unsigned short  port_get;
    const unsigned short c_iIgnorePortListSize = 2;
    unsigned short c_aiIgnorePortList[ c_iIgnorePortListSize ] = {1,2};


   QLIB_SetLibraryMode(false);

   

       // port_get=0;

         // If ports are to be ignored, they can be put into this list.  This will make the
         // process of autodetecting faster, if fewer ports are being scanned.
         //  Values of 0 are "don't cares" since this is an invalid port #


         // Get the port list
         NUM_COM=999;

         if ( QLIB_GetAvailablePhonesPortList( &_iPortListSize, _aiPortList, c_iIgnorePortListSize, &c_aiIgnorePortList[0] ) )
         {

            if(_iPortListSize!=0)
             NUM_COM=int(_aiPortList[0]);



         }


   }


   bool DUT::ConnectPort()
   {


     if (NUM_COM!=999)

        {

                HandlerCom=QLIB_ConnectServerWithWait(NUM_COM,2000);


                if( HandlerCom==NULL)

                       return false;


                else
                {
                      PortStatus= QLIB_IsPhoneConnected(HandlerCom);

                      return true;
                }

        }
        return false;

   }


   bool DUT::DisconnectPort()
   {
        if (PortStatus!=0)
        {
                QLIB_DisconnectServer(HandlerCom);
                return true;
        }

         else

                return  false;
   }


   int DUT::GetComPort()
   {

        
         return NUM_COM;

   }


   int DUT::SearchComPort()
   {
        SearchPort();
        return NUM_COM;
   }




   bool DUT::SetModemModeOnline()
   {

       unsigned char result;

      /*

        MODE_OFFLINE_A_F = 0,    //!<' Go to offline analog
        MODE_OFFLINE_D_F = 1,    //!<' Go to offline digital
        MODE_RESET_F = 2,        //!<' Reset. Only exit from offline
        MODE_FTM_F = 3,          //!<' FTM mode
        MODE_ONLINE_F = 4,       //!<' Go to Online
        MODE_LPM_F = 5,          //!<' Low Power Mode (if supported)
        MODE_POWER_OFF_F = 6,    //!<' Power off (if supported)
        MODE_MAX_F = 7           //!<' Last (and invalid) mode enum value

        */

        result=QLIB_DIAG_CONTROL_F(HandlerCom,4);

        if (result==0)     return false;
         
        return true;



   }

   bool DUT::SetModemModeFTM()
   {
        unsigned char result;

      /*

        MODE_OFFLINE_A_F = 0,    //!<' Go to offline analog
        MODE_OFFLINE_D_F = 1,    //!<' Go to offline digital
        MODE_RESET_F = 2,        //!<' Reset. Only exit from offline
        MODE_FTM_F = 3,          //!<' FTM mode
        MODE_ONLINE_F = 4,       //!<' Go to Online
        MODE_LPM_F = 5,          //!<' Low Power Mode (if supported)
        MODE_POWER_OFF_F = 6,    //!<' Power off (if supported)
        MODE_MAX_F = 7           //!<' Last (and invalid) mode enum value

        */

        result=QLIB_DIAG_CONTROL_F(HandlerCom,3);

        if (result==0)     return false;
         
        return true;

   
   }





    string DUT::GetModemMode()
   {


       
        unsigned char result;
        unsigned long modemMode=0;

//acquire current operation mode

        result=QLIB_GetPhoneOperatingMode(HandlerCom,&modemMode);
/*


        SYS_OPRT_MODE_PWROFF        = 0,   //!< ' Phone is powering off
        SYS_OPRT_MODE_FTM           = 1,   //!< ' Phone is in factory test mode
        SYS_OPRT_MODE_OFFLINE       = 2,   //!< ' Phone is offline
        SYS_OPRT_MODE_OFFLINE_AMPS  = 3,   //!< ' Phone is offline analog
        SYS_OPRT_MODE_OFFLINE_CDMA  = 4,   //!< ' Phone is offline cdma
        SYS_OPRT_MODE_ONLINE        = 5,   //!< ' Phone is online
        SYS_OPRT_MODE_LPM           = 6,   //!< ' Phone is in LPM - Low Power Mode
        SYS_OPRT_MODE_RESET         = 7,   //!< ' Phone is resetting - i.e. power-cycling
        SYS_OPRT_MODE_NET_TEST_GW   = 8,   //!< ' Phone is conducting network test for GSM/WCDMA.
        SYS_OPRT_MODE_OFFLINE_IF_NOT_FTM = 9, //!< ' offline request during powerup.
        SYS_OPRT_MODE_PSEUDO_ONLINE = 10, //!< ' Phone is pseudo online, tx disabled

        modemMode=0 Powering off
        modemMode=1 FTM mode
        modemMode=5 online mode
   */
        if (result!=0)
        {

                switch(modemMode)
                {
                        case 0:  ModemMode="Powering off";      break;
                        case 1:  ModemMode="FTM mode";          break;
                        case 2:  ModemMode="Offline mode";      break;
                        case 3:  ModemMode="Offline analog";    break;
                        case 4:  ModemMode="offline cdma";      break;
                        case 5:  ModemMode="Online mode";       break;
                        case 6:  ModemMode="Low Power Mode";    break;
                        case 7:  ModemMode="Reset...";          break;
                        case 8:  ModemMode="network test...";   break;
                        case 9:  ModemMode="offline request...";break;
                        case 10: ModemMode="Pseudo online";     break;
                        default: ModemMode=" ";                 break;
                }
        }

         return ModemMode;
   }




