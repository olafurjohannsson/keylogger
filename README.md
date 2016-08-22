# keylogger
win32 keylogger

Simple C++ program that uses the WH_KEYBOARD_LL global hook, this hook is executed in ´´this´´ process(not in the process where the keyboard event happened), this is done via a message loop sending the thread (this process) the messages

