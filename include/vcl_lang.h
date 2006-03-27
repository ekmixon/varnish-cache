/*
 * Stuff necessary to compile a VCL programs C code
 *
 * XXX: When this file is changed, lib/libvcl/vcl_gen_fixed_token.tcl
 * XXX: *MUST* be rerun.
 */


struct vcl_ref {
	unsigned	line;
	unsigned	pos;
	unsigned	count;
	const char	*token;
};

struct vcl_acl {
	unsigned	ip;
	unsigned	mask;
};

struct client {
	unsigned	ip;
};

struct req {
	char		*req;
	char		*useragent;
	struct {
		char		*path;
		char		*host;
	}		url;
	double		ttlfactor;
	struct backend	*backend;
};

struct backend {
	unsigned	ip;
	double		responsetime;
	double		timeout;
	double		bandwidth;
	int		down;
};

struct obj {
	int		exists;
	double		ttl;
	unsigned	result;
	unsigned	size;
	unsigned	usage;
};

#define VCL_FARGS	struct client *client, struct obj *obj, struct req *req, struct backend *backend
#define VCL_PASS_ARGS	client, obj, req, backend

void VCL_count(unsigned);
void VCL_no_cache();
void VCL_no_new_cache();
int ip_match(unsigned, struct vcl_acl *);
int string_match(const char *, const char *);
int VCL_rewrite(const char *, const char *);
int VCL_error(unsigned, const char *);
int VCL_fetch(void);
int VCL_switch_config(const char *);

typedef void vcl_init_f(void);

struct VCL_conf {
	unsigned	magic;
#define VCL_CONF_MAGIC	0x7406c509	/* from /dev/random */
	vcl_init_f	*init_func;
	struct backend	*default_backend;
	struct vcl_ref	*ref;
	unsigned	nref;
};
