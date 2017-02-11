#include "discord.h"

#include <unistd.h>
#include <malloc.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define FAIL    -1

/*---------------------------------------------------------------------*/
/*--- OpenConnection - create socket and connect to server.         ---*/
/*---------------------------------------------------------------------*/
int OpenConnection(const char *hostname, int port) {
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(sd, &addr, sizeof(addr)) != 0 )
    {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

/*---------------------------------------------------------------------*/
/*--- InitCTX - initialize the SSL engine.                          ---*/
/*---------------------------------------------------------------------*/
SSL_CTX* InitCTX(void) {
    SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();       /* Load cryptos, et.al. */
    SSL_load_error_strings();           /* Bring in and register error messages */
    method = SSLv23_client_method();     /* Create new client-method instance */
    ctx = SSL_CTX_new(method);          /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

/*---------------------------------------------------------------------*/
/*--- ShowCerts - print out the certificates.                       ---*/
/*---------------------------------------------------------------------*/
void ShowCerts(SSL* ssl) {
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);   /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);                         /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);                         /* free the malloc'ed string */
        X509_free(cert);                    /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}

void wsclient_new(Discord *discord, const char *url) {
    printf("=> Connecting to WebSocket URL: %s\n", url);

	HTTPResponse r;
    SSL_CTX *ctx;
    SSL *ssl;
    int server, bytes;
    char buf[1024];
    char* base64EncodeOutput, *wskey = "Hello World", *seckey, *hostname;
    hostname = "gateway.discord.gg";
    seckey = "Sec-WebSocket-Key: ";
    Base64Encode(wskey, strlen(wskey), &base64EncodeOutput);
    strcat(seckey, base64EncodeOutput);

    ctx = InitCTX();
    server = OpenConnection(hostname, 443);
    ssl = SSL_new(ctx);                     /* create new SSL connection state */
    SSL_set_fd(ssl, server);                /* attach the socket descriptor */
    if ( SSL_connect(ssl) == FAIL )         /* perform the connection */
        ERR_print_errors_fp(stderr);
    else {
        printf("Connected!\n");
        //printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    }
}
