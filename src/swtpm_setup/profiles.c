/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * profiles.c: TPM 2 runtime-enabled algorithm profiles
 *
 * Author: Stefan Berger, stefanb@linux.ibm.com
 *
 * Copyright (c) IBM Corporation, 2022
 */

#include "config.h"

#include <stdio.h>

#include <glib.h>

#include "profiles.h"
#include "swtpm_utils.h"

struct profile {
    const char *name;
    const char *rules;
};

static const struct profile profiles[] = {
    {
        /* all algorithms of the TPM 2 are available */
        .name = "unrestricted",
        .rules = NULL,
    }, {
        .name = "default",
        /* removed: sha1
         * keysize: TDES=192
         */
        .rules = "rsa:rsa-min-size=2048:tdes:tdes-min-size=192:hmac:"
                 "aes:aes-min-size=128:mgf1:keyedhash:xor:sha256:sha384:sha512:"
                 "null:rsassa:rsaes:rsapss:oaep:ecdsa:ecdh:ecdaa:sm2:ecschnorr:"
                 "ecmqv:kdf1-sp800-56a:kdf2:kdf1-sp800-108:ecc:symcipher:"
                 "camellia:camellia-min-size=128:cmac:ctr:ofb:cbc:cfb:ecb"
    }, {
        .name = "fips",
        /* removed: sha1, rsapss (signing scheme, CentOS 9 FIPS mode),
         *          camellia (CentOS 9), tdes (CentOS 9)
         */
        .rules = "rsa:rsa-min-size=2048:hmac:"
                 "aes:aes-min-size=128:mgf1:keyedhash:xor:sha256:sha384:sha512:"
                 "null:rsassa:rsaes:oaep:ecdsa:ecdh:ecdaa:sm2:ecschnorr:"
                 "ecmqv:kdf1-sp800-56a:kdf2:kdf1-sp800-108:ecc:symcipher:"
                 "cmac:ctr:ofb:cbc:cfb:ecb",
    }
};

int get_rules_by_profile(const char *profilename, char **rules)
{
    size_t i;

    for (i = 0; i < ARRAY_LEN(profiles); i++) {
        if (!strcmp(profilename, profiles[i].name)) {
            *rules = g_strdup(profiles[i].rules);
            return 0;
        }
    }
    fprintf(stderr, "Could not find profile with name '%s'.\n", profilename);
    return -1;
}

