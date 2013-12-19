/*
 * Copyright 2013 Tresys Technology, LLC. All rights reserved.
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

#ifndef CIL_FLAVOR_H_
#define CIL_FLAVOR_H_

/*
	Tree/list node types
*/
#define CIL_MIN_DECLARATIVE	500

enum cil_flavor {
	CIL_NONE = 0,
	CIL_ROOT,
	CIL_DB,
	CIL_AST_NODE,
	CIL_PARSE_NODE,
	CIL_STRING,
	CIL_DATUM,
	CIL_LIST,
	CIL_LIST_ITEM,
	CIL_INT,
	CIL_FILES,
	CIL_AVRULE,
	CIL_BLOCKINHERIT,
	CIL_BLOCKABSTRACT,
	CIL_IN,
	CIL_FILECON,
	CIL_PORTCON,
	CIL_NODECON,
	CIL_GENFSCON,
	CIL_NETIFCON,
	CIL_PIRQCON,
	CIL_IOMEMCON,
	CIL_IOPORTCON,
	CIL_PCIDEVICECON,
	CIL_FSUSE,
	CIL_CONSTRAIN,
	CIL_MLSCONSTRAIN,
	CIL_VALIDATETRANS,
	CIL_MLSVALIDATETRANS,
	CIL_CLASSMAPPING,
	CIL_CLASSPERMS,
	CIL_MAP_CLASSPERMS,
	CIL_USERROLE,
	CIL_USERLEVEL,
	CIL_USERRANGE,
	CIL_USERBOUNDS,
	CIL_USERPREFIX,
	CIL_SELINUXUSER,
	CIL_SELINUXUSERDEFAULT,
	CIL_TYPEATTRIBUTESET,
	CIL_TYPE_RULE,
	CIL_TYPEBOUNDS,
	CIL_NAMETYPETRANSITION,
	CIL_RANGETRANSITION,
	CIL_TYPEPERMISSIVE,
	CIL_ROLETRANSITION,
	CIL_ROLEALLOW,
	CIL_ROLETYPE,
	CIL_ROLEATTRIBUTESET,
	CIL_ROLEBOUNDS,
	CIL_CATORDER,
	CIL_DOMINANCE,
	CIL_SENSCAT,
	CIL_CLASSCOMMON,
	CIL_SIDCONTEXT,
	CIL_CALL,
	CIL_ARGS,
	CIL_BOOLEANIF,
	CIL_TUNABLEIF,
	CIL_CONDBLOCK,
	CIL_CONDTRUE,
	CIL_CONDFALSE,
	CIL_TUNABLEIFDEF,
	CIL_TUNABLEIFNDEF,

	CIL_OP,
	CIL_STAR,
	CIL_AND,
	CIL_OR,
	CIL_XOR,
	CIL_NOT,
	CIL_EQ,
	CIL_NEQ,
	CIL_PARAM,
	CIL_CONS_DOM,
	CIL_CONS_DOMBY,
	CIL_CONS_INCOMP,
	CIL_CONS_OPERAND,
	CIL_CONS_U1,
	CIL_CONS_U2,
	CIL_CONS_U3,
	CIL_CONS_T1,
	CIL_CONS_T2,
	CIL_CONS_T3,
	CIL_CONS_R1,
	CIL_CONS_R2,
	CIL_CONS_R3,
	CIL_CONS_L1,
	CIL_CONS_L2,
	CIL_CONS_H1,
	CIL_CONS_H2,

	CIL_BLOCK = CIL_MIN_DECLARATIVE,
	CIL_OPTIONAL,
	CIL_PERM,
	CIL_COMMON,
	CIL_CLASS,
	CIL_MAP_PERM,
	CIL_MAP_CLASS,
	CIL_CLASSPERMSET,
	CIL_SID,
	CIL_USER,
	CIL_ROLE,
	CIL_ROLEATTRIBUTE,
	CIL_TYPE,
	CIL_TYPEATTRIBUTE,
	CIL_TYPEALIAS,
	CIL_NAME,
	CIL_BOOL,
	CIL_TUNABLE,
	CIL_SENS,
	CIL_SENSALIAS,
	CIL_CAT,
	CIL_CATALIAS,
	CIL_CATRANGE,
	CIL_CATSET,
	CIL_LEVEL,
	CIL_LEVELRANGE,
	CIL_CONTEXT,
	CIL_IPADDR,
	CIL_MACRO,
	CIL_POLICYCAP,
};


#endif /* CIL_FLAVOR_H_ */
