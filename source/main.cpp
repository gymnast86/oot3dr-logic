/*==============================================|
|                 NON-3DS MAIN                  |
|==============================================*/
#ifndef __3DS__
#include "generate.hpp"
#include "utility/log.hpp"

int main()
{
    int retVal = GenerateRandomizer();
    if (retVal != 0)
    {
        std::cout << ErrorLog::getInstance().getLastErrors() << std::endl;
    }
    CloseLogs();
}
#endif

/*==============================================|
|                   3DS MAIN                    |
|==============================================*/
#ifdef __3DS__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include "generate.hpp"
#include "utility/log.hpp"

int main(int argc, char* argv[])
{
  	gfxInitDefault();
  	consoleInit(GFX_TOP, NULL);

    Result rc = romfsInit();
    if (rc)
    {
        printf("romfsInit: %08lX\n", rc);
    }

  	// Main loop
  	while (aptMainLoop())
  	{
    		gspWaitForVBlank();
    		gfxSwapBuffers();
    		hidScanInput();

    		// Your code goes here
    		u32 kDown = hidKeysDown();
    		if (kDown & KEY_START)
    			 break; // break in order to return to hbmenu
        if (kDown & KEY_A)
        {
            int retVal = GenerateRandomizer();
            if (retVal != 0)
            {
                std::cout << ErrorLog::getInstance().getLastErrors() << std::endl;
            }
            CloseLogs();
        }
  	}

  	gfxExit();
  	return 0;
}
#endif
