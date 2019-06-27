#include "led.h"
// #ifdef __APPLE_CC__
#include <arpa/inet.h>
// #endif  // __APPLE_CC__
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>

namespace {
std::array<int, LED_WIDTH * LED_HEIGHT * LED_DEPTH> m;
int sockfd = 0;
char const* url;
unsigned short port;
bool contains(int x, int y, int z) {
  return 0 <= x && x < LED_WIDTH && 0 <= y && y < LED_HEIGHT && 0 <= z &&
         z < LED_DEPTH;
}
int address(int x, int y, int z) {
  return (x * LED_HEIGHT + y) * LED_DEPTH + z;
}
}  // namespace

int InitSdk(char const* arg0, unsigned short arg1) {
  url = arg0;
  port = arg1;
  if (0 < sockfd) {
    close(sockfd);
    sockfd = 0;
  }
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    std::cerr << "socket " << strerror(errno) << std::endl;
    return 1;
  }
  sockfd = sock;
  return 0;
}

void SetLed(int x, int y, int z, int rgb) {
  if (contains(x, y, z)) m[address(x, y, z)] = rgb;
}

void Clear() { std::fill(m.begin(), m.end(), 0); }

int Show() {
  std::array<char, LED_WIDTH * LED_HEIGHT * LED_DEPTH * 2> pkt;
  for (int x = 0, i = 0; x < LED_WIDTH; ++x) {
    for (int y = 0; y < LED_HEIGHT; ++y) {
      for (int z = 0; z < LED_DEPTH; ++z, i += 2) {
        int v = m[address(x, y, z)];
        pkt[i] = static_cast<char>((v & 0xF80000) >> 16) + ((v & 0xE000) >> 13);
        pkt[i + 1] = static_cast<char>((v & 0x1C00) >> 5) + ((v & 0xF8) >> 3);
      }
    }
  }
  sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(url);
  if (sendto(sockfd, pkt.data(), pkt.size(), 0,
             reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
    std::cerr << "sendto " << strerror(errno) << std::endl;
    return 1;
  }
  return 0;
}

void Wait(int ms) {
  static auto sLastWaitTime = std::chrono::system_clock::now();
  auto now = std::chrono::system_clock::now();
  int diff = static_cast<int>(
      std::chrono::duration_cast<std::chrono::milliseconds>(now - sLastWaitTime)
          .count());
  ms = std::max(1, ms - diff);
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  sLastWaitTime = std::chrono::system_clock::now();
}
