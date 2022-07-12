
struct task;
struct shared;

struct task_inheritance
{
	int (*compare)(const struct task*, const struct task*);
	
	void (*process)(struct task*, struct shared*);
	
	void (*dotout)(struct task*, struct shared*);
};

