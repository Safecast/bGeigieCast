#include <string.h>
#include <stdio.h>
#include "http_request.h"

HttpRequest::HttpRequest() : _method(""), _uri(""), _version(""), _headers(), _header_count(0) {
}

void HttpRequest::set_request_line(const char* line) {
  int n = sscanf(line, "%s %s %s", _method, _uri, _version);
  if(n != 3) { // Need to be 3 parts
    _method[0] = '\0';
    _uri[0] = '\0';
    _version[0] = '\0';
  }
}

void HttpRequest::add_header_line(const char* line) {

}

void HttpRequest::set_content(const char* content) {

}

bool HttpRequest::has_query_params() {
  return strchr(_uri, '?') != nullptr;
}

bool HttpRequest::get_param_value(const char* key, char* result, size_t result_size) {
  if(has_query_params()) {
    size_t line_len = strlen(_uri);
    size_t key_len = strlen(key);
    const char assignChar = '=';
    for(size_t i = 0; i < line_len - key_len; ++i) {
      if(strncmp(_uri + i, key, key_len) == 0 && *(_uri + i + key_len) == assignChar) {
        ++i;
        for(size_t j = 0; j < result_size - 1 && j + i + key_len < line_len; ++j) {
          const char current = _uri[i + key_len + j];
          if(current == '&') {
            break;
          }
          result[j] = current;
          result[j + 1] = 0;
        }
        return true;
      }
    }
  }
  return false;
}
