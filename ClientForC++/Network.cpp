#include<WinSock2.h>
#include"Network.h"


void Network::pars(std::string data)
{
	std::string temp;
	int k = 0;
	for (int i = 1; i < data.size() + 1; i++)
	{
		if (data[i] != ';')
		{
			temp += data[i];
		}
		else
		{
			data_[k] = atof(temp.c_str());
			temp.clear();
			k++;
		}
	}
	data_[k] = atof(temp.c_str());
	temp.clear();
}


void Network::sendData(const std::string& command)
{
	int commandSize = command.size();
	send(connections_, (char*)&commandSize, sizeof(int), NULL);
	send(connections_, command.c_str(), commandSize, NULL);
}


void Network::getDataWithServer(HWND hWnd)
{
	int dataSize;
	while (isStartGetData_.load(std::memory_order_acquire))
	{
		recv(connections_, (char*)&dataSize, sizeof(int), NULL);
		char* data = new char[dataSize + 1];
		data[dataSize] = '\0';
		recv(connections_, data, dataSize, NULL);
		if (data[0] == 'D')
		{
			pars(data);
			InvalidateRect(hWnd, NULL, 1);
			UpdateWindow(hWnd);
		}
		delete[] data;
	}
}

void Network::stop()
{
	isStartGetData_.store(false, std::memory_order_release);
	sendData("stop");
	closesocket(connections_);
}

size_t Network::connection()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(ipAddress_.c_str());
	addr.sin_port = htons(port_);
	addr.sin_family = AF_INET;

	connections_ = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connections_, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		return 0;
	}
	return 1;
}

bool Network::start(HWND hWnd)
{
	if (connection())
	{
		std::thread tr(&Network::getDataWithServer, this, hWnd);
		tr.detach();
		isStartGetData_.store(true, std::memory_order_release);
		return 1;
	}
	else
		return 0;
}

void Network::setPort(size_t port)
{
	this->port_ = port;
}
void Network::setIpAddress(std::string ipAddress)
{
	this->ipAddress_ = ipAddress;
}
std::string Network::getIpAddress()const
{
	return ipAddress_;
}
size_t Network::getPort()const
{
	return port_;
}
std::vector<int> Network::getData()
{
	return data_;
}