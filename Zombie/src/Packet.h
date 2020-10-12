#pragma once

#define MAX_PACKET_SIZE 65542
#include <iomanip>

enum class FLAGS : unsigned char
{
	Authentification, Changestate,

};

struct Header
{
	unsigned int destination; //4 byte
	unsigned char flags;				//1 byte
	unsigned short size;	//2 bytes + 65.535 bytes

	Header(unsigned int d, unsigned char f, unsigned short s)
		: destination(d), flags(f), size(s) {}
};

struct Body
{
	const char* data;

	Body(const char* d)
		: data(d) {}
};

struct Packet
{
	Packet(const Header& h = Header(0,0,0), const Body& b = Body(0))
		: header(h), body(b) {}

	static Packet Pack(const char* msg)
	{
		uint32_t destination = (msg[3] << 24) | (msg[2] << 16) | (msg[1] << 8) | (msg[0] << 0);
		unsigned char flags = msg[5];				//1 byte
		unsigned short size = (msg[7] << 8) | (msg[6] << 0);	//2 bytes + 65.535 bytes
		Packet tmp({ destination, flags, size }, { msg + 9 });
		return std::move(tmp);
	}

	friend std::ostream& operator<<(std::ostream& os, const Packet& packet)
	{
		os << "Destination: " << packet.header.destination << std::endl;
		os << "Flags: " << packet.header.flags << std::endl;
		os << "Size: " << packet.header.size << std::endl;
		os << "Data: " << std::setw(packet.header.size) << packet.body.data << std::endl;
		return os;
	}
	Header header;
	Body body;
};