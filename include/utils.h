#ifndef UTILS_H_
#define UTILS_H_
#include "index.h"
/// @brief convert req to string(use for send)
/// @param req
/// @param str output
void Req2String(Request *req, const char *str);
/// @brief
/// @param res
/// @param str output
void Res2String(Response *res, const char *str);
/// @brief
/// @param str
/// @param req output
void String2Req(char *str, const Request *req);
/// @brief
/// @param str
/// @param res output
void String2Res(char *str, const Response *res);

void Req2String(Request *req, const char *str)
{
}
void Res2String(Response *res, const char *str) {}
void String2Req(char *str, const Request *req) {}
void String2Res(char *str, const Response *res) {}

#endif /* UTILS_H_ */