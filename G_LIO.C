/*
	グラフィックライブラリ
*/
#include <dos.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

union REGS		inregs,outregs;
struct SREGS	segregs;
unsigned int	DSEG,GSEG;
unsigned int	IRET = 0xcfcf;

void	setb(int adr,int dat)
{
	movedata(DSEG,&dat,GSEG,adr,1);
}

void	setw(int adr,int dat)
{
	movedata(DSEG,&dat,GSEG,adr,2);
}

void	lio(int intno)
{
	inregs.x.bx = 0;
	segregs.ds = GSEG;
	int86x(intno,&inregs,&outregs,&segregs);
}

void	g_init()
{
	int	i;
	unsigned WORK;
	char	*gwork;
	if((gwork = malloc(0x1400)) == 0){
		fputs("g_lio : メモリが足りません\n",stderr);
	}
	segread(&segregs);
	DSEG = segregs.ds;
	GSEG = DSEG + (int)gwork/16;
	WORK = 0xf990;
	for(i=0; i<16; i++){
		movedata(0xf990,6+i*4,0x0000,0xa0*4+i*4,2);
		movedata(DSEG,&WORK,0x0000,0xa0*4+i*4+2,2);
	}
	movedata(0xf990,6+16*4,0x0000,0xce*4,2);
	WORK = (unsigned)&IRET;
	movedata(DSEG,&WORK,0x0000,0xc5*4,2);
	movedata(DSEG,&DSEG,0x0000,0xc5*4+2,2);
	lio(0xa0);
}

void	g_screen(int act,int dsp)
{
	setb(0,3);
	setb(1,0);
	setb(2,act);
	setb(3,dsp);
	lio(0xa1);
}

void	g_cls()
{
	lio(0xa5);
}

void	g_palete(int a,int b)
{
	setb(0,a);
	setb(1,b);
	lio(0xa4);
}

void	g_line(int x0,int y0,int x1,int y1,int col,int func)
{
	static int	sw[]={0,1,2,0x100,0x101,0x102,0x202};
	setw(0,x0);		setw(2,y0);
	setw(4,x1);		setw(6,y1);
	setb(8,col);
	setw(9,sw[func]);
	setb(13,0xff);
	setw(16,DSEG);
	lio(0xa7);
}

void	g_circle(int x,int y,int r,int c)
{
	setw(0,x);
	setw(2,y);
	setw(4,r);
	setw(6,r);
	setb(8,c);
	setb(9,0);
	setw(21,DSEG);
	lio(0xa8);
}

void	g_paint(int x,int y,int c1,int c2)
{
	setw(0,x);
	setw(2,y);
	setb(4,c1);
	setb(5,c2);
	setw(6,0x0a00);
	setw(8,0x06a0);
	lio(0xa9);
}

void	g_get(int x1,int y1,int x2,int y2,int *dat,int leng)
{
	setw(0,x1);		setw(2,y1);
	setw(4,x2);		setw(6,y2);
	setw(8,(int)dat);
	setw(10,DSEG);
	setw(12,leng);
	lio(0xab);
}

void	g_put(int x,int y,int *dat,int leng,int mode,int sw,int c1,int c2)
{
	setw(0,x);		setw(2,y);
	setw(4,(int)dat);
	setw(6,DSEG);
	setw(8,leng);
	setb(10,mode);
	setb(11,sw);
	setb(12,c1);
	setb(13,c2);
	lio(0xac);
}
