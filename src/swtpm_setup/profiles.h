/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * profiles.h: TPM 2 runtime-enabled algorithm profiles
 *
 * Author: Stefan Berger, stefanb@linux.ibm.com
 *
 * Copyright (c) IBM Corporation, 2022
 */

#ifndef SWTPM_SETUP_PROFILES_H
#define SWTPM_SETUP_PROFILES_H

int get_rules_by_profile(const char *profilename, char **rules);

#endif /* SWTPM_SETUP_PROFILES_H */
