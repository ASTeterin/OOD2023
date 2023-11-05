#include "IInputStream.h"

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(std::string const& fileName)
	{
		m_file.open(fileName, std::ios::in | std::ios::binary);
	}
	~CFileInputStream()
	{
		m_file.close();
	}

	bool IsEOF() const
	{
		return m_file.eof();
	}

	uint8_t ReadByte()
	{
		char symbol;
		if (!m_file.read(&symbol, 1))
			throw std::ios_base::failure("End of the file");
		return static_cast<uint8_t>(symbol);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)
	{
		if (!m_file.read(static_cast<char*>(dstBuffer), size))
			throw std::ios_base::failure("End of the file");

		return m_file.gcount();
	}

private:
	std::fstream m_file;
};
