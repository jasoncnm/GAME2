#define IsDown(a) Input->Buttons[a].IsDown
#define Pressed(a) (Input->Buttons[a].IsDown && Input->Buttons[a].Changed)
#define Released(a) (!Input->Buttons[a].IsDown && Input->Buttons[a].Changed)

float PlayerPositionX = 0.f;
float PlayerPositionY = 0.f;
Internal void 
SimulateGame(Input* Input, float DeltaTime)
{
	ClearScreen(0xff5500);
	float speed = 50.f;
	if (IsDown(BUTTON_RIGHT))
	{
		PlayerPositionX += speed * DeltaTime;
	}
	if (IsDown(BUTTON_LEFT))
	{
		PlayerPositionX -= speed * DeltaTime;
	}
	if (IsDown(BUTTON_UP))
	{
		PlayerPositionY -= speed * DeltaTime;
	}
	if (IsDown(BUTTON_DOWN))
	{
		PlayerPositionY += speed * DeltaTime;
	}

	DrawRect(PlayerPositionX, PlayerPositionY, 5, 5, 0x00ff22);
	DrawRect(80, 15, 2, 3, 0x00ffff);
}

