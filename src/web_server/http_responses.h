#ifndef BGEIGIE_POINTCAST_HTTP_RESPONSES_H
#define BGEIGIE_POINTCAST_HTTP_RESPONSES_H

#include <Stream.h>

// HTTP responses

void respondSuccess(Stream& client);
void respondSuccess(Stream& client, const char* content, const char* content_type = "text/html");
void respondRedirect(Stream& client, const char* location);
void respondBadRequest(Stream& client);
void respondNotFound(Stream& client);


#endif //BGEIGIE_POINTCAST_HTTP_RESPONSES_H
