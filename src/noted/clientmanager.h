#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "../net/socket.h" 
#include "../helpers/config.h"

void handleClient(const Config& config, Socket* client);

#endif
