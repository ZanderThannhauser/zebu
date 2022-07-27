
struct task;
struct shared;
struct yacc_shared;

struct task_inheritance
{
	int (*compare)(const struct task*, const struct task*);
	
	void (*process)(struct task*, struct yacc_shared*);
	
	#ifdef DEBUGGING
	void (*dotout)(struct task*, struct yacc_shared*);
	#endif
	
	void (*free)(struct task*);
};

