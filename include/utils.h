#ifndef UTILS_H_
#define UTILS_H_
#include "index.h"
/// @brief convert req to string(use for send)
/// @param req
/// @param str output
void Req2String(Req *req, const char *str);
/// @brief
/// @param res
/// @param str output
void Res2String(Res *res, const char *str);
/// @brief
/// @param str
/// @param req output
void String2Req(char *str, const Req *req);
/// @brief
/// @param str
/// @param res output
void String2Res(char *str, const Res *res);

void Req2String(Req *req, const char *str)
{
}
void Res2String(Res *res, const char *str) {}
void String2Req(char *str, const Req *req) {}
void String2Res(char *str, const Res *res) {}

#endif /* UTILS_H_ */