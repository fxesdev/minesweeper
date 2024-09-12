#include "base.h"
#include "light.h"
#include "dark.h"
#include "st_l.h"
#include "st_d.h"

#include "glider_gun.h"
//hi

word get_random(word max)
{
	return deref(0xF00D) % max;
}

void smtren(word addr)
{
    word i = 0;
    word j = 0;
    for(i = 0; i < 0x0600; i++)
    {
        j++;
        if((j & 0x001F) == 0x18)
        {
            j+=8;
        }
        *((word *)(0x9000 + j)) = *((word *)(addr + i));
    }
}

void cooler()
{
	word i = 0x8080;
	word j = 0;
	for(j=0;j<deref(i);j++)
	{
		deref(0x9000+i) = deref(i+1);
	}
}

void samtren(word addr)
{
    word i = 0;
    word j = 0;
    for(i = 0; i < 0x0600; i++)
    {
        j++;
        if((j & 0x001F) == 0x18)
        {
            j+=8;
        }
        *((word *)(0x9800 + j)) = *((word *)(addr + i));
    }
}

void delay(ushort after_ticks)
{
	if ((FCON & 2) != 0)
		FCON &= 0xfd;
	__DI();
	Timer0Interval = after_ticks;
	Timer0Counter = 0;
	Timer0Control = 0x0101;
	InterruptPending_W0 = 0;
	StopAcceptor = 0x50;
	StopAcceptor = 0xa0;
	StopControl = 2;
	__asm("nop");
	__asm("nop");
	__EI();
}

void set_pixel(word x, word y,byte color) {
	word addr = (y<<5) + (x >> 3) + 0xF800;
	byte ty = 0x80>>(x & 7);
	if(color)
	{
		val(addr) |= ty;
		return;
	}
	val(addr) &= ~ty;
}


void set_pixel_buf(word x, word y,byte color) {
	word addr = (y<<5) + (x >> 3) + 0x9800;
	byte ty = 0x80>>(x & 7);
	if(color)
	{
		val(addr) |= ty;
		return;
	}
	val(addr) &= ~ty;
}


enum SPECIAL_CHARS
{
	SP_EXE = 0x0F,
	SP_TAB = '\t',
	SP_SPACE = ' ',
	SP_BACKSPACE = '\b',

	SP_HOME = 0x2A,
	SP_END = 0x1A,
	SP_YES = 0x3A,
	SP_NO = 0x12,
	SP_OK = 0x21,
	SP_UP = 0x20,
	SP_DOWN = 0x22,
	SP_LEFT = 0x29,
	SP_RIGHT = 0x19,
	SP_PLUS = 0x10,
	SP_MINUS = 0x11,
	SP_ALT = 0x31,
	SP_ABC = 0x30,
	SP_ESC = 0x39,
	SP_SELECTLEFT,
	SP_SELECTRIGHT,
	SP_PASTE,
	SP_COPY,

	SPECIAL_MAX
};


byte lastbutton = 0xff;
byte CheckButtons()
{
	byte x;
	byte y;
	byte i = 0;
	for(x = 0x80; x != 0; x = x >> 1)
	{
		deref(0xf046) = x;
		for(y = 0x80; y != 0; y = y >> 1)
		{
			if((deref(0xf040) & y) == 0)
			{
				if(i != lastbutton)
				{
					lastbutton = i;
					return i;
				}
				return 0xff;
			}
			++i;
		}
	}
	lastbutton = 0x50;
	return 0xff;
}


void render()
{
	word i = 0;
	for(i=0;i<2048;i++)
	{
		//deref(0x9000+i) = deref(0x9800+i);
		deref(0xf037) = 0;
		deref(0xf800+i) = deref(0x9000+i);
		deref(0xf037) = 4;
		deref(0xf800+i) = deref(0x9800+i);
	}
}

void render_dark(word addr)
{
    word i = 0;
    word j = 0;
    for(i = 0; i < 0x0600; i++)
    {
        j++;
        if((j & 0x001F) == 0x18)
        {
            j+=8;
        }
        *((word *)(0x9800 + j)) = *((word *)(addr + i));
    }
}

void render_light(word addr)
{
    word i = 0;
    word j = 0;
    for(i = 0; i < 0x0600; i++)
    {
        j++;
        if((j & 0x001F) == 0x18)
        {
            j+=8;
        }
        *((word *)(0x9000 + j)) = *((word *)(addr + i));
    }
}

void draw_tile(word tile,word x,word y) {
	word i = 0;
	word j = 0;
	y*=8;
	for(i=0;i<8;i++) {
		deref(0xf037) = 0;
		deref(0xF800+x+(y<<5)) = *(light_data + (tile<<3)+i);
		deref(0xf037) = 4;
		deref(0xF800+x+(y<<5)) = *(dark_data + (tile<<3)+i);

		y++;
	}
}
void draw_tile3(word tile,word x,word y) {
	word i = 0;
	word j = 0;
	y*=8;
	for(i=0;i<8;i++) {
		deref(0xf037) = 0;
		deref(0xF800+x+(y<<5)) |= *(light_data + (tile<<3)+i);
		deref(0xf037) = 4;
		deref(0xF800+x+(y<<5)) |= *(dark_data + (tile<<3)+i);

		y++;
	}
}
void draw_tile2(word x,word y) {
	word i = 0;
	word j = 0;
	y*=8;
	for(i=0;i<8;i++) {
		deref(0xf037) = 0;
		deref(0xF800+x+(y<<5)) = deref(0x9800+i);
		deref(0xf037) = 4;
		deref(0xF800+x+(y<<5)) = deref(0x9808+i);

		y++;
	}
}
void set_tile2(word x,word y) {
	word i = 0;
	word j = 0;
	y*=8;
	for(i=0;i<8;i++) {
		deref(0xf037) = 0;
		deref(0x9800+i) = deref(0xF800+x+(y<<5));
		deref(0xf037) = 4;
		deref(0x9808+i) = deref(0xF800+x+(y<<5));

		y++;
	}
}
void set_tile(word tile,word x, word y) {
	deref(0x9000+x+(y*24)) = tile;
}
word get_tile(word x, word y) {
	if(x<0||x>23||y<0||y>7) {
		return 10;
	}
	return deref(0x9000+x+(y*24));
}

void lose() {
	word i = 0;
	word j = 0;
	for(i=0;i<24;i++) {
		for(j=0;j<8;j++) {
			draw_tile(get_tile(i,j),i,j);
		}
	}
	custom_break();
}

void reveal_tiles_5(word x,word y) {
	word coloffset = 0;
	word rowoffset = 0;

	for(coloffset = 0;coloffset <= 2; coloffset++) {
		for(rowoffset = 0;rowoffset <= 2; rowoffset++) {
			if(rowoffset == 1 && coloffset == 1) {
				continue;
			}
			draw_tile(get_tile(x+coloffset-1,y+rowoffset-1),x+coloffset-1,y+rowoffset-1);
			deref(0x9901) += 1;
			//reveal_tiles(x+coloffset-1,y+rowoffset-1);
		}
	}
}

void reveal_tiles_4(word x,word y) {
	word coloffset = 0;
	word rowoffset = 0;

	for(coloffset = 0;coloffset <= 2; coloffset++) {
		for(rowoffset = 0;rowoffset <= 2; rowoffset++) {
			if(rowoffset == 1 && coloffset == 1) {
				continue;
			}
			draw_tile(get_tile(x+coloffset-1,y+rowoffset-1),x+coloffset-1,y+rowoffset-1);
			if(get_tile(x+coloffset-1,y+rowoffset-1)==11) {
				reveal_tiles_5(x+coloffset-1,y+rowoffset-1);
			}
			deref(0x9901) += 1;
			//reveal_tiles(x+coloffset-1,y+rowoffset-1);
		}
	}
}

void reveal_tiles_3(word x,word y) {
	word coloffset = 0;
	word rowoffset = 0;

	for(coloffset = 0;coloffset <= 2; coloffset++) {
		for(rowoffset = 0;rowoffset <= 2; rowoffset++) {
			if(rowoffset == 1 && coloffset == 1) {
				continue;
			}
			draw_tile(get_tile(x+coloffset-1,y+rowoffset-1),x+coloffset-1,y+rowoffset-1);
			if(get_tile(x+coloffset-1,y+rowoffset-1)==11) {
				reveal_tiles_4(x+coloffset-1,y+rowoffset-1);
			}
			deref(0x9901) += 1;
			//reveal_tiles(x+coloffset-1,y+rowoffset-1);
		}
	}
}

void reveal_tiles_2(word x,word y) {
	word coloffset = 0;
	word rowoffset = 0;

	for(coloffset = 0;coloffset <= 2; coloffset++) {
		for(rowoffset = 0;rowoffset <= 2; rowoffset++) {
			if(rowoffset == 1 && coloffset == 1) {
				continue;
			}
			draw_tile(get_tile(x+coloffset-1,y+rowoffset-1),x+coloffset-1,y+rowoffset-1);
			if(get_tile(x+coloffset-1,y+rowoffset-1)==11) {
				reveal_tiles_3(x+coloffset-1,y+rowoffset-1);
			}
			deref(0x9901) += 1;
			//reveal_tiles(x+coloffset-1,y+rowoffset-1);
		}
	}
}

void reveal_tiles(word x,word y) {
	word coloffset = 0;
	word rowoffset = 0;

	for(coloffset = 0;coloffset <= 2; coloffset++) {
		for(rowoffset = 0;rowoffset <= 2; rowoffset++) {
			if(rowoffset == 1 && coloffset == 1) {
				continue;
			}
			draw_tile(get_tile(x+coloffset-1,y+rowoffset-1),x+coloffset-1,y+rowoffset-1);
			if(get_tile(x+coloffset-1,y+rowoffset-1)==11) {
				reveal_tiles_2(x+coloffset-1,y+rowoffset-1);
			}

			deref(0x9901) += 1;
			//reveal_tiles(x+coloffset-1,y+rowoffset-1);
		}
	}
}

void start_screen() {
	byte button = 0;
	render_dark(st_dd);
	render_light(st_ll);
	render();
	while(1) {
		button = CheckButtons();
		if(button==SP_EXE) {
			break;
		}
	}
}

void main() {
	word i = 0;
	word j = 0;
	word k = 0;
	word z = 0;
	word cus_x = 0;
	word px = -1;
	word cus_y = 0;
	word py = -1;
	byte bomb = 0;
	byte first_button = 1;
	byte button = 0;
	word bx = 0;
	word by = 0;
	deref(0xf034) = 0x06;
	deref(0xf036) = 0x08;
	deref(0x9900) = 0;
	deref(0x9901) = 0;
	start_screen();

	for(i=0;i<24;i++) {
		for(j=0;j<8;j++) {
			if(get_random(get_random(10))==1) {
				bomb = 9;
				deref(0x9900) += 1;
			} else {
				bomb = 11;
			}
			set_tile(bomb,i,j);
			draw_tile(10,i,j);
		}
	}
	for(i=0;i<24;i++) {
		for(j=0;j<8;j++) {
			if(get_sum(i,j)==0||get_tile(i,j)==9) {
				//set_tile(10,i,j);
				continue;
			}
			set_tile(get_sum(i,j)-1,i,j);
			//draw_tile(get_sum(i,j)-1,i,j);
		}
	}
	while(1) {
		button = CheckButtons();
		if(button==0xFF) {
			continue;
		}
		if(button==SP_DOWN) {
			cus_y++;
		} else if(button==SP_LEFT) {
			cus_x--;
		} else if(button==SP_RIGHT) {
			cus_x++;
		} else if(button==SP_UP) {
			cus_y--;
		} else if(button==0x0B) {
			if(get_tile(cus_x,cus_y)==8) {
				draw_tile(10,cus_x,cus_y);
			} else {
				draw_tile(8,cus_x,cus_y);
			}
			set_tile2(cus_x,cus_y);
		} else if(button==SP_EXE) {
			if(get_tile(cus_x,cus_y)==9) {
				lose();
			}
			draw_tile(get_tile(cus_x,cus_y),cus_x,cus_y);
			deref(0x9901) += 1;
			if(get_tile(cus_x,cus_y)==11) {
				reveal_tiles(cus_x,cus_y);
			}
			set_tile2(cus_x,cus_y);
			first_button = 0;
			continue;
			//custom_break();
		}
		draw_tile2(px,py);
		if(cus_y==-1) {
			cus_y = 7;
		}
		if(cus_x==-1) {
			cus_x = 23;
		}
		if(cus_y==8) {
			cus_y = 0;
		}
		if(cus_x==24) {
			cus_x = 0;
		}
		py = cus_y;
		px = cus_x;
		set_tile2(cus_x,cus_y);
		draw_tile3(12,cus_x,cus_y);
		//draw_tile2(px,py);
	}
}
byte bomb_here(word x, word y) {
	if(get_tile(x,y) == 9) {
		return 1;
	}
	return 0;
}

word get_sum(word x, word y) {
	return bomb_here(x-1,y-1) + bomb_here(x,y-1) + bomb_here(x+1,y-1) + bomb_here(x+1,y) + bomb_here(x+1,y+1) + bomb_here(x,y+1) + bomb_here(x-1,y+1) + bomb_here(x-1,y);
}
void conway() {
	word i = 0;
	word dl = 0x201;
	word j = 0;
	byte curr = 0;
	byte sum = 0;
	deref(0xf034) = 0x06;
	deref(0xf036) = 0x08;

	for(i=0;i<2048;i++)
	{
		deref(0xf037) = 0;
		deref(0xf800+i) = 0;
		deref(0xf037) = 4;
		deref(0xf800+i) = 0;
	}
	for(i=0;i<2048;i++)
	{
		deref(0x9000+i) = deref(*gg+i);
		deref(0x9800+i) = deref(*gg+i);
	}
	while(1)
	{
		for(i=0;i<192;i++)
		{
			for(j=1;j<63;j++)
			{
				curr = (val((j<<5)+(i>>3)+0x9000)&(0x80>>(i&7)))?1:0;
				sum = get_pixel(i,j-1) + get_pixel(i+1,j-1) + get_pixel(i+1,j) + get_pixel(i+1,j+1) + get_pixel(i,j+1) + get_pixel(i-1,j+1) + get_pixel(i-1,j) + get_pixel(i-1,j-1);
				if(curr==1)
				{
					if(sum==2||sum==3)
					{
						set_pixel_buf(i,j,1);
						continue;
					}
					set_pixel_buf(i,j,0);
					continue;
				}
				if(sum==3)
				{
					set_pixel_buf(i,j,1);
				}
			}
		}
		render();
	}


}

byte get_pixel(word x, word y)
{

    return(val((y<<5)+(x>>3)+0x9000)&(0x80>>(x&7)))?1:0;
}

/*
void plot_line (int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  for (;;){
    set_pixel (x0,y0);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}
*/
void custom_break()
{
	while(1)
	{

	}
}
