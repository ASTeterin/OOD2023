﻿#include <cstdint>
#include <iostream>
#include <string>
#include "CFileInputStream.cpp"

using namespace std;

class IOutputDataStream
{
public:
	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	virtual void WriteByte(uint8_t data) = 0;

	// Записывает в поток блок данных размером size байт,
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	// Закрывает поток. Операции над ним после этого должны выбрасывать исключение logic_error
	virtual void Close() = 0;

	virtual ~IOutputDataStream() = default;
};

int main()
{
	auto inputStream = make_unique<CFileInputStream>("hello.txt");
	cout << inputStream->ReadByte();
	return 0;
}