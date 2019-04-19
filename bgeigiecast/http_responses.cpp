#include "http_responses.h"

// Responses
void respondSuccess(Stream& client) {
  // Return 204 OK to client
  client.println("HTTP/1.1 204 NO CONTENT");
  client.println("Connection: close");
  client.println();
}

void respondSuccess(Stream& client, const char* content, const char* content_type) {
  // Return 200 OK to client
  client.println("HTTP/1.1 200 OK");
  client.println("Connection: close");
  client.print("Content-Type: ");
  client.println(content_type);
  client.print("Content-Length: ");
  client.println(strlen(content) + 2);
  client.println();
  client.println(content);
}

void respondRedirect(Stream& client, const char* location) {
  // Return 302 REDIRECT to client
  client.println("HTTP/1.1 302 FOUND");
  client.print("Location: ");
  client.println(location);
  client.println();
}

void respondBadRequest(Stream& client) {
  // Return 400 BAD REQUEST to client
  client.println("HTTP/1.1 400 BAD REQUEST");
  client.println("Content-Length: 17");
  client.println();
  client.println("400 Bad Request");
}

void respondNotFound(Stream& client) {
  // Return 400 BAD REQUEST to client
  client.println("HTTP/1.1 404 NOT FOUND");
  client.println("Content-Length: 15");
  client.println();
  client.println("404 Not Found");
}