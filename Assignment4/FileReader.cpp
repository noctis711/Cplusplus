#include "FileReader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

FileReader::FileReader(const std::string& file)
{
    m_input.open(file);
    if (!m_input.is_open())
        throw std::string("file not found");
}

FileReader::~FileReader()
{
    if (m_input.is_open())
        m_input.close();
}

bool FileReader::endOfFile()
{
    return !m_input.good();
}

std::string FileReader::readLine()
{
    std::string line("");
    if (m_input.good())
    {
        getline(m_input, line);
    }
    return line;
}
