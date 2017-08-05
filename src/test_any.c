#include "test_any.h"

void run_test_any()
{
		int tmp=0;
	int t;
	int R1=0x00004000;//16384
	int A1 =0x00000001;//
	int d1 =0x00008000;//32768
	int f1= 0xFFFFFFFF;
	

	tmp = tmp|R1;
	tmp = tmp|A1;

	 t = tmp&R1;
	 t=tmp&A1;
}
