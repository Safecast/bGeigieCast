#ifndef BGEIGIE_POINTCAST_HTTP_REQUEST_H
#define BGEIGIE_POINTCAST_HTTP_REQUEST_H

#include <stdint.h>
#include <stddef.h>


#define REQUEST_LINE_METHOD_MAX 10
#define REQUEST_LINE_URI_MAX 1024
#define REQUEST_LINE_VERSION_MAX 10
#define HEADER_LINE_MAX 100
#define CONTENT_MAX 10
#define MAX_HEADERS 10


class HttpRequest {
 public:
  HttpRequest();
  virtual ~HttpRequest() = default;


  void set_request_line(const char* line);
  void add_header_line(const char* line);
  void set_content(const char* content);

  bool has_query_params();

  bool get_param_value(const char* key, char* result, size_t result_size);

 private:
  char _method[REQUEST_LINE_METHOD_MAX];
  char _uri[REQUEST_LINE_URI_MAX];
  char _version[REQUEST_LINE_VERSION_MAX];
  char _headers[HEADER_LINE_MAX][MAX_HEADERS];
  uint8_t _header_count;
};

#endif //BGEIGIE_POINTCAST_HTTP_REQUEST_H
