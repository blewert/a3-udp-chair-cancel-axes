#include "..\..\include\gui\AMSgui.h"

AMSA3::GUI::Visualiser::Visualiser(PCars::PCarsGame* game) : game(game)
{
	//Initialise everything
	SDL_Init(SDL_INIT_EVERYTHING);

	if (TTF_Init() == -1)
		throw new std::exception("Couldn't init TTF");

	//Create the window
	this->window = SDL_CreateWindow("AMS A3 Visualiser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	//Create the renderer
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

	//Create the packet log box
	this->packetLogBox = new PacketLogBox(this->window, this->renderer, 10);

	//Set the position
	this->packetLogBox->SetPosition(10, 50);

	//Set SDL render hints
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//Hide the console
	//ShowWindow(GetConsoleWindow(), false);

	//Load the fonts
	this->font = TTF_OpenFont(FONT_PATH, FONT_PT_SIZE);

	if (this->font == NULL)
		throw new std::exception("Couldn't load font");

	//Call update & render once 
	this->Update();
	this->Render();
}

AMSA3::GUI::Visualiser::~Visualiser(void)
{
	//Destroy window & renderer
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	TTF_CloseFont(this->font);

	//Delete pointers
	delete this->packetLogBox;
	delete this->window;
	delete this->renderer;
	delete this->font;

	//Quit SDL
	TTF_Quit();
	SDL_Quit();
}

void AMSA3::GUI::Visualiser::Render(void) const
{
	//Present, so clear first:
	SDL_SetRenderDrawColor(this->renderer, 0x0, 0x0, 0x0, 0xff);
	SDL_RenderClear(this->renderer);

	//Draw stuff -- packet list in white
	SDL_SetRenderDrawColor(this->renderer, 0xff, 0xff, 0xff, 0xff);
	this->packetLogBox->Render(this->font, 12);

	//Initiallly, this is just the default message
	std::string strCar = "Project CARS not detected!";
	std::string strGameState = "N/A";
		
	if (game != NULL)
	{
		strCar = string_format("%s on %s (%.2fm)", game->GetCarName().c_str(), game->GetTrackName().c_str(), game->GetTrackLength());
		
		strGameState = string_format("Game = %s, Race = %s, Sess = %s", game->GetGameStateString().c_str(), game->GetRaceStateString().c_str(), game->GetSessionStateString().c_str());
	}

	//Draw info box for car
	GUI::RenderText(strCar.c_str(), renderer, font, 10, 10);
	GUI::RenderText(strGameState.c_str(), renderer, font, 10, 25);

	//Then call render present
	SDL_RenderPresent(this->renderer);
}

void AMSA3::GUI::Visualiser::Update(void) const
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			exit(1);
	}
}

void AMSA3::GUI::Visualiser::OnPacketSent(const Network::Packet::UDPPacketData* packet) const
{
	this->packetLogBox->PushPacket(packet);
}







AMSA3::GUI::PacketLogBox::~PacketLogBox(void)
{
	//Delete the queue
	delete this->messageQueue;
}

AMSA3::GUI::PacketLogBox::PacketLogBox(SDL_Window* window, SDL_Renderer* renderer, int messageCount) : window(window), renderer(renderer), messageCount(messageCount)
{
	//Make the message queue
	this->messageQueue = new std::list<std::string>();
}

void AMSA3::GUI::PacketLogBox::PushPacket(const Network::Packet::UDPPacketData* packet)
{
	//Format the message
	std::string message = string_format("a = (%.1f, %.1f, %.1f), t = %d", packet->localAccel[0], packet->localAccel[1], packet->localAccel[2], packet->packetTimeMillis);

	//Emplace the message
	messageQueue->push_front(message);

	//More than message count? pop it
	if (messageQueue->size() > this->messageCount)
		messageQueue->pop_back();
}

void AMSA3::GUI::PacketLogBox::PushMessage(const std::string& message)
{
	//Emplace the message
	messageQueue->push_front(message);

	//More than message count? pop it
	if (messageQueue->size() > this->messageCount)
		messageQueue->pop_back();
}

void AMSA3::GUI::PacketLogBox::Render(TTF_Font* font, int pxGap = 20)
{
	//Render time, run through all messages and render them
	//..

	//Counter
	int i = 0;

	GUI::RenderText("Packets Sent", this->renderer, font, this->x, this->y);

	for (std::list<std::string>::const_iterator& it = messageQueue->begin(); it != messageQueue->end(); it++)
	{
		//Render text
		GUI::RenderText(it->c_str(), this->renderer, font, this->x, this->y + ((i+2) * pxGap));
		
		//Increment i
		i++;
	}
}

void AMSA3::GUI::PacketLogBox::SetPosition(const unsigned int x, const unsigned int y)
{
	this->x = x;
	this->y = y;
}

void AMSA3::GUI::RenderText(const char* text, SDL_Renderer* renderer, TTF_Font* font, int x, int y)
{
	//First, size the text
	int w = 0, h = 0;
	TTF_SizeText(font, text, &w, &h);

	//Make the color from render draw color
	SDL_Color col = { 0, 0, 0, 0 };
	SDL_GetRenderDrawColor(renderer, &col.r, &col.g, &col.b, &col.a);

	//Then render the text to a surface
	SDL_Surface* surf = TTF_RenderText_Blended(font, text, col);

	//Convert to texture & free
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

	//Build rect
	SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopy(renderer, tex, NULL, &dstRect);

	//Then clean up
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
}
