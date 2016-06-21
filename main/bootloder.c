#include "include.h"
#include "bootloader.h"

#define MENU	"		\"u\": Upload User Application Firmware" \
							"		\"a\": Get the version of the current application"	\
							"		\"b\": Get the version of the current bootloader"	\
							"		\"q\": Quit"

extern volatile uint8_t UARTBuffer[BUFSIZE];

void print_menu(void)
{
	_PRINT_("Commands:");
	_PRINT_(MENU);
}

static void initAppBufData(uint32_t *startAddr)
{
	uint32_t* pAppBuffer = startAddr;
	while(pAppBuffer < pAppBuffer + 0x1000)
	{
		*pAppBuffer = 0;
		pAppBuffer += 4;
	}
}

static int uploadApp(void)
{
	int retval = 0;
	uint8_t recvEndAddr;
	uint32_t flashMemory = APP_ADDR_START;
	uint32_t blockNum = 0;
	uint32_t recvCnt = 0;
	uint8_t* pAppBuffer = (uint8_t *)FLASH_BUFFER_ADDR;
	
	__disable_irq();
	
	/* Erase the last sector which includes the application id */
	retval = EraseSector(LAST_SECTOR_ADDR);
	if (0 != retval)
		return retval;
	
	/* receive user application firmware data */
	retval = receiveAppData(&recvCnt, (uint8_t *)&recvEndAddr);
	if (0 != retval)
		return retval;	
	
	/* receive firmware data */
	while(1)
	{	
		pAppBuffer = (uint8_t *)FLASH_BUFFER_ADDR + (blockNum << 10);
		if (*pAppBuffer > recvEndAddr)	// reach at receive address tail
		{
			EraseSector(recvEndAddr);
			break;
		}			
		
		/* Write flash */
		flashMemory = APP_ADDR_START + (blockNum << 10);
		
		if (blockNum%4 == 0)
		{
			initAppBufData((uint32_t *)pAppBuffer);
			retval = EraseSector(flashMemory);
		}
		
		/* Write App data to falsh */
		if (0 == retval)
			retval = ProgramPage(flashMemory, APP_DATA_BLOCK_SIZE, pAppBuffer);
		
		if (0 == retval)
		{
			blockNum++;
			continue;
		}
		else
			break;
	}
	
	__enable_irq();
	
	return retval;
}

static int receiveAppData(uint32_t* pRecvCnt, uint8_t* recvEndAddr)
{
	uint8_t* pAppBuffer = (uint8_t *)FLASH_BUFFER_ADDR;
	
	if (pRecvCnt == NULL)
		return (1);
	
	*pRecvCnt = UART_ReveiveDown(&pAppBuffer);
	recvEndAddr = pAppBuffer;
	
	return 0;
}

static int runNewApp(void)
{
	USER_ENTRY_PFN user_entry;
	user_entry = (USER_ENTRY_PFN)*((uint32_t *)(APP_ADDR_START +4));
	(user_entry)();
	return 0;
}

int c_entry()
{
	uint8_t ch;
//	int retval = 0;
	
	UART_Init();		// baudrate: 115200
	print_menu();
	
	while(1)
	{
		_PRINT_("\r\n>");
		ch = _GET_C;
		_PRINT_C(ch);
		_PRINT_("");	// new line
		switch(ch)
		{
			case 'u':
			case 'U':
				_PRINT_("Upload User Application Firmware");
				if (0 == uploadApp())
					runNewApp();
				break;
			case 'a':
			case 'A':
				_PRINT_("Read Current App Version ID...");
				break;
			case 'b':
			case 'B':
				_PRINT_("Read Current Bootloader Version ID...");
				break;
			case 'q':
			case 'Q':
				goto end_program;
			default:
				continue;
		}
	}
	
end_program:
	while(1);
}

int main()
{
	return c_entry();
}

