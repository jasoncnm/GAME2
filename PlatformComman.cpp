struct ButtonState
{
	bool IsDown;
	bool Changed;
};


enum
{
	BUTTON_DOWN, 
	BUTTON_UP, 
	BUTTON_LEFT, 
	BUTTON_RIGHT,
	BUTTON_COUNT
};


struct Input
{
	ButtonState Buttons[BUTTON_COUNT];
};