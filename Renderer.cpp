

Internal void ClearScreen(uint32 Color)
{
	uint32* Pixel = (uint32*)Buffer.Memory;
	for (int Height = 0; Height < Buffer.Height; Height++)
	{
		for (int Width = 0; Width < Buffer.Width; Width++)
		{
			*Pixel++ = Color;
		}
	}
}



Internal void DrawRectInPixels(int x0, int y0, int x1, int y1, uint32 Color)
{
	x0 = Clamp(0, Buffer.Width, x0);
	x1 = Clamp(0, Buffer.Width, x1);
	y0 = Clamp(0, Buffer.Height, y0);
	y1 = Clamp(0, Buffer.Height, y1);

	for (int Height = y0; Height < y1; Height++)
	{
		uint32* Pixel = (uint32*)Buffer.Memory + x0 + Height * Buffer.Width;
		for (int Width = x0; Width < x1; Width++)
		{
			*Pixel++ = Color;
		}
	}
}

global float RenderScale = 0.01f;
#if 0
global float AspectRatio = 16.0f / 9.0f;
#endif 
Internal void DrawRect(float x, float y, float HalfSizeX, float HalfSizeY, uint32 Color)
{
	float ratio = (float)Buffer.Width / (float)Buffer.Height;
#if 0 
	if (ratio > AspectRatio)
	{
		x *= Buffer.Width * RenderScale;
		y *= Buffer.Width * RenderScale;
		HalfSizeX *= Buffer.Width* RenderScale;
		HalfSizeY *= Buffer.Width * RenderScale;
	}
	else
	{
#endif
		x *= Buffer.Height * RenderScale;
		y *= Buffer.Height * RenderScale;
		HalfSizeX *= Buffer.Height * RenderScale;
		HalfSizeY *= Buffer.Height * RenderScale;
#if 0
	}
#endif

	x += Buffer.Width / 2.f;
	y += Buffer.Height / 2.f;

	int x0 = x - HalfSizeX;
	int x1 = x + HalfSizeX;
	int y0 = y - HalfSizeY;
	int y1 = y + HalfSizeY;

	DrawRectInPixels(x0, y0, x1, y1, Color);
}