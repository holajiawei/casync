/* SPDX-License-Identifier: LGPL-2.1+ */

#ifndef foocadigesthfoo
#define foocadigesthfoo

#include <stdbool.h>
#include <sys/types.h>
#include <inttypes.h>

typedef struct CaDigest CaDigest;

typedef enum CaDigestType {
        CA_DIGEST_SHA256,
        CA_DIGEST_SHA512_256,
        _CA_DIGEST_TYPE_MAX,
        CA_DIGEST_DEFAULT = CA_DIGEST_SHA512_256,
        _CA_DIGEST_TYPE_INVALID = -1,
} CaDigestType;

int ca_digest_new(CaDigestType t, CaDigest **ret);
CaDigest *ca_digest_free(CaDigest *d);

static inline void ca_digest_freep(CaDigest **d) {
        if (d)
                ca_digest_free(*d);
}

int ca_digest_ensure_allocated(CaDigest **d, CaDigestType t);

void ca_digest_write(CaDigest *d, const void *p, size_t l);

static inline void ca_digest_write_u8(CaDigest *d, uint8_t u) {
        ca_digest_write(d, &u, sizeof(u));
}

static inline void ca_digest_write_u32(CaDigest *d, uint32_t u) {
        u = htole32(u);
        ca_digest_write(d, &u, sizeof(u));
}

static inline void ca_digest_write_u64(CaDigest *d, uint64_t u) {
        u = htole64(u);
        ca_digest_write(d, &u, sizeof(u));
}

const void* ca_digest_read(CaDigest *d);

void ca_digest_reset(CaDigest *d);

size_t ca_digest_get_size(CaDigest *d);
CaDigestType ca_digest_get_type(CaDigest *d);
const char *ca_digest_get_name(CaDigest *d);

size_t ca_digest_type_size(CaDigestType t);

const char *ca_digest_type_to_string(CaDigestType t);
CaDigestType ca_digest_type_from_string(const char *name);

int ca_digest_set_type(CaDigest *d, CaDigestType t);

#endif
