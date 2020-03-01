#pragma once

#include <windows.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include <list>
#include <string>
#include <memory>
#include <string>
#include <stdexcept>


#include "../ams/AMSPacket.h"
#include "../pcars/PCarsGame.h"

namespace AMSA3
{
	namespace GUI
	{
		//[https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf#comment61134428_2342176]
		template<typename ... Args> std::string string_format(const std::string& format, Args ... args)
		{
			size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'

			if (size <= 0)
				throw std::runtime_error("Error during formatting.");

			std::unique_ptr<char[]> buf(new char[size]);

			snprintf(buf.get(), size, format.c_str(), args ...);

			return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		}

		void RenderText(const char* text, SDL_Renderer* renderer, TTF_Font* font, int x, int y);

		class PacketHistoryTracer
		{
		private:
			SDL_Renderer* renderer;
			std::list<Network::Packet::UDPPacketData>* packetQueue;

			unsigned int x = 0;
			unsigned int y = 0;
			unsigned int size = 50;

			const unsigned int PACKET_HISTORY_LIMIT = 15;

		public:
			void PushPacket(Network::Packet::UDPPacketData packet);
			~PacketHistoryTracer(void);
			PacketHistoryTracer(unsigned int x, unsigned int y, unsigned int size, SDL_Renderer* renderer);
			void Render(void) const;
		};

		class PacketLogBox
		{
		private:
			SDL_Window* window;
			SDL_Renderer* renderer;
			unsigned int messageCount;
			std::list<std::string>* messageQueue;

			unsigned int x = 0;
			unsigned int y = 0;


		public:
			~PacketLogBox(void);
			PacketLogBox(SDL_Window* window, SDL_Renderer* renderer, int messageCount);
			void PushPacket(const Network::Packet::UDPPacketData* packet);
			void PushMessage(const std::string& message);
			void SetPosition(const unsigned int x, const unsigned int y);
			void Render(TTF_Font* font, int pxGap);
		};

		class Visualiser
		{
		private:
			SDL_Window* window;
			SDL_Renderer* renderer;
			PCars::PCarsGame* game;

			//Constants
			const unsigned int WINDOW_WIDTH  = 1000;
			const unsigned int WINDOW_HEIGHT = 1000;
			const char* FONT_PATH = "assets/consola.ttf";
			const unsigned int FONT_PT_SIZE = 14;

			PacketLogBox* packetLogBox;
			PacketHistoryTracer* packetHistoryTracer;

			//The font
			TTF_Font* font;

		public:
			Visualiser(PCars::PCarsGame* game);
			~Visualiser(void);

			void Render(void) const;
			void Update(void) const;
			void OnPacketSent(const Network::Packet::UDPPacketData* packet) const;
		};
	}
}