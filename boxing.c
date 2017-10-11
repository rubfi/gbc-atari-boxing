#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include <time.h>

#include "back_t.h"
#include "back_m.h"
#include "back_p.h"
#include "player.h"

UWORD backPalCGB[] =
{
  backTilesCGBPal0c0,backTilesCGBPal0c1,backTilesCGBPal0c2,backTilesCGBPal0c3
};

UWORD playerPalCGB[] =
{
  playerCGBPal0c0,playerCGBPal0c1,playerCGBPal0c2,playerCGBPal0c3,
  playerCGBPal1c0,playerCGBPal1c1,playerCGBPal1c2,playerCGBPal1c3

};

int f = 0;  /* Counter for the points of Player 1*/
int g = 0;  /* Counter for the points of Player 2*/
int j = 100;
int k = 77;
int x = 60;
int y = 77;
int i;
int timeco;  /* Counter for the time */
int cont;
int conti;

///////////
void sound_on (void)
{
  NR52_REG = 0xF8U;
  NR51_REG = 0x00U;
  NR50_REG = 0xFFU;
}

hit ()
{
    NR41_REG = 0x21U;
    NR42_REG = 0xF1U;
    NR43_REG = 0x44U;
    NR44_REG = 0x80U;
    NR51_REG = 0xF7U;
  
}
nohit ()
{
    NR41_REG = 0x85U;
    NR42_REG = 0xF1U;
    NR43_REG = 0x44U;
    NR44_REG = 0xC0U;
    NR51_REG = 0xF7U;
  
}
ko_end ()
{
    NR21_REG = 0x84U;
    NR22_REG = 0xF0U;
    NR23_REG = 0x11U;
    NR24_REG = 0xC7U;
    NR51_REG = 0xF7U;
  
}

//////////

/***backandsprites()***************************************************
--> puts the background and the sprites onto screen
**********************************************************************/
void 	BackandSprites ()
{
	DISPLAY_OFF;
	HIDE_BKG;
	set_bkg_data(0,2,backTiles);
	set_bkg_palette(0,1,&backPalCGB[0]);
	set_bkg_tiles(0,0,backMapWidth,backMapHeight,backMap);
	SPRITES_8x8;
	set_sprite_palette(0,1,&playerPalCGB[0]);
	set_sprite_palette(1,1,&playerPalCGB[4]);
	set_sprite_data(0,26,player);
	for (i=0;i<=13;i++)
	{
		set_sprite_tile(i,i);
		set_sprite_prop(i+13,S_PALETTE | 1);
		set_sprite_prop(i+13,S_FLIPY | S_FLIPX | 1);
		set_sprite_tile(i+13,i);
	}
	DISPLAY_ON;
	SHOW_BKG;
	SHOW_SPRITES;
	sound_on();
}	


/***P1move()***********************************************************
--> Moves the player 1
**********************************************************************/

void P1move()
{
	if ( joypad() & J_A )        
   	{
		move_sprite (1,500,500);
		move_sprite (7,x+16,y-8);
		move_sprite (8,x+8,y-8);
   		for (cont=0;cont <=8;cont++)
		for (conti=0;conti <=8;conti++)
		if (((x + 12 - cont ) == (j-16)) &&( (y + conti -12) == k))
			{
				hit();
				f++;
				move_sprite (16,500,500);
				move_sprite (17,500,500);
				move_sprite (24,j,k);
				if ( j < 128)
					j = j+8;
				else
					j = 136;
				
				if (k < 96)  
					k = k+16;	
				else 
					k = 112;
				delay (25);	
			}
			 
		delay (25);
	}
	if ( joypad() & J_B)         
   	{
		move_sprite (6,500,500);
		move_sprite (9,x+16,y+8);
		move_sprite (10,x+8,y+8);
   		for (cont=0;cont <=8;cont++)
		for (conti=0;conti <=8;conti++)
		if (((x + 12 - cont ) == (j-16)) &&( (y + conti + 6) == k))
			{
				hit();
				f++;
				move_sprite (16,500,500);
				move_sprite (17,500,500);
				move_sprite (24,j,k);
				if ( j < 128)
					j = j+8;
				else
					j = 136;
				
				if ( k > 72)  
					k = k-16;
				else 
					k = 56;
					delay (25);	
			}
			delay (25);
		
	}
	if ( joypad() & J_UP)  
   	{
		if ( y > 56)  
   			y--;
			
	}
	if ( joypad() & J_DOWN)                
   	{
		if ( y < 112)  
   			y++;
			
	}
	if ( joypad() & J_RIGHT)
   	{
		if ( x < 128)  
   			if ( (j-x)>30)
				x++;
			
	}
	if ( joypad() & J_LEFT)        
   	{
		if ( x > 32)  
   			x--;
			
	}
}


/***P2move()***********************************************************
--> Moves the player 2
**********************************************************************/
p2move()
{
	if (y < k)
		if ( k < 112)
			if ((k-y) < 12)  
				k++;
			else
				k--;
   	if (y > k)
		if ( k > 56)
			if ((y-k) < 12)  
				k--;
			else
				k++;
	if (x > (j-28))
		if ( j < 136)
			j++;
	  
   	if (x < (j-28))
		j--;
}

/***p2movev2()*********************************************************
--> uses to give player 2 more movement ( f.e : Hits ) 
**********************************************************************/
p2movev2()
{
	switch (rand ()%10)
	{
		case 1:
		{	
			j= j-4;
			break;
		}
		case 2:
		{	
			if ( j < 136)
				j= j+4;
			break;
		}
		case 3:
		{	
			if ( k >= 60)
				k= k-4;
				break;
		}
		case 4:
		{	
			if ( k <= 108)
				k= k+4;
			break;
		}
		case 5:
		{	
			move_sprite (14,500,500);
			move_sprite (20,(j-16),(k-(0-8)));
			move_sprite (21,(j-8),(k-(0-8)));
			for (cont=0;cont <=8;cont++)
			for (conti=0;conti <=8;conti++)
			if (((j-12-cont) == (x+16)) &&((k+conti+6) == y))
			{
				nohit();
				g++;
				move_sprite (3,500,500);
				move_sprite (4,500,500);
				move_sprite (11,x,y);
				if ( x > 40)  
   					x = x-8;
				else 
					x=30;
				if ( y > 64)  
					y = y-16;
				else 
					y = 56;
				delay (25);	
			}
			delay (25);	
			break;
		}
		case 6:
		{	
			move_sprite (19,500,500);
			move_sprite (22,(j-16),(k-8));
			move_sprite (23,(j-8),(k-8));
			for (cont=0;cont <=8;cont++)
			for (conti=0;conti <=8;conti++)
			if (((j-12-cont) == (x+16)) && ((k+conti-12) == y))
			{
				nohit();
				g++;
				move_sprite (3,500,500);
				move_sprite (4,500,500);
				move_sprite (11,x,y);
				if ( x > 40)  
   					x = x-8;
				else 
					x=30;
				if (y < 104)  
					y = y+16;	
				else 
					y = 112;
				delay (25);	
			}
			delay (25);	
			break;
		}
		default:
		{
			p2move ();
		}
	}
}	

/***scores()***********************************************************
--> puts onto screen player's scores
**********************************************************************/
void scores ()
{
	
	if (f/10)
		set_sprite_tile(27,((f/10)-(-14)));
	set_sprite_tile(28,((f%10)-(-14)));
	set_sprite_prop(29,S_PALETTE | 1 );
	set_sprite_prop(30,S_PALETTE | 1 );
	if (g/10)
		set_sprite_tile(29,((g/10)-(-14)));
	set_sprite_tile(30,((g%10)-(-14)));
	move_sprite (27,44,16);
	move_sprite (28,52,16);
	move_sprite (29,108,16);
	move_sprite (30,116,16);
	if ((f == 100) || (g == 100))
	{
		ko_end();
		delay (4000);
		ko_end();
		reset();
	}	
}

/***timeCounter()******************************************************
--> timeCounter counts the time of the fight
**********************************************************************/

void timeCounter()
{
	timeco =(clock()/50);
	timeco = (120 - timeco);
	set_sprite_tile(31,((timeco/60)-(-14)));
	set_sprite_tile(32,(((timeco%60)/10)-(-14)));
	set_sprite_tile(33,(((timeco%60)%10)-(-14)));
	set_sprite_tile(34,25);
	set_sprite_prop(31,S_PALETTE | 1 );
	set_sprite_prop(32,S_PALETTE | 1 );
	set_sprite_prop(33,S_PALETTE | 1 );
	set_sprite_prop(34,S_PALETTE | 1 );
	move_sprite (31,68,24);
	move_sprite (34,76,24);
	move_sprite (32,84,24);
	move_sprite (33,92,24);
	if (timeco == 0)
	{
		ko_end();
		delay (4000);
		ko_end();
		reset();
	}	
}

/***movesprites()******************************************************
--> moves the sprites
**********************************************************************/

void movesprites()
{
		move_sprite (7,500,500);
		move_sprite (8,500,500);
		move_sprite (9,500,500);
		move_sprite (10,500,500);
		move_sprite (11,500,500);
		move_sprite (20,500,500);
		move_sprite (21,500,500);
		move_sprite (22,500,500);
		move_sprite (23,500,500);
		move_sprite (24,500,500);
			
		
		move_sprite (1,x+8,y-8);
		move_sprite (2,x,y-8);
		move_sprite (3,x,y);
		move_sprite (4,x+8,y);
		move_sprite (5,x,y+8);
		move_sprite (6,x+8,y+8);
		
		move_sprite (14,j-8,k+8);
		move_sprite (15,j,k+8);
		move_sprite (16,j,k);
		move_sprite (17,j-8,k);
		move_sprite (18,j,k-8);
		move_sprite (19,j-8,k-8);	
}




void main ()
{
	BackandSprites();
	while (1)
	{
		scores();
		timeCounter();
		movesprites();
		P1move();
   	      p2movev2();
		delay(25);
	}

}

