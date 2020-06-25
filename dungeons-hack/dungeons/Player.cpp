#include <vector>
#include "../utils/proc.cpp"

const std::vector<unsigned int> HEALTH_OFFSETS = { 0x0, 0x20, 0xE38, 0x310, 0x308, 0x230, 0xF0 };
const std::vector<unsigned int> X_OFFSETS = { 0x0, 0x20, 0x360, 0xEA8, 0x148, 0x398, 0x384 };
const std::vector<unsigned int> Y_OFFSETS = { 0x0, 0x20, 0x3B0, 0xC48, 0x118, 0x398, 0x388 };
const std::vector<unsigned int> Z_OFFSETS = { 0x0, 0xE8, 0x360, 0xE88, 0x20, 0x398, 0x398 };

class Player {
public:
	Player(HANDLE hProcess, uintptr_t offsetBaseAddress)
	{
		this->hProcess = hProcess;
		healthAddress = FindDMAAddy(hProcess, offsetBaseAddress, HEALTH_OFFSETS);
		xAddress = FindDMAAddy(hProcess, offsetBaseAddress, X_OFFSETS);
		yAddress = FindDMAAddy(hProcess, offsetBaseAddress, Y_OFFSETS);
		zAddress = FindDMAAddy(hProcess, offsetBaseAddress, Z_OFFSETS);
	}
	Player() = default;
	int GetHealth()
	{
		int value = 0;
		ReadProcessMemory(hProcess, (BYTE*)healthAddress, &value, sizeof(value), nullptr);
		return value;
	}
	float GetXPosition()
	{
		float value = 0;
		ReadProcessMemory(hProcess, (BYTE*)xAddress, &value, sizeof(value), nullptr);
		return value;
	}
	float GetYPosition()
	{
		float value = 0;
		ReadProcessMemory(hProcess, (BYTE*)yAddress, &value, sizeof(value), nullptr);
		return value;
	}
	float GetZPosition()
	{
		float value = 0;
		ReadProcessMemory(hProcess, (BYTE*)zAddress, &value, sizeof(value), nullptr);
		return value;
	}
private:
	HANDLE hProcess;
	uintptr_t healthAddress;
	uintptr_t xAddress;
	uintptr_t yAddress;
	uintptr_t zAddress;
};