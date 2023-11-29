
#pragma once
#include "common.h"
#include "sha256.h"

// container for hasher
typedef uint8_t hashdata_t[SHA256_HASH_SIZE];

// container for file paths
typedef struct FilePath {
    char path[PATH_LEN];
} FilePath_t;

// container for assembling request message headers
typedef struct RequestHeader {
    char ip[IP_LEN];
    uint32_t port;
    uint32_t command;
    uint32_t length;
} RequestHeader_t;

// container for assembling reply message headers
typedef struct ReplyHeader {
    uint32_t length;
    uint32_t status;
    uint32_t this_block;
    uint32_t block_count;
    hashdata_t block_hash;
    hashdata_t total_hash;
} ReplyHeader_t;

// container for storing ip and port
typedef struct PeerAddress {
    char ip[IP_LEN];
    char port[PORT_LEN];
} PeerAddress_t;

// container for sending ip and port over a network
typedef struct NetworkAddress {
    char ip[IP_LEN];
    uint32_t port;
} NetworkAddress_t;

ReplyHeader_t create_header(int status, int this_block, int block_count, int block_len, char* block_data, hashdata_t total_hash);

void handle_register(int connfd, char* client_ip, int client_port_int);

void handle_inform(char* request, int request_len);

void handle_retrieve(int connfd, char* request, int request_len);

void handle_server_request(int connfd);

void* server_thread();