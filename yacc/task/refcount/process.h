
struct shared;
struct task;
struct yacc_shared;

void refcount_task_process(struct task* super, struct yacc_shared* shared);
