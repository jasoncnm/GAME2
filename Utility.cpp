#define global static;
#define Internal static;
typedef unsigned int uint32;

inline int Clamp(int min, int max, int Value)
{
	if (Value > max)
	{
		return max;
	}
	if (Value < min)
	{
		return min;
	}
	return Value;
}