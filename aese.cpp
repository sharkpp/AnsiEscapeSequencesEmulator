/**
 * aese is An ANSI Escape Sequences Emulator
 *
 * @author     sharkpp
 * @license    MIT License
 * @copyright  2013+ sharkpp
 * @link       https://www.sharkpp.net/
 */

#include  <stdio.h>
#include  <windows.h>

// cl aesc.cpp

// http://ascii-table.com/ansi-escape-sequences.php
// http://en.wikipedia.org/wiki/ANSI_escape_sequences
// http://ttssh2.sourceforge.jp/manual/ja/about/ctrlseq.html
int main()
{
	HANDLE hStdIn  = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbiDefault = { sizeof(CONSOLE_SCREEN_BUFFER_INFO) };
	GetConsoleScreenBufferInfo(hStdOut, &csbiDefault);

	TCHAR buff[4096];
	DWORD len;
	while( 0 < ReadFile(hStdIn, buff, sizeof(buff), &len, NULL) )
	{
		TCHAR* p  = buff;
		TCHAR* pa = buff;
		TCHAR* last = buff + len;
		for(TCHAR* last = buff + len; p < last; )
		{
			if( 0x1B == *p ) {
				WriteFile(hStdOut, pa, size_t(p - pa), &len, NULL);
				// ESC [ 
				TCHAR* pEsc = p;
				p++; // ESC
				if( p < last && '[' == *p ) {
					p++; // [
					if( p < last ) {
						for(; p < last && (';' == *p || ('0' <= *p && *p <= '9')); p++);
						TCHAR c = *p++; // あとでチェックを実装
						//
//	TCHAR tmp[1024] = {};memcpy(tmp, pEsc + 1, size_t(p - pEsc - 1));printf("'ESC%s'", tmp);
						switch(c)
						{
						case 'm': { // Set Graphics Mode
							CONSOLE_SCREEN_BUFFER_INFO csbi = { sizeof(CONSOLE_SCREEN_BUFFER_INFO) };
							GetConsoleScreenBufferInfo(hStdOut, &csbi);
							TCHAR* pb = pEsc + 2;
							for(; pb && *pb && (';' == *pb || ('0' <= *pb && *pb <= '9'));) {
								int attr = strtol(pb, &pb, 10);
								if( !pb || !*pb ) {
									break;
								}
								if( ';' == *pb || c == *pb ) {
									pb++;
								}
								const WORD wFgColors[] = {
									/* Black   */	0,
									/* Red     */	FOREGROUND_RED,
									/* Green   */	FOREGROUND_GREEN,
									/* Yellow  */	FOREGROUND_RED|FOREGROUND_GREEN,
									/* Blue    */	FOREGROUND_BLUE,
									/* Magenta */	FOREGROUND_RED|FOREGROUND_BLUE,
									/* Cyan    */	FOREGROUND_GREEN|FOREGROUND_BLUE,
									/* White   */	FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
									};
								const WORD wBgColors[] = {
									/* Black   */	0,
									/* Red     */	BACKGROUND_RED,
									/* Green   */	BACKGROUND_GREEN,
									/* Yellow  */	BACKGROUND_RED|BACKGROUND_GREEN,
									/* Blue    */	BACKGROUND_BLUE,
									/* Magenta */	BACKGROUND_RED|BACKGROUND_BLUE,
									/* Cyan    */	BACKGROUND_GREEN|BACKGROUND_BLUE,
									/* White   */	BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE,
									};
								switch(attr)
								{
								case 0: // All attributes off
									csbi.wAttributes = csbiDefault.wAttributes;
									break;
								case 1: // Bold on
									break;
								case 4: // Underscore (on monochrome display adapter only)
									csbi.wAttributes |= COMMON_LVB_UNDERSCORE;
									break;
								case 5: // Blink on
									break;
								case 7: // Reverse video on
									csbi.wAttributes |= COMMON_LVB_REVERSE_VIDEO;
									break;
								case 8: // Concealed on
									break;
								case 22: // Bold off
									break;
								case 24: // reset Underscore (on monochrome display adapter only)
									csbi.wAttributes &= ~COMMON_LVB_UNDERSCORE;
									break;
								case 25: // Blink on
									break;
								case 27: // Reverse video off
									csbi.wAttributes &= ~COMMON_LVB_REVERSE_VIDEO;
									break;
								// Foreground colors
								case 30: case 31: case 32: case 33:
								case 34: case 35: case 36: case 37:
									csbi.wAttributes &= ~wFgColors[7];
									csbi.wAttributes |=  wFgColors[attr - 30];
									break;
								// Foreground colors
								case 90: case 91: case 92: case 93:
								case 94: case 95: case 96: case 97:
									csbi.wAttributes &= ~(wFgColors[7]|FOREGROUND_INTENSITY);
									csbi.wAttributes |=  (wFgColors[attr - 90]|FOREGROUND_INTENSITY);
									break;
								// Background colors
								case 40: case 41: case 42: case 43:
								case 44: case 45: case 46: case 47:
									csbi.wAttributes &= ~wBgColors[7];
									csbi.wAttributes |=  wBgColors[attr - 40];
									break;
								// Background colors
								case 100: case 101: case 102: case 103:
								case 104: case 105: case 106: case 107:
									csbi.wAttributes &= ~(wBgColors[7]|BACKGROUND_INTENSITY);
									csbi.wAttributes |=  (wBgColors[attr - 100]|BACKGROUND_INTENSITY);
									break;
								}
							}
							SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
							break; }
						}
						//
						pa = p;
					}
				}
				continue;
			}
			p++;
		}
		if( pa != p )
		{
			WriteFile(hStdOut, pa, size_t(p - pa), &len, NULL);
		}
	}
	// reset text attributes
	SetConsoleTextAttribute(hStdOut, csbiDefault.wAttributes);
	return 0;
}
