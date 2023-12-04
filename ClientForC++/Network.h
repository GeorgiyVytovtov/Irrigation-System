#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)
#include<string>
#include<Windows.h>
#include<WinSock2.h>
#include<tchar.h>
#include<vector>
#include<thread>
#include<atomic>

class Network
{
private:
	void pars(std::string data);
	void getDataWithServer(HWND hWnd);
	size_t connection();
	std::vector<int> data_{0,0,0,0,0,0};
	SOCKET connections_;
	std::string ipAddress_;
	size_t port_;
	std::atomic<bool> isStartGetData_{ true };
public:
	void sendData(const std::string& command);
	void setPort(size_t port);
	void setIpAddress(std::string ipAdress);
	std::string getIpAddress()const;
	size_t getPort()const;
	std::vector<int> getData();
	void stop();
	bool start(HWND hWnd);
};