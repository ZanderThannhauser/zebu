
#ifndef ZEBU_LINE_NUMBERS
#define ZEBU_LINE_NUMBERS (0)
#endif

#ifndef ZEBU_COLUMN_NUMBERS
#define ZEBU_COLUMN_NUMBERS (0)
#endif

#ifndef ZEBU_TREE_DEPTH
#define ZEBU_TREE_DEPTH (0)
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static const enum state {
	s_reject,
	s_accept,
	
	s_start,
	
	s_escape,
	s_csi,
	
	s_insert,
	s_backspace,
	
	s_move_up,
	s_move_down,
	s_move_left,
	s_move_right,
	s_move_leftmost,
	s_move_rightmost,
	
	number_of_states,
} lookup[number_of_states][256] = {
	[s_start]['a' ... 'z'] = s_insert,
	[s_start]['A' ... 'Z'] = s_insert,
	[s_start]['0' ... '9'] = s_insert,
	[s_start][' '] = s_insert,
	
	[s_start][0x7F] = s_backspace,
	
	[s_start][0x1B] = s_escape,
	
	[s_escape]['['] = s_csi,
	
	[s_csi]['A'] = s_move_up,
	[s_csi]['B'] = s_move_down,
	[s_csi]['D'] = s_move_left,
	[s_csi]['C'] = s_move_right,
	
	[s_csi]['H'] = s_move_leftmost,
	[s_csi]['F'] = s_move_rightmost,
};

int main()
{
	#if 0
	if (!isatty(0))
	{
		assert(!"TODO");
	}
	#endif
	
	// disable ICANON:
	{
		struct termios termios;
		tcgetattr(0, &termios);
		termios.c_lflag &= ~ICANON;
		termios.c_lflag &= ~ECHO;
		tcsetattr(0, TCSAFLUSH, &termios);
	}
	
	struct {
		struct a {
			struct {
				unsigned char red, green, blue;
			} foreground, background;
			char codepoint;
		}* data;
		unsigned size;
		unsigned cursor;
	} current = {}, published = {};
	
	void republish()
	{
		if (published.size < current.size)
		{
			fflush(stdout);
			
			published.data = realloc(published.data, sizeof(*published.data) * current.size);
			memset(published.data + published.size, 0, sizeof(*published.data) * (current.size - published.size));
			published.size = current.size;
		}
		
		bool changed = false;
		
		for (unsigned i = 0, n = current.size; i < n; i++)
		{
			struct a* c = &current.data[i], *p = &published.data[i];
			
			if (false
				|| c->foreground.red   != p->foreground.red
				|| c->foreground.green != p->foreground.green
				|| c->foreground.blue  != p->foreground.blue
				|| c->background.red   != p->background.red
				|| c->background.green != p->background.green
				|| c->background.blue  != p->background.blue
				|| c->codepoint        != p->codepoint)
			{
				printf("\e[%uG\e[38;2;%u;%u;%u;48;2;%u;%u;%um%c", i + 1,
					c->foreground.red,
					c->foreground.green,
					c->foreground.blue,
					c->background.red,
					c->background.green,
					c->background.blue,
					c->codepoint);
				*p = *c;
				changed = true;
			}
		}
		
		if (changed || published.cursor != current.cursor)
		{
			printf("\e[%uG", current.cursor + 1);
			published.cursor = current.cursor;
			fflush(stdout);
		}
	}
	
	void set(unsigned index, struct a a)
	{
		while (index >= current.size)
		{
			current.size = current.size << 1 ?: 1;
			current.data = realloc(current.data, sizeof(*current.data) * current.size);
		}
		
		current.data[index] = a;
	}
	
	set(0, (struct a) { {100, 100, 100}, {0, 0, 0}, '>'});
	set(1, (struct a) { {150, 150, 150}, {0, 0, 0}, '>'});
	set(2, (struct a) { {200, 200, 200}, {0, 0, 0}, '>'});
	
	set(3, (struct a) { {255, 255, 255}, {0, 0, 0}, ' '});
	
	current.cursor = 4;
	
	republish();
	
	struct {
		char* data;
		unsigned n, cap;
	} text = {};
	
	unsigned insertion_point = 0;
	
	enum state state = s_start;
	
	for (unsigned char c; read(0, &c, 1) == 1; )
	{
		switch ((state = lookup[state][c]))
		{
			case s_accept:
				assert(!"TODO");
				break;
			
			case s_reject:
				printf("c == 0x%hhx!\n", c);
				assert(!"TODO");
				break;
			
			case s_escape: break;
			
			case s_csi: break;
			
			case s_insert:
			{
				if (text.n == text.cap)
				{
					text.cap = text.cap << 1 ?: 1;
					text.data = realloc(text.data, sizeof(*text.data) * text.cap);
				}
				
				memmove(text.data + insertion_point + 1, text.data + insertion_point, text.n - insertion_point);
				
				text.data[insertion_point++] = c, text.n++;
				
				current.cursor++;
				
				for (unsigned i = 0, n = text.n; i < n; i++)
					set(i + 4, (struct a) { {240, 240, 240}, {0, 0, 0}, text.data[i]});
				
				republish();
				
				state = s_start;
				break;
			}
			
			case s_backspace:
			{
				if (insertion_point > 0)
				{
					memmove(text.data + insertion_point - 1, text.data + insertion_point, text.n - insertion_point);
					
					text.n--;
					
					insertion_point--;
					
					current.cursor--;
					
					for (unsigned i = 0, n = text.n; i < n; i++)
						set(i + 4, (struct a) { {240, 240, 240}, {0, 0, 0}, text.data[i]});
					
					set(text.n + 4, (struct a) { {240, 240, 240}, {0, 0, 0}, ' '});
					
					republish();
				}
				
				state = s_start;
				break;
			}
			
			case s_move_up:
			{
				state = s_start;
				break;
			}
			
			case s_move_down:
			{
				state = s_start;
				break;
			}
			
			case s_move_left:
			{
				if (insertion_point > 0)
				{
					insertion_point--, current.cursor--;
					
					republish();
				}
				
				state = s_start;
				break;
			}
			
			case s_move_right:
			{
				if (insertion_point < text.n)
				{
					insertion_point++, current.cursor++;
					
					republish();
				}
				
				state = s_start;
				break;
			}
			
			case s_move_leftmost:
			{
				insertion_point = 0, current.cursor = 4;
				republish();
				state = s_start;
				break;
			}
			
			case s_move_rightmost:
			{
				insertion_point = text.n, current.cursor = text.n + 4;
				republish();
				state = s_start;
				break;
			}
			
			default:
				assert(!"TODO");
				break;
		}
	}
	
	// enable ICANON:
	{
		struct termios termios;
		tcgetattr(0, &termios);
		termios.c_lflag |= ICANON;
		termios.c_lflag |= ECHO;
		tcsetattr(0, TCSAFLUSH, &termios);
	}
	
	return 0;
}










