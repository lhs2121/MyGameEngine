#include <iostream>

int Ser(int Size)
{
	int BlockSize;
	int i = 4;
	while (true)
	{
		int BlockSize = 2 ^ i;
		i++;


		if (BlockSize > Size)
		{
			return BlockSize;
		}

	}
}
int main()
{
	Ser(128);

}