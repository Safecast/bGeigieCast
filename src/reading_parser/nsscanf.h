#ifndef NSSCANF_H
#define NSSCANF_H

/**
 * Parse a string with specific format
 * @param s: String to parse
 * @param format: Format of the string
 * @param ...: Any arguments to put the output in...
 * @return
 */
int nsscanf( const char *s, const char *format, ...);

#endif
