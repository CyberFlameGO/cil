/*
 * Copyright 2011 Tresys Technology, LLC. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY TRESYS TECHNOLOGY, LLC ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL TRESYS TECHNOLOGY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of Tresys Technology, LLC.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <sepol/policydb/policydb.h>
#include <sepol/policydb/polcaps.h>

#include "cil.h"
#include "cil_mem.h"
#include "cil_tree.h"

struct cil_args_binary {
	const struct cil_db *db;
	policydb_t *pdb;
	int pass;
};

int cil_common_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	uint32_t value = 0;
	char *key = NULL;
	struct cil_common *cil_common = node->data;
	struct cil_tree_node *cil_perm = node->cl_head;
	common_datum_t *sepol_common = cil_malloc(sizeof(*sepol_common));
	memset(sepol_common, 0, sizeof(common_datum_t));

	key = cil_strdup(cil_common->datum.name);
	rc = symtab_insert(pdb, SYM_COMMONS, key, sepol_common, SCOPE_DECL, 0, &value);
	if (rc != SEPOL_OK) {
		goto common_to_binary_out;
	}
	sepol_common->s.value = value;

	rc = symtab_init(&sepol_common->permissions, PERM_SYMTAB_SIZE);
	if (rc != SEPOL_OK) {
		goto common_to_binary_out;
	}

	while (cil_perm != NULL) {
		struct cil_perm *curr = cil_perm->data;
		perm_datum_t *sepol_perm = cil_malloc(sizeof(*sepol_perm));
		memset(sepol_perm, 0, sizeof(perm_datum_t));

		key = cil_strdup(curr->datum.name);
		rc = hashtab_insert(sepol_common->permissions.table, key, sepol_perm);
		if (rc != SEPOL_OK) {
			goto common_to_binary_out;
		}
		sepol_perm->s.value = sepol_common->permissions.nprim + 1;
		sepol_common->permissions.nprim++;
		cil_perm = cil_perm->next;
	}

	return SEPOL_OK;

common_to_binary_out:
	return rc;
}

int cil_class_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	uint32_t value = 0;
	char *key = NULL;
	struct cil_class *cil_class = node->data;
	struct cil_tree_node *cil_perm = node->cl_head;
	class_datum_t *sepol_class = cil_malloc(sizeof(*sepol_class));
	memset(sepol_class, 0, sizeof(class_datum_t));

	key = cil_strdup(cil_class->datum.name);
	rc = symtab_insert(pdb, SYM_CLASSES, key, sepol_class, SCOPE_DECL, 0, &value);
	if (rc != SEPOL_OK) {
		goto class_to_policydb_out;
	}
	sepol_class->s.value = value;

	rc = symtab_init(&sepol_class->permissions, PERM_SYMTAB_SIZE);
	if (rc != SEPOL_OK) {
		goto class_to_policydb_out;
	}

	while (cil_perm != NULL) {
		struct cil_perm *curr = cil_perm->data;
		perm_datum_t *sepol_perm = cil_malloc(sizeof(*sepol_perm));
		memset(sepol_perm, 0, sizeof(perm_datum_t));

		key = cil_strdup(curr->datum.name);
		rc = hashtab_insert(sepol_class->permissions.table, key, sepol_perm);
		if (rc != SEPOL_OK) {
			goto class_to_policydb_out;
		}
		sepol_perm->s.value = sepol_class->permissions.nprim + 1;

		sepol_class->permissions.nprim++;
		cil_perm = cil_perm->next;
	}

	return SEPOL_OK;

class_to_policydb_out:
	return rc;
}

int cil_classcommon_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	struct cil_classcommon *cil_classcom = node->data;
	class_datum_t *sepol_class;
	common_datum_t *sepol_common;

	sepol_class = hashtab_search(pdb->p_classes.table, cil_classcom->class_str);
	if (sepol_class == NULL) {
		goto classcommon_to_policydb_out;
	}

	sepol_common = hashtab_search(pdb->p_commons.table, cil_classcom->common_str);
	if (sepol_common == NULL) {
		goto classcommon_to_policydb_out;
	}

	sepol_class->comdatum = sepol_common;

	return SEPOL_OK;

classcommon_to_policydb_out:
	return rc;
}

int cil_role_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	uint32_t value = 0;
	char *key = NULL;
	struct cil_role *cil_role = node->data;
	role_datum_t *sepol_role = cil_malloc(sizeof(*sepol_role));
	role_datum_init(sepol_role);

	key = cil_strdup(cil_role->datum.name);
	rc = symtab_insert(pdb, SYM_ROLES, key, sepol_role, SCOPE_DECL, 0, &value);
	if (rc != SEPOL_OK) {
		goto role_to_policydb_out;
	}
	sepol_role->s.value = value;

	return SEPOL_OK;

role_to_policydb_out:
	return rc;
}

int cil_roletype_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	struct cil_role *cil_role;
	struct cil_type *cil_type;
	struct cil_roletype *cil_roletype;
	role_datum_t *sepol_role;
	type_datum_t *sepol_type;

	cil_roletype = node->data;
	cil_role = cil_roletype->role;
	cil_type = cil_roletype->type;

	sepol_role = hashtab_search(pdb->p_roles.table, cil_role->datum.name);
	if (sepol_role == NULL) {
		goto roletype_to_policydb_out;
	}

	sepol_type = hashtab_search(pdb->p_types.table, cil_type->datum.name);
	if (sepol_type == NULL) {
		goto roletype_to_policydb_out;
	}

	if (ebitmap_set_bit(&sepol_role->types.types, sepol_type->s.value - 1, 1)) {
		goto roletype_to_policydb_out;
	}

	return SEPOL_OK;

roletype_to_policydb_out:
	return rc;
}

int cil_type_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	uint32_t value = 0;
	char *key = NULL;
	struct cil_type *cil_type = node->data;
	type_datum_t *sepol_type = cil_malloc(sizeof(*sepol_type));
	type_datum_init(sepol_type);

	sepol_type->primary = 1;
	sepol_type->flavor = TYPE_TYPE;

	key = cil_strdup(cil_type->datum.name);
	rc = symtab_insert(pdb, SYM_TYPES, key, sepol_type, SCOPE_DECL, 0, &value);
	if (rc != SEPOL_OK) {
		goto type_to_binary_out;
	}
	sepol_type->s.value = value;

	return SEPOL_OK;

type_to_binary_out:
	return rc;
}

int policydb_type_ebitmap_init(policydb_t *pdb)
{
	int rc = SEPOL_ERR;
	uint32_t i;

	if (pdb->attr_type_map != NULL && pdb->type_attr_map != NULL) {
		rc = SEPOL_OK;
		goto type_ebitmap_out;
        }

	pdb->attr_type_map = cil_malloc(pdb->p_types.nprim * sizeof(ebitmap_t));
	pdb->type_attr_map = cil_malloc(pdb->p_types.nprim * sizeof(ebitmap_t));

	for (i = 0; i < pdb->p_types.nprim; i++) {
		ebitmap_init(&pdb->attr_type_map[i]);
		ebitmap_init(&pdb->type_attr_map[i]);
		if (ebitmap_set_bit(&pdb->type_attr_map[i], i, 1)) {
			goto type_ebitmap_out;
		}
	}

	return SEPOL_OK;

type_ebitmap_out:
	return rc;
}

int cil_policycap_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	int capnum;
	struct cil_policycap *cil_polcap = node->data;

	capnum = sepol_polcap_getnum(cil_polcap->datum.name);
	if (capnum == -1) {
		goto policycap_to_policydb_out;
	}

	if (ebitmap_set_bit(&pdb->policycaps, capnum, 1)) {
		goto policycap_to_policydb_out;
	}

	return SEPOL_OK;

policycap_to_policydb_out:
	return rc;
}

int cil_bool_to_policydb(policydb_t *pdb, struct cil_tree_node *node)
{
	int rc = SEPOL_ERR;
	uint32_t value = 0;
	char *key = NULL;
	struct cil_bool *cil_bool = node->data;
	cond_bool_datum_t *sepol_bool = cil_malloc(sizeof(*sepol_bool));
	memset(sepol_bool, 0, sizeof(cond_bool_datum_t));

	key = cil_strdup(cil_bool->datum.name);
	rc = symtab_insert(pdb, SYM_BOOLS, key, sepol_bool, SCOPE_DECL, 0, &value);
	if (rc != SEPOL_OK) {
		goto bool_to_policydb_out;
	}
	sepol_bool->s.value = value;
	sepol_bool->state = cil_bool->value;

	return SEPOL_OK;

bool_to_policydb_out:
	return rc;
}

int __cil_node_to_policydb(policydb_t *pdb, struct cil_tree_node *node, int pass)
{
	int rc = SEPOL_OK;
	switch (pass) {
	case 1:
		switch (node->flavor) {
		case CIL_COMMON:
			rc = cil_common_to_policydb(pdb, node);
			break;
		case CIL_CLASS:
			rc = cil_class_to_policydb(pdb, node);
			break;
		case CIL_ROLE:
			rc = cil_role_to_policydb(pdb, node);
		case CIL_TYPE:
			rc = cil_type_to_policydb(pdb, node);
			break;
		case CIL_POLICYCAP:
			rc = cil_policycap_to_policydb(pdb, node);
		case CIL_BOOL:
			rc = cil_bool_to_policydb(pdb, node);
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (node->flavor) {
		case CIL_CLASSCOMMON:
			rc = cil_classcommon_to_policydb(pdb, node);
			break;
		case CIL_ROLETYPE:
			rc = cil_roletype_to_policydb(pdb, node);
			break;
		}
		break;
	default:
		break;
	}
	return rc;
}

int __cil_binary_create_helper(struct cil_tree_node *node, __attribute__((unused)) uint32_t *finished, void *extra_args)
{
	int rc = SEPOL_ERR;
	int pass;
	struct cil_args_binary *args = extra_args;
	policydb_t *pdb;

	pdb = args->pdb;
	pass = args->pass;

	rc = __cil_node_to_policydb(pdb, node, pass);
	if (rc != SEPOL_OK) {
		goto binary_create_helper_out;
	}

	return SEPOL_OK;

binary_create_helper_out:
	return rc;
}

int cil_binary_create(const struct cil_db *db, policydb_t *pdb, const char *fname)
{
	int rc = SEPOL_ERR;
	int i;
	FILE *binary;
	struct policy_file pf;
	struct cil_args_binary extra_args;

	if (db == NULL || &pdb == NULL || fname == NULL) {
		goto binary_create_out;
	}

	extra_args.db = db;
	extra_args.pdb = pdb;
	for (i = 1; i <= 2; i++) {
		extra_args.pass = i;
		rc = cil_tree_walk(db->ast->root, __cil_binary_create_helper, NULL, NULL, &extra_args);
		if (rc != SEPOL_OK) {
			goto binary_create_out;
		}
	}

	rc = policydb_type_ebitmap_init(pdb);
	if (rc != SEPOL_OK) {
		goto binary_create_out;
	}

	binary = fopen(fname, "w");
	if (binary == NULL) {
		fprintf(stderr, "Failure creating binary file\n");
		rc = SEPOL_ERR;
		goto binary_create_out;
	}

	policy_file_init(&pf);
	pf.type = PF_USE_STDIO;
	pf.fp = binary;

	rc = policydb_write(pdb, &pf);
	if (rc != 0) {
		fprintf(stderr, "Failed writing binary policy\n");
		goto binary_create_out;
	}

	fclose(binary);

	return SEPOL_OK;

binary_create_out:
	return rc;
}