	.set noreorder

#include "pspstub.s"


	STUB_START "sceImpose_driver",0x40090000,0x00010005
	STUB_FUNC  0x810FB7FB,sceImposeSetParam
	STUB_END


