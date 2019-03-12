#include <string.h>
#include <stdio.h>
#include <debugger.h>
#include "http_request.h"

HttpRequest::HttpRequest() : _method(""), _uri(""), _query_params(""), _version(""), _headers(), _header_count(0) {
}

void HttpRequest::set_request_line(const char* line) {
  char full_uri[1024];
  int n = sscanf(line, "%s %s %s", _method, full_uri, _version);
  if(n != 3) {
    _method[0] = '\0';
    _uri[0] = '\0';
    _version[0] = '\0';
    _query_params[0] = '\0';
  }
  else {
    sscanf(full_uri, "%[^?]?%s", _uri, _query_params);
  }
  debug_println(line);
}

void HttpRequest::add_header_line(const char* line) {

}

void HttpRequest::set_content(const char* content) {

}

bool HttpRequest::has_query_params() {
  return strlen(_query_params) > 0;
}

bool HttpRequest::get_param_value(const char* key, char* result, size_t result_size) {
  if(has_query_params()) {
    size_t line_len = strlen(_query_params);
    size_t key_len = strlen(key);
    const char assignChar = '=';
    for(size_t i = 0; i < line_len - key_len; ++i) {
      if(strncmp(_query_params + i, key, key_len) == 0 && *(_query_params + i + key_len) == assignChar) {
        ++i;
        for(size_t j = 0; j < result_size - 1 && j + i + key_len < line_len; ++j) {
          const char current = _query_params[i + key_len + j];
          if(current == '&') {
            break;
          }
          result[j] = current;
          result[j + 1] = 0;
        }
        // Remove url encoded spaces...
        for (char* p = strchr(result, '+'); (p = strchr(p, '+')) != nullptr; *p = ' ');
        return true;
      }
    }
  }
  return false;
}

const char* HttpRequest::get_uri() const {
  return _uri;
}
