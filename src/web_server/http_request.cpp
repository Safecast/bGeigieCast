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
  } else {
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

bool HttpRequest::has_param(const char* key) {
  if(has_query_params()) {
    size_t line_len = strlen(_query_params);
    size_t key_len = strlen(key);
    for(size_t i = 0; i < line_len - key_len; ++i) {
      if(strncmp(_query_params + i, key, key_len) == 0) {
        return true;
      }
    }
  }
  return false;
}

bool HttpRequest::get_param_value(const char* key, char* result, size_t result_size) {
  if(has_query_params()) {
    result[0] = '\0';
    size_t key_len = strlen(key);

    const char assignChar = '=';

    auto next_begin = [this](char** begin) {
      char* next = strchr(*begin, '&');
      *begin = next && *next == '&' && next - _query_params < strlen(_query_params) - 1 ? next + 1 : nullptr;
    };

    for(char* begin = _query_params; begin != nullptr; next_begin(&begin)) {
      if(strncmp(begin, key, key_len) == 0 && *(begin + key_len) == assignChar) {
        char* begin_value = begin + key_len + 1; // + 1 for the '=' character
        char* end_value = strchr(begin_value, '&');
        uint32_t val_len = end_value ? end_value - begin_value : strlen(begin_value);
        if(val_len > result_size - 1) {
          debug_println("Request param value exceeding max size");
          return false;
        }
        strncpy(result, begin_value, val_len);
        result[val_len] = '\0';

        // Remove url encoded spaces...
        for(char* p = result; (p = strchr(p, '+')) != nullptr; *p = ' ') {}
        return true;
      }
    }
  }
  return false;
}

bool HttpRequest::is_uri(const char* uri) const {
  return strcmp(_uri, uri) == 0;
}

const char* HttpRequest::get_uri() const {
  return _uri;
}
