#include <janet.h>

static Janet base16_encode(int32_t argc, Janet *argv) {
  janet_arity(argc, 1, 2);

  JanetByteView b = janet_getbytes(argv, 0);
  size_t nbytes = (size_t)b.len;
  size_t ntmp = nbytes * 2;
  uint8_t *tmp = janet_smalloc(ntmp);
  char *chartab = "0123456789abcdef";
  for (size_t i = 0; i < nbytes; i++) {
    uint8_t c = b.bytes[i];
    tmp[2 * i] = chartab[(c & 0xf0) >> 4];
    tmp[2 * i + 1] = chartab[c & 0x0f];
  }
  Janet r;
  if (argc == 1) {
    r = janet_stringv(tmp, ntmp);
  } else {
    JanetBuffer *out = janet_getbuffer(argv, 1);
    janet_buffer_push_bytes(out, tmp, ntmp);
    r = janet_wrap_buffer(out);
  }
  janet_sfree(tmp);
  return r;
}

static int decode_nibble(uint8_t b) {
  if (b >= '0' && b <= '9')
    return b - '0';
  if (b >= 'a' && b <= 'f')
    return 10 + b - 'a';
  if (b >= 'A' && b <= 'F')
    return 10 + b - 'A';
  return 0;
}

static Janet base16_decode(int32_t argc, Janet *argv) {
  janet_arity(argc, 1, 2);
  JanetBuffer *out;

  JanetByteView b = janet_getbytes(argv, 0);
  size_t nbytes = (size_t)b.len;

  if (argc == 2) {
    out = janet_getbuffer(argv, 1);
  } else {
    out = janet_buffer(nbytes / 2);
  }

  for (size_t i = 0; i < nbytes; i += 2) {
    uint8_t c1 = decode_nibble(b.bytes[i]);
    uint8_t c2 = decode_nibble((i + 1 < nbytes) ? b.bytes[i + 1] : 0);
    janet_buffer_push_u8(out, (c1 << 4) | c2);
  }

  return janet_wrap_buffer(out);
}

static const JanetReg cfuns[] = {
    {"encode", base16_encode,
     "(base16/encode buf &opt buf)\n\n"
     "Encode a string or buffer to a base16 string,"
     " or optionally into a buffer."},
    {"decode", base16_decode,
     "(base16/decode s &opt buf)\n\n"
     "Decode a base16 string to a buffer,"
     " invalid characters are treated as 0."},
    {NULL, NULL, NULL}};

JANET_MODULE_ENTRY(JanetTable *env) { janet_cfuns(env, "base16", cfuns); }
