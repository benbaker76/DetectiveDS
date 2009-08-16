#include <nds.h>
#include <stdio.h>

int main(void)
{
	touchPosition touch;

	consoleDemoInit();

	iprintf("\n\n\tThe Detective Game\n");

	while(1)
	{

		touchRead(&touch);
		iprintf("\x1b[10;0HTouch x = %04i, %04i\n", touch.rawx, touch.px);
		iprintf("Touch y = %04i, %04i\n", touch.rawy, touch.py);

		swiWaitForVBlank();
	}

	return 0;
}
