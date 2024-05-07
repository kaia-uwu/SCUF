//Simple Console Ui Framework

#include <iostream>
#include <string>
#include <windows.h>

void dump_events(INPUT_RECORD record, std::string info) {
	std::cout <<
		"-=[EVENT DUMP]=-" <<
		"\ninfo:" << info <<
		"\nevent type:" << record.EventType <<
		"\n" << (char)(-(255 - 194)) << "key:" <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 194)) << "ascii:" << (DWORD)record.Event.KeyEvent.uChar.AsciiChar <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 194)) << "down:" << record.Event.KeyEvent.bKeyDown <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 191)) << "control:" << record.Event.KeyEvent.dwControlKeyState <<
		"\n" << (char)(-(255 - 194)) << "focus:" <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 191)) << "set focus:" << record.Event.FocusEvent.bSetFocus <<
		"\n" << (char)(-(255 - 194)) << "menu:" <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 191)) << "command:" << record.Event.MenuEvent.dwCommandId <<
		"\n" << (char)(-(255 - 194)) << "mouse:" <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 194)) << "button:" << record.Event.MouseEvent.dwButtonState <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 194)) << "control:" << record.Event.MouseEvent.dwControlKeyState <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 194)) << "flags:" << record.Event.MouseEvent.dwEventFlags <<
		"\n" << (char)(-(255 - 178)) << (char)(-(255 - 191)) << "pos:" <<
		"\n" << (char)(-(255 - 178)) << " " << (char)(-(255 - 194)) << "x:" << record.Event.MouseEvent.dwMousePosition.X <<
		"\n" << (char)(-(255 - 178)) << " " << (char)(-(255 - 191)) << "y:" << record.Event.MouseEvent.dwMousePosition.Y <<
		"\n" << (char)(-(255 - 191)) << "buffer size:" <<
		"\n" << " " << (char)(-(255 - 191)) << "size:" <<
		"\n" << "  " << (char)(-(255 - 194)) << "x:" << record.Event.WindowBufferSizeEvent.dwSize.X <<
		"\n" << "  " << (char)(-(255 - 191)) << "y:" << record.Event.WindowBufferSizeEvent.dwSize.Y <<
		"\n-=-" << std::endl;
}

void clear_screen(HANDLE console_out_handle) {
	WCHAR nothing = '\0';
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(console_out_handle, (PCONSOLE_SCREEN_BUFFER_INFO)&buffer_info);
	DWORD length = buffer_info.dwSize.X * buffer_info.dwSize.Y;
	COORD top_left;
	top_left.X = 0;
	top_left.Y = 0;
	DWORD num_char_written;
	FillConsoleOutputCharacter(console_out_handle, nothing, length, top_left, &num_char_written);
	SetConsoleCursorPosition(console_out_handle, top_left);
}

class button {
public:
	std::string text;
	COORD position;
	bool hover;
	bool toggled;
};

char get_char(int code) {
	return (char)(-(256 - code));
}

void render(HANDLE console_out_handle, button* button_array, size_t button_count) {
	for (int i = 0; i < button_count; i++) {
		SetConsoleCursorPosition(console_out_handle, button_array[i].position);
		if (button_array[i].toggled) {
			SetConsoleTextAttribute(console_out_handle, 10);
			std::cout << get_char(201);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(205);
			}
			std::cout << get_char(187);

			COORD cur_pos = button_array[i].position;
			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(186);
			SetConsoleTextAttribute(console_out_handle, 15);
			std::cout << button_array[i].text;
			SetConsoleTextAttribute(console_out_handle, 10);
			std::cout << get_char(186);

			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(200);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(205);
			}
			std::cout << get_char(188);
		}
		else if (button_array[i].hover) {
			SetConsoleTextAttribute(console_out_handle, 10);
			std::cout << get_char(218);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(196);
			}
			std::cout << get_char(191);

			COORD cur_pos = button_array[i].position;
			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(179);
			SetConsoleTextAttribute(console_out_handle, 15);
			std::cout << button_array[i].text;
			SetConsoleTextAttribute(console_out_handle, 10);
			std::cout << get_char(179);

			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(192);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(196);
			}
			std::cout << get_char(217);
		}
		else {
			SetConsoleTextAttribute(console_out_handle, 8);
			std::cout << get_char(218);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(196);
			}
			std::cout << get_char(191);

			COORD cur_pos = button_array[i].position;
			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(179);
			std::cout << button_array[i].text;
			std::cout << get_char(179);

			cur_pos.Y += 1;
			SetConsoleCursorPosition(console_out_handle, cur_pos);
			std::cout << get_char(192);
			for (int ii = 0; ii < button_array[i].text.length(); ii++) {
				std::cout << get_char(196);
			}
			std::cout << get_char(217);
		}
	}
}

void handle(HANDLE console_out_handle, button* button_array, size_t button_count, COORD position, bool clicked) {
	for (int i = 0; i < button_count; i++) {
		if (position.Y >= button_array[i].position.Y and position.Y <= button_array[i].position.Y + 2 and position.X >= button_array[i].position.X and position.X <= button_array[i].position.X + 2 + button_array[i].text.length()) {
			button_array[i].hover = true;
			if (clicked) {
				button_array[i].toggled = !button_array[i].toggled;
			}
		}
		else {
			button_array[i].hover = false;
		}
	}
}

int main()
{
	COORD top_left;
	top_left.X = 0;
	top_left.Y = 0;

	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);

	HANDLE console_in_handle = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE console_out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleMode(console_in_handle, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);
	SetConsoleCP((UINT)437);

	SetConsoleMode(console_out_handle, DISABLE_NEWLINE_AUTO_RETURN | ENABLE_PROCESSED_OUTPUT);

	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(console_out_handle, &buffer_info);

	COORD console_size;
	console_size.X = buffer_info.dwMaximumWindowSize.X;
	console_size.Y = buffer_info.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(console_out_handle, console_size);

	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.dwSize = (DWORD)100;
	cursor_info.bVisible = (BOOL)false;
	SetConsoleCursorInfo(console_out_handle, &cursor_info);

	COORD temp;

	button buttons[4];
	button first_button;
	first_button.hover = false;
	first_button.toggled = false;
	temp.X = 0;
	temp.Y = 0;
	first_button.position = temp;
	first_button.text = "button 1";
	buttons[0] = button(first_button);

	button second_button;
	second_button.hover = false;
	second_button.toggled = false;
	temp.X = 15;
	temp.Y = 0;
	second_button.position = temp;
	second_button.text = "button 2";
	buttons[1] = button(second_button);

	button third_button;
	third_button.hover = false;
	third_button.toggled = false;
	temp.X = 30;
	temp.Y = 0;
	third_button.position = temp;
	third_button.text = "button 3";
	buttons[2] = button(third_button);

	button fourth_button;
	fourth_button.hover = false;
	fourth_button.toggled = false;
	temp.X = 45;
	temp.Y = 0;
	fourth_button.position = temp;
	fourth_button.text = "button 4";
	buttons[3] = button(fourth_button);

	DWORD num_events = 0;
	WORD color = 0;

	do {
		render(console_out_handle, &buttons[0], 4);

		GetNumberOfConsoleInputEvents(console_in_handle, &num_events);
		if (num_events > 0) {
			//SetConsoleTextAttribute(console_out_handle, 8);
			//if (!skip_event_details) std::cout << "got event count:" << num_events << "\n";
			INPUT_RECORD record[128];
			DWORD num_events_read;
			ReadConsoleInput(console_in_handle, (PINPUT_RECORD)&record, (DWORD)128, &num_events_read);
			//if (!skip_event_details) std::cout << "read events count:" << num_events_read << "\n";
			for (int i = 0; i < num_events_read; i++) {
				if (true) {
					SetConsoleTextAttribute(console_out_handle, 8);
					//dump_events(record[i], std::to_string(i));
				}
				if (record[i].EventType == KEY_EVENT) {
					if (record[i].Event.KeyEvent.uChar.AsciiChar == (CHAR)27 and record[i].Event.KeyEvent.bKeyDown == (BOOL)0) {
						clear_screen(console_out_handle);
						SetConsoleTextAttribute(console_out_handle, 4);
						std::cout << "exiting in 5000ms";
						std::cout << '.';
						Sleep(1000);
						std::cout << '.';
						Sleep(1000);
						std::cout << '.';
						Sleep(1000);
						std::cout << '.';
						Sleep(1000);
						std::cout << '.';
						Sleep(1000);
						return EXIT_SUCCESS;
					}
				}
				else if (record[i].EventType == MOUSE_EVENT) {
					POINT mouse_pos;
					GetCursorPos(&mouse_pos);
					//std::cout << "px mouse: x:" << mouse_pos.x << " y:" << mouse_pos.y;
					bool clicked = false;
					if (record[i].Event.MouseEvent.dwButtonState != 0) {
						if (record[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
							clicked = true;
						}
						else if (record[i].Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED) {

						}
						else if (record[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {

						}
					}
					handle(console_out_handle, &buttons[0], 4, record[i].Event.MouseEvent.dwMousePosition, clicked);
				}
				else if (record[i].EventType == WINDOW_BUFFER_SIZE_EVENT) {
					CONSOLE_SCREEN_BUFFER_INFO buffer_info;
					GetConsoleScreenBufferInfo(console_out_handle, &buffer_info);
					SetConsoleScreenBufferSize(console_out_handle, buffer_info.dwMaximumWindowSize);
					SetConsoleCursorInfo(console_out_handle, &cursor_info);
				}
				else {
					//dump_events(record[i], std::to_string(i));
				}
				num_events_read--;
			}
		}
	} while (true);
}